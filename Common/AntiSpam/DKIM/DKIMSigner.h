#pragma once

namespace HM
{
   class Message;

   class DKIMSigner
   {
   public:
      DKIMSigner();

      void Sign(std::shared_ptr<Message> message);
   };

}