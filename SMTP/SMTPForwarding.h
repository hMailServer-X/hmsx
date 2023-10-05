#pragma once

namespace HM
{
   class Account;
   class Message;
   class MessageData;

   class SMTPForwarding
   {
   public:

      bool PerformForwarding(std::shared_ptr<const Account> pRecipientAccount, std::shared_ptr<Message> pOriginalMessage);


   };
}