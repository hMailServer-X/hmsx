#include "pch.h"

#include "./PersistentSURBLServer.h"
#include "../BO/SURBLServer.h"
#include "../SQL/SQLStatement.h"

namespace HM
{
   PersistentSURBLServer::PersistentSURBLServer(void)
   {
   }

   PersistentSURBLServer::~PersistentSURBLServer(void)
   {
   }

   bool
   PersistentSURBLServer::DeleteObject(std::shared_ptr<SURBLServer> pObject)
   {
      SQLCommand command("delete from hm_surblservers where surblid = @SURBLID");
      command.AddParameter("@SURBLID", pObject->GetID());

      Application::Instance()->GetDBManager()->Execute(command);
      return true;
   }

   bool 
   PersistentSURBLServer::ReadObject(std::shared_ptr<SURBLServer> pObject, std::shared_ptr<DALRecordset> pRS)
   {
      pObject->SetID (pRS->GetLongValue("surblid"));
      pObject->SetIsActive(pRS->GetLongValue("surblactive") == 1);
      pObject->SetDNSHost(pRS->GetStringValue("surblhost"));
      pObject->SetRejectMessage(pRS->GetStringValue("surblrejectmessage"));
      pObject->SetScore(pRS->GetLongValue("surblscore"));


      return true;
   }

   bool 
   PersistentSURBLServer::SaveObject(std::shared_ptr<SURBLServer> pObject, String &errorMessage, PersistenceMode mode)
   {
      // errorMessage - not supported yet.
      return SaveObject(pObject);
   }

   bool 
   PersistentSURBLServer::SaveObject(std::shared_ptr<SURBLServer> pObject)
   {
      SQLStatement oStatement;
      oStatement.SetTable("hm_surblservers");
      
      if (pObject->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("surblid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);
         String sWhere;
         sWhere.Format(PLATFORM_STRING("surblid = %I64d"), pObject->GetID());
         oStatement.SetWhereClause(sWhere);
         
      }

      oStatement.AddColumn("surblactive", pObject->GetIsActive() == 1);
      oStatement.AddColumn("surblhost", pObject->GetDNSHost());
      oStatement.AddColumn("surblrejectmessage", pObject->GetRejectMessage());
      oStatement.AddColumn("surblscore", pObject->GetScore());

      bool bNewObject = pObject->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pObject->SetID((int) iDBID);


      return true;
   }
}