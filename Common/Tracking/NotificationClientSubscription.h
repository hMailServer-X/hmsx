#pragma once

namespace HM
{
   class NotificationClient;

   class NotificationClientSubscription
   {
   public:
      NotificationClientSubscription(long long subscriptionKey, std::weak_ptr<NotificationClient> client);
      virtual ~NotificationClientSubscription();

      long long GetSubscriptionKey();
      std::weak_ptr<NotificationClient> GetSubscribedClient();

   private:

      long long subscription_key_;
      std::weak_ptr<NotificationClient> client_;

   };
}
