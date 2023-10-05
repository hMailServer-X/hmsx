#pragma once

#include "../Common/Threading/Task.h"

namespace HM
{
   class DeliveryQueueClearer : public Task
   {
   public:
      DeliveryQueueClearer(void);
      ~DeliveryQueueClearer(void);

      virtual void DoWork();

   private:

   };

   class DeliveryQueue
   {
   public:
      DeliveryQueue(void);
      ~DeliveryQueue(void);

      static void Clear();
      static void ResetDeliveryTime(long long iMessageID);
      static void Remove(long long iMessageID);
      static void StartDelivery();

      static void OnDeliveryQueueCleared();
   private:

      static bool is_clearing_;
   };
}