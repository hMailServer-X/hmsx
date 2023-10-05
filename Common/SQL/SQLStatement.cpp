#include "pch.h"
#include "SQLStatement.h"
#include "SQLCommand.h"

#include "DatabaseSettings.h"
#include "../Util/VariantDateTime.h"
#include "../Util/Time.h"

namespace HM
{
   SQLStatement::SQLStatement() :
      type_(STUndefined),
      top_rows_(-1)
   {

   }

   SQLStatement::SQLStatement(eStatementType iType, const String &tableName) :
      type_(iType),
      top_rows_(-1),
      table_(tableName)
   {

   }


   SQLStatement::~SQLStatement()
   {

   }

   void 
   SQLStatement::AddColumn(const String &sName, const String &sValue)
   {
      Column p;

      p.sName = sName;
      p.iType = ColTypeString;
      p.sString = sValue;

      vecColumns.push_back(p);
   }

   void 
   SQLStatement::AddColumn(const String &sName, const String &sValue, int iMaxLength)
   {
      Column p;

      String sCopyOfValue = sValue;

      if (sCopyOfValue.GetLength() > iMaxLength)
         sCopyOfValue = sCopyOfValue.Mid(0, iMaxLength);

      p.sName = sName;
      p.iType = ColTypeString;
      p.sString = sCopyOfValue;

      vecColumns.push_back(p);
   }

   void 
   SQLStatement::AddColumnDate(const String &sName, const DateTime & dtValue)
   {
      String value = Time::GetTimeStampFromDateTime(dtValue);

      Column p;

      p.sName = sName;

      // If the date is older than 1800, don't store it. This is to solve
      // limitations in SQL Server.
      if (dtValue.GetStatus() == DateTime::invalid || dtValue.GetYear() < 1800)
      {
         p.iType = ColTypeRaw;
         p.sString = "NULL";
      }
      else
      {
         p.iType = ColTypeString;
         p.sString = value;
      }

      vecColumns.push_back(p);
   }

   void 
   SQLStatement::AddColumnNULL(const String &sName)
   {
      Column p;

      p.sName = sName;
      p.iType = ColTypeRaw;
      p.sString = "NULL";

      vecColumns.push_back(p);
   }



   void 
   SQLStatement::AddColumn(const String &sName, long lValue)
   {
      Column p;
      p.sName = sName;
      p.iType = ColTypeValue;
      p.iInt = lValue;

      vecColumns.push_back(p);
   }

   void 
   SQLStatement::AddColumnInt64(const String &sName, long long lValue)
   {
      Column p;
      p.sName = sName;
      p.iType = ColTypeValue;
      p.iInt = lValue;

      vecColumns.push_back(p);
   }

   void 
   SQLStatement::AddColumn(const String & sName)
   {
      Column p;
      p.sName = sName;
      p.iType = ColTypeUnknown;
   
      vecColumns.push_back(p);
   }

   void
   SQLStatement::AddColumnCommand(const String &column, const String &command)
   {
      Column p;
      p.sName = column;
      p.iType = ColTypeRaw;
      p.sString = command;

      vecColumns.push_back(p);
   }

   SQLCommand
   SQLStatement::GetCommand() const
   {
      DatabaseSettings::SQLDBType dbType = IniFileSettings::Instance()->GetDatabaseType();
      if (dbType == DatabaseSettings::TypeUnknown)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetCommand()", Formatter::Format("Unknown database type: {0}", dbType));
         SQLCommand emtpy;
         return emtpy;
      }

      String sSQL;
      SQLCommand command;

      int parameterValue = 1;
      if (type_ == SQLStatement::STInsert)
      {
         sSQL.append(PLATFORM_STRING("INSERT INTO "));
         sSQL.append(table_);
         sSQL.append(PLATFORM_STRING(" "));

         // First add columns
         sSQL.append(PLATFORM_STRING("("));
         bool first = true;
         for(Column c : vecColumns)
         {
            if (!first)
               sSQL.append(PLATFORM_STRING(", "));
            else
               first = false;

            sSQL.append(c.sName);
         }
         sSQL.append(PLATFORM_STRING(") VALUES ("));

         // Now append values
         first = true;
         for(Column c : vecColumns)
         {
            if (!first)
               sSQL += ", ";
            else
               first = false;

            parameterValue++;
            String parameterName = "@" + c.sName + StringParser::IntToString(parameterValue);

            switch (c.iType)
            {
            case ColTypeValue:
               sSQL.append(parameterName);
               command.AddParameter(parameterName, c.iInt);
               break;
            case ColTypeString:
               sSQL.append(parameterName);
               command.AddParameter(parameterName, c.sString);
               break;
            case ColTypeRaw:
               sSQL.append(Escape(c.sString));
               break;
            }
         }

         sSQL.append(PLATFORM_STRING(")"));

         if (dbType == DatabaseSettings::TypePGServer && !identity_column_.IsEmpty())
         {
            sSQL += " RETURNING " + identity_column_;
         }

      }
      else if (type_ == SQLStatement::STUpdate)
      {
         sSQL.append(PLATFORM_STRING("UPDATE "));
         sSQL.append(table_);
         sSQL.append(PLATFORM_STRING(" SET "));

         // First add columns
         bool first = true;
         for(Column c : vecColumns)
         {
            if (!first)
               sSQL.append(PLATFORM_STRING(", "));
            else
               first = false;

            parameterValue++;
            String parameterName = "@" + c.sName +  StringParser::IntToString(parameterValue);

            sSQL.append(c.sName);
            sSQL.append(PLATFORM_STRING("="));

            switch (c.iType)
            {
            case ColTypeValue:
               sSQL.append(parameterName);
               command.AddParameter(parameterName, c.iInt);
               break;
            case ColTypeString:
               sSQL.append(parameterName);
               command.AddParameter(parameterName, c.sString);
               break;
            case ColTypeRaw:
               sSQL.append(Escape(c.sString));
               break;
            }
         }
      }
      else if (type_ == SQLStatement::STDelete)
      {
         sSQL = "DELETE FROM ";
         sSQL.append(table_);
      }
      else if (type_ == SQLStatement::STSelect)
      {
         sSQL = "SELECT ";

         if (top_rows_ > -1)
         {
            String value;

            switch (dbType)
            {
            case DatabaseSettings::TypeMSSQLServer:
               // SQL Server 2000 does not support ( and ) around the value.
               value.Format(PLATFORM_STRING(" TOP %d "), top_rows_);
               sSQL.append(value);
               break;
            case DatabaseSettings::TypeMSSQLCompactEdition:
               // SQL Server Compact Edition 3.5 requires () around the value.
               value.Format(PLATFORM_STRING(" TOP (%d) "), top_rows_);
               sSQL.append(value);
               break;
            }
         }

         if (vecColumns.size() == 0)
         {
            sSQL += " * ";
         }
         else
         {
            std::vector<Column>::const_iterator it = vecColumns.begin();
            std::vector<Column>::const_iterator itEnd = vecColumns.end();

            bool first = true;

            for(Column c : vecColumns)
            {
               if (!first)
                  sSQL.append(PLATFORM_STRING(", "));
               else
                  first = false;
               
               sSQL.append(c.sName);
            }
         }

         sSQL.append(PLATFORM_STRING(" FROM "));
         sSQL.append(table_);

         if (!additional_sql_.IsEmpty())
            sSQL.append(PLATFORM_STRING(" ") + additional_sql_);
      }

      if (where_clause_columns_.size() != 0)
      {
         sSQL.append(PLATFORM_STRING(" WHERE "));
         bool first = true;
         for(Column col : where_clause_columns_)
         {
            if (!first)
               sSQL.append(PLATFORM_STRING(" AND "));
            else
               first = false;

            parameterValue++;
            String parameterName = "@" + col.sName + StringParser::IntToString(parameterValue);

            if (col.iType == ColTypeString)
            {
               switch (dbType)
               {
               case DatabaseSettings::TypeMYSQLServer:
               case DatabaseSettings::TypeMSSQLServer:
               case DatabaseSettings::TypeMSSQLCompactEdition:
                  sSQL += col.sName + " = " + parameterName;
                  break;
               case DatabaseSettings::TypePGServer:
                  sSQL += "lower(" + col.sName + ") = lower(" + parameterName + ")";
                  break;
               }

               command.AddParameter(parameterName, col.sString);
            }
            else if (col.iType == ColTypeValue)
            {
               sSQL += col.sName + " = " + parameterName;
               command.AddParameter(parameterName, col.iInt);
            }
            else if (col.iType == ColTypeRaw)
            {
               sSQL += col.sName + " = " + Escape(col.sString);
            }
         }
      }
      else if (!where_.IsEmpty())
      {
         sSQL.append(PLATFORM_STRING(" WHERE "));
         sSQL.append(where_);
      }

      if (type_ == SQLStatement::STSelect)
      {
         if (top_rows_ > -1)
         {
            HM::DatabaseSettings::SQLDBType DBType = IniFileSettings::Instance()->GetDatabaseType();
            String value;
            switch (DBType)
            {
            case DatabaseSettings::TypePGServer:
               value.Format(PLATFORM_STRING(" LIMIT %d "), top_rows_);
               sSQL.append(value);
               break;
            case DatabaseSettings::TypeMYSQLServer:
               value.Format(PLATFORM_STRING(" LIMIT 0, %d "), top_rows_);
               sSQL.append(value);
               break;
            }
         }
      }
   
      command.SetQueryString(sSQL);
      return command;
   }

   void 
   SQLStatement::AddWhereClauseColumn(const String &sName, const String &sValue)
   {
      Column col;
      col.iType = ColTypeString;
      col.sName = sName;
      col.sString = sValue;

      where_clause_columns_.push_back(col);
   }

   void
   SQLStatement::SetTopRows(int rowCount)
   {
      top_rows_ = rowCount;
   }

   String 
   SQLStatement::GetCreateDatabase(std::shared_ptr<DatabaseSettings> pSettings, const String &sDatabaseName)
   {
      HM::DatabaseSettings::SQLDBType DBType = pSettings->GetType();
      String sSQL;
      switch (DBType)
      {
      case DatabaseSettings::TypeMSSQLServer:
         sSQL.Format(PLATFORM_STRING("create database %s"), sDatabaseName.c_str());
         break;
      case DatabaseSettings::TypeMYSQLServer:
         sSQL.Format(PLATFORM_STRING("create database %s character set 'utf8'"), sDatabaseName.c_str());
         break;
      case DatabaseSettings::TypePGServer:
         sSQL.Format(PLATFORM_STRING("create database \"%s\" ENCODING = 'UTF8'"), sDatabaseName.c_str());
         break;
      default:
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetCreateDatabase()", Formatter::Format("Unknown database type: {0}", DBType));
         break;
      }

      return sSQL;
   }

   int 
   SQLStatement::GetNoOfCols() const
   { 
      return (int) vecColumns.size(); 
   }

   String 
   SQLStatement::GetCurrentTimestamp()
   {
      HM::DatabaseSettings::SQLDBType DBType = IniFileSettings::Instance()->GetDatabaseType();
      
      switch (DBType)
      {
      case DatabaseSettings::TypeMSSQLServer:
      case DatabaseSettings::TypeMSSQLCompactEdition:
         return "GETDATE()";
      case DatabaseSettings::TypePGServer:
         return "current_timestamp";
      case DatabaseSettings::TypeMYSQLServer:
         return "NOW()";
      default:
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetCurrentTimestamp()", Formatter::Format("Unknown database type: {0}", DBType));   
      }

      assert(0);
      return "";
   }

   String 
   SQLStatement::GetLeftFunction(const String &sParamName, int iLength)
   {
      HM::DatabaseSettings::SQLDBType DBType = IniFileSettings::Instance()->GetDatabaseType();
      String sRetVal;

      switch (DBType)
      {
      case DatabaseSettings::TypeMSSQLServer:
      case DatabaseSettings::TypeMSSQLCompactEdition:
         /*
            Use SUBSTRING instead of the normal LEFT. LEFT doesn't work
            with MSSQL Compact Edition while SUBSTRING works with both.
         */
         sRetVal.Format(PLATFORM_STRING("SUBSTRING(%s, 1, %d)"), sParamName.c_str(), iLength);
         break;
      case DatabaseSettings::TypePGServer:
         sRetVal.Format(PLATFORM_STRING("SUBSTRING(%s FROM 1 FOR %d)"), sParamName.c_str(), iLength);
         break;
      case DatabaseSettings::TypeMYSQLServer:
         sRetVal.Format(PLATFORM_STRING("LEFT(%s, %d)"), sParamName.c_str(), iLength);
         break;
      default:
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetLeftFunction()", Formatter::Format("Unknown database type: {0}", DBType));
         break;
      }

      return sRetVal;
   }

   String 
   SQLStatement::GetTopRows(const String &tableName, int rows)
   {
      HM::DatabaseSettings::SQLDBType DBType = IniFileSettings::Instance()->GetDatabaseType();
      String sRetVal;

      switch (DBType)
      {
      case DatabaseSettings::TypeMSSQLServer:
      case DatabaseSettings::TypeMSSQLCompactEdition:
         /*
         Use SUBSTRING instead of the normal LEFT. LEFT doesn't work
         with MSSQL Compact Edition while SUBSTRING works with both.
         */
         sRetVal.Format(PLATFORM_STRING("SELECT TOP %d FROM %s"), rows, tableName.c_str());
         break;
      case DatabaseSettings::TypePGServer:
         sRetVal.Format(PLATFORM_STRING("SELECT * FROM %s LIMIT %d"), tableName.c_str(), rows);
         break;
      case DatabaseSettings::TypeMYSQLServer:
         sRetVal.Format(PLATFORM_STRING("SELECT * FROM %s LIMIT 0, %d"), tableName.c_str(), rows);
         break;
      default:
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetTopRows()", Formatter::Format("Unknown database type: {0}", DBType));
         break;
      }

      return sRetVal;
   }

   String 
   SQLStatement::GetCurrentTimestampPlusMinutes(int iMinutes)
   {
      HM::DatabaseSettings::SQLDBType DBType = IniFileSettings::Instance()->GetDatabaseType();

      String sRetVal;

      switch (DBType)
      {
      case DatabaseSettings::TypeMYSQLServer:
         sRetVal.Format(PLATFORM_STRING("DATE_ADD(CONCAT(CURDATE(), ' ', CURTIME()), INTERVAL %d MINUTE)"), iMinutes);
         break;
      case DatabaseSettings::TypeMSSQLServer:
      case DatabaseSettings::TypeMSSQLCompactEdition:
         sRetVal.Format(PLATFORM_STRING("DATEADD(mi, %d, GETDATE())"), iMinutes);
         break;
      case DatabaseSettings::TypePGServer:
         sRetVal.Format(PLATFORM_STRING("current_timestamp + INTERVAL '%d minutes'"), iMinutes);
         break;
      default:
         ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5407, "SQLStatement::GetCurrentTimestampPlusMinutes()", Formatter::Format("Unknown database type: {0}", DBType));
         break;

      }

      return sRetVal;
   }

   String 
   SQLStatement::Escape(const String &input)
   {
      String sRetVal = input;

      sRetVal.Replace(PLATFORM_STRING("'"), PLATFORM_STRING("''"));

      HM::DatabaseSettings::SQLDBType iType = IniFileSettings::Instance()->GetDatabaseType();

      if (iType == DatabaseSettings::TypeMYSQLServer || iType == DatabaseSettings::TypePGServer)
         sRetVal.Replace(PLATFORM_STRING("\\"), PLATFORM_STRING("\\\\"));

      return sRetVal;
   }

   String
   SQLStatement::GenerateFromCommand(const SQLCommand &command)
   {
      String queryString = command.GetQueryString();

      for(SQLParameter parameter : command.GetParameters())
      {
         String paramName = parameter.GetName();

         if (parameter.GetType() == SQLParameter::ParamTypeInt32)
         {
            queryString.Replace(paramName, StringParser::IntToString(parameter.GetInt32Value()));
         }
         if (parameter.GetType() == SQLParameter::ParamTypeInt64)
         {
            queryString.Replace(paramName, StringParser::IntToString(parameter.GetInt64Value()));
         }
         if (parameter.GetType() == SQLParameter::ParamTypeUnsignedInt32)
         {
            queryString.Replace(paramName, StringParser::IntToString(parameter.GetUnsignedInt32Value()));
         }
         else if (parameter.GetType() == SQLParameter::ParamTypeString)
         {
            String valueToUse = "'" + Escape(parameter.GetStringValue()) + "'";
            queryString.Replace(paramName, valueToUse);
         }
      }

      return queryString;
   }

   String
   SQLStatement::ConvertWildcardToLike(String input)
   {
      input.Replace(PLATFORM_STRING("/"), PLATFORM_STRING("//"));
      input.Replace(PLATFORM_STRING("%"), PLATFORM_STRING("/%"));
      input.Replace(PLATFORM_STRING("_"), PLATFORM_STRING("/_"));
      input.Replace(PLATFORM_STRING("?"), PLATFORM_STRING("_"));
      input.Replace(PLATFORM_STRING("*"), PLATFORM_STRING("%"));
      return input;
   }

   String
   SQLStatement::ConvertLikeToWildcard(String input)
   {
      input.Replace(PLATFORM_STRING("//"), PLATFORM_STRING("/"));
      input.Replace(PLATFORM_STRING("/%"), PLATFORM_STRING("¤¤¤ESCAPED¤¤¤PERCENTAGE¤¤¤"));
      input.Replace(PLATFORM_STRING("/_"), PLATFORM_STRING("¤¤¤ESCAPED¤¤¤UNDERSCORE¤¤¤"));
      input.Replace(PLATFORM_STRING("_"), PLATFORM_STRING("?"));
      input.Replace(PLATFORM_STRING("%"), PLATFORM_STRING("*"));
      input.Replace(PLATFORM_STRING("¤¤¤ESCAPED¤¤¤PERCENTAGE¤¤¤"), PLATFORM_STRING("%"));
      input.Replace(PLATFORM_STRING("¤¤¤ESCAPED¤¤¤UNDERSCORE¤¤¤"), PLATFORM_STRING("_"));

      return input;
   }
}
