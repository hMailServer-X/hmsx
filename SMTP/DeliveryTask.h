#pragma once

#include "../Common/Threading/Task.h"

namespace HM
{
   class Message;

   class DeliveryTask : public Task
   {
   public:
      DeliveryTask(std::shared_ptr<Message> pMessage);
      ~DeliveryTask(void);

      virtual void DoWork();

   private:
      
      std::shared_ptr<Message> message_;
   };
}