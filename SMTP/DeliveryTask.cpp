#include "pch.h"

#include "DeliveryTask.h"
#include "SMTPDeliverer.h"

namespace HM
{
   DeliveryTask::DeliveryTask(std::shared_ptr<Message> pMessage) :
      Task("DeliveryTask"),
      message_(pMessage)
   {
      
   }

   DeliveryTask::~DeliveryTask(void)
   {
   }

   void 
   DeliveryTask::DoWork()
   {
      // Do our delivery work.
      SMTPDeliverer::DeliverMessage(message_);
   }

}