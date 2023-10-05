#include "pch.h"
#include "PersistentAlias.h"
#include "../Cache/Cache.h"
#include "PreSaveLimitationsCheck.h"
#include "PersistenceMode.h"
#include "../BO/Alias.h"

namespace HM
{
   PersistentAlias::PersistentAlias()
   {

   }

   PersistentAlias::~PersistentAlias()
   {

   }
   bool
   PersistentAlias::DeleteObject(std::shared_ptr<Alias> pAlias)
   {
      assert(pAlias->GetID());

      bool bResult = false;
      if (pAlias->GetID() > 0)
      {
         SQLCommand command("delete from hm_aliases where aliasid = @ALIASID");
         command.AddParameter("@ALIASID", pAlias->GetID());
    
         bResult = Application::Instance()->GetDBManager()->Execute(command);

         Cache<Alias>::Instance()->RemoveObject(pAlias);
      }

      return bResult;
   }

   bool
   PersistentAlias::SaveObject(std::shared_ptr<Alias> pAlias)
   {
      String sErrorMessage;

      return SaveObject(pAlias, sErrorMessage, PersistenceModeNormal);
   }

   bool
   PersistentAlias::SaveObject(std::shared_ptr<Alias> pAlias, String &sErrorMessage, PersistenceMode mode)
   {
      if (!PreSaveLimitationsCheck::CheckLimitations(mode, pAlias, sErrorMessage))
         return false;

      SQLStatement oStatement;
      
      oStatement.SetTable("hm_aliases");

      oStatement.AddColumnInt64("aliasdomainid", pAlias->GetDomainID());
      oStatement.AddColumn("aliasname", pAlias->GetName());
      oStatement.AddColumn("aliasvalue", pAlias->GetValue());
      oStatement.AddColumn("aliasactive", pAlias->GetIsActive());

      if (pAlias->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("aliasid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);

         String sWhere;
         sWhere.Format(PLATFORM_STRING("aliasid = %I64d"), pAlias->GetID());
         oStatement.SetWhereClause(sWhere);
      }

      bool bNewObject = pAlias->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pAlias->SetID((int) iDBID);

      Cache<Alias>::Instance()->RemoveObject(pAlias);

      return bRetVal;
   }

   bool
   PersistentAlias::ReadObject(std::shared_ptr<Alias> pAlias, const String & sName)
   {
      SQLStatement statement;

      statement.SetStatementType(SQLStatement::STSelect);
      statement.SetTable("hm_aliases");
      statement.AddWhereClauseColumn("aliasname", sName);

      return ReadObject(pAlias, statement.GetCommand());
   }

   bool
   PersistentAlias::ReadObject(std::shared_ptr<Alias> pAccount, long long ObjectID)
   {
      SQLCommand command("select * from hm_aliases where aliasid = @ALIASID");
      command.AddParameter("@ALIASID", ObjectID);

      bool bResult = ReadObject(pAccount, command);

      return bResult;
   }


   bool
   PersistentAlias::ReadObject(std::shared_ptr<Alias> pAlias, const SQLCommand &command)
   {
      std::shared_ptr<DALRecordset> pRS = Application::Instance()->GetDBManager()->OpenRecordset(command);
      if (!pRS)
         return false;

      bool bRetVal = false;
      if (!pRS->IsEOF())
      {
         bRetVal = ReadObject(pAlias, pRS);
      }
   
      return bRetVal;
   }



   bool
   PersistentAlias::ReadObject(std::shared_ptr<Alias> pAlias, std::shared_ptr<DALRecordset> pRS)
   {
   
      pAlias->SetID(pRS->GetLongValue("aliasid"));
      pAlias->SetIsActive(pRS->GetLongValue("aliasactive") ? true : false);
      pAlias->SetDomainID(pRS->GetLongValue("aliasdomainid"));
      pAlias->SetName(pRS->GetStringValue("aliasname"));
      pAlias->SetValue(pRS->GetStringValue("aliasvalue"));
   
      return true;
   }
}