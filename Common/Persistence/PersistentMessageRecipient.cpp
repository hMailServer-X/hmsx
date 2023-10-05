#include "pch.h"
#include "PersistentMessageRecipient.h"
#include "../BO/MessageRecipient.h"

namespace HM
{
   PersistentMessageRecipient::PersistentMessageRecipient(void)
   {
   }

   PersistentMessageRecipient::~PersistentMessageRecipient(void)
   {
   }


   bool 
   PersistentMessageRecipient::DeleteObject(std::shared_ptr<MessageRecipient> pRecipient)
   {
      SQLCommand command("delete from hm_messagerecipients where recipientaddress = @ADDRESS AND recipientmessageid = @MESSAGEID");
      command.AddParameter("@ADDRESS", pRecipient->GetAddress());
      command.AddParameter("@MESSAGEID", pRecipient->GetMessageID());

      return Application::Instance()->GetDBManager()->Execute(command);

   }
}