#pragma once

namespace HM
{
   class NotificationClient;
   class ChangeNotification;
   class NotificationClientSubscription;

   class NotificationServer
   {
   public:
      NotificationServer();

      void SendNotification(std::shared_ptr<ChangeNotification> pChangeNotification);
      void SendNotification(std::shared_ptr<NotificationClient> source, std::shared_ptr<ChangeNotification> pChangeNotification);

      long long SubscribeMessageChanges(long long accountID, long long folderID, std::shared_ptr<NotificationClient> pChangeClient);
      void UnsubscribeMessageChanges(long long accountID, long long folderID, long long subscriptionKey);

      long long SubscribeFolderListChanges(long long accountID, std::shared_ptr<NotificationClient> pChangeClient);
      void UnsubscribeFolderListChanges(long long accountID, long long subscriptionKey);

   private:

      std::set<std::shared_ptr<NotificationClient> > GetClientsToNotify_(std::shared_ptr<NotificationClient> source, std::shared_ptr<ChangeNotification> pChangeNotification);

      std::multimap<std::pair<long long, long long>, std::shared_ptr<NotificationClientSubscription> > message_change_subscribers_;
      std::multimap<long long, std::shared_ptr<NotificationClientSubscription> > folder_list_change_subscribers_;

      boost::recursive_mutex mutex_;

      long long subscription_counter_;
   };
}
