#pragma once

namespace HM
{
   class MessageRecipient;

   class PersistentMessageRecipient 
   {
   public:
      PersistentMessageRecipient(void);
      ~PersistentMessageRecipient(void);

      static bool DeleteObject(std::shared_ptr<MessageRecipient> pRecipient);
   };
}
