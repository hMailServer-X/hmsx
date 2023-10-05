#include "pch.h"
#include "NotificationClientSubscription.h"

namespace HM
{
   NotificationClientSubscription::NotificationClientSubscription(long long subscriptionKey, std::weak_ptr<NotificationClient> client) :
      subscription_key_(subscriptionKey),
      client_(client)
   {

   }

   NotificationClientSubscription::~NotificationClientSubscription()
   {

   }

   long long 
   NotificationClientSubscription::GetSubscriptionKey()
   {
      return subscription_key_;
   }

   std::weak_ptr<NotificationClient> 
   NotificationClientSubscription::GetSubscribedClient()
   {
      return client_;
   }

}
