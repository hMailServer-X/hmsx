#include "pch.h"

#include "./PersistentServerMessage.h"
#include "../BO/ServerMessage.h"
#include "../SQL/SQLStatement.h"

namespace HM
{
   PersistentServerMessage::PersistentServerMessage(void)
   {
   }

   PersistentServerMessage::~PersistentServerMessage(void)
   {
   }


   bool 
   PersistentServerMessage::DeleteObject(std::shared_ptr<ServerMessage> pObject)
   {
      return false;
   }


   bool 
   PersistentServerMessage::ReadObject(std::shared_ptr<ServerMessage> pObject, std::shared_ptr<DALRecordset> pRS)
   {
      pObject->SetID (pRS->GetLongValue("smid"));
      pObject->SetName(pRS->GetStringValue("smname"));
      pObject->SetText(pRS->GetStringValue("smtext"));

      return true;
   }

   bool 
   PersistentServerMessage::SaveObject(std::shared_ptr<ServerMessage> pObject)
   {
      SQLStatement oStatement;
      oStatement.SetTable("hm_servermessages");
      
      if (pObject->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("smid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);
         String sWhere;
         sWhere.Format(PLATFORM_STRING("smid = %I64d"), pObject->GetID());
         oStatement.SetWhereClause(sWhere);
         
      }

      oStatement.AddColumn("smname", pObject->GetName());
      oStatement.AddColumn("smtext", pObject->GetText());

      bool bNewObject = pObject->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pObject->SetID((int) iDBID);


      return true;
   }
}