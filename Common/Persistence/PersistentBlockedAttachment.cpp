#include "pch.h"

#include "./PersistentBlockedAttachment.h"
#include "../BO/BlockedAttachment.h"
#include "../SQL/SQLStatement.h"

namespace HM
{
   PersistentBlockedAttachment::PersistentBlockedAttachment(void)
   {
   }

   PersistentBlockedAttachment::~PersistentBlockedAttachment(void)
   {
   }

   bool
   PersistentBlockedAttachment::DeleteObject(std::shared_ptr<BlockedAttachment> pObject)
   {
      SQLCommand command("delete from hm_blocked_attachments where baid = @BAID");
      command.AddParameter("@BAID", pObject->GetID());

      return Application::Instance()->GetDBManager()->Execute(command);
   }

   bool 
   PersistentBlockedAttachment::ReadObject(std::shared_ptr<BlockedAttachment> pObject, std::shared_ptr<DALRecordset> pRS)
   {
      pObject->SetID (pRS->GetLongValue("baid"));
      pObject->SetWildcard(pRS->GetStringValue("bawildcard"));
      pObject->SetDescription(pRS->GetStringValue("badescription"));

      return true;
   }

   bool 
   PersistentBlockedAttachment::SaveObject(std::shared_ptr<BlockedAttachment> pObject, String &errorMessage, PersistenceMode mode)
   {
      // errorMessage -- not supported yet.
      return SaveObject(pObject);
   }

   bool 
   PersistentBlockedAttachment::SaveObject(std::shared_ptr<BlockedAttachment> pObject)
   {
      SQLStatement oStatement;
      oStatement.SetTable("hm_blocked_attachments");
      
      if (pObject->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("baid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);
         String sWhere;
         sWhere.Format(PLATFORM_STRING("baid = %I64d"), pObject->GetID());
         oStatement.SetWhereClause(sWhere);
         
      }

      oStatement.AddColumn(PLATFORM_STRING("bawildcard"), pObject->GetWildcard());
      oStatement.AddColumn(PLATFORM_STRING("badescription"), pObject->GetDescription());

      bool bNewObject = pObject->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pObject->SetID((int) iDBID);


      return true;
   }
}