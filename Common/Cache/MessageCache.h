#pragma once
#include "../Util/Singleton.h"

namespace HM
{
   class Message;

   class MessageCache : public Singleton<MessageCache>
   {
   public:
      MessageCache(void);
      ~MessageCache(void);

      void AddMessage(std::shared_ptr<Message> pMessage);
      std::shared_ptr<Message> GetMessage(long long iMessageID);


   private:

      boost::recursive_mutex mutex_;
      std::map<long long, std::shared_ptr<Message> > message_;

   };
}