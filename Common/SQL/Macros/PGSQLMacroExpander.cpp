#include "pch.h"
#include "PGSQLMacroExpander.h"
#include "Macro.h"
#include "../PGRecordset.h"

namespace HM
{
   bool
   PGSQLMacroExpander::ProcessMacro(std::shared_ptr<DALConnection> connection, const Macro &macro, String &sErrorMessage)
   {
      switch (macro.GetType())
      {
      case Macro::DropColumnKeys:
         SQLCommand command("select DISTINCT CONSTRAINT_NAME from INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_NAME = @TABLE_NAME AND COLUMN_NAME = @COLUMN_NAME");
         command.AddParameter("@TABLE_NAME", macro.GetTableName());
         command.AddParameter("@COLUMN_NAME", macro.GetColumnName());

         PGRecordset rec;
         if (!rec.Open(connection, command))
         {
            sErrorMessage = "It was not possible to execute the below SQL statement. Please see hMailServer error log for details.\r\n" + command.GetQueryString();
            return false;
         }

         while (!rec.IsEOF())
         {
            String constraintName = rec.GetStringValue("CONSTRAINT_NAME");

            String sqlUpdate;
            sqlUpdate.Format(PLATFORM_STRING("ALTER TABLE %s DROP %s"), macro.GetTableName().c_str(), constraintName.c_str());

            DALConnection::ExecutionResult execResult = connection->TryExecute(SQLCommand(sqlUpdate), sErrorMessage, 0, 0);

            if (execResult != DALConnection::DALSuccess)
               return false;

            rec.MoveNext();
         }
         break;
      }

      return true;
   }
}
