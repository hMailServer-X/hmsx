#include "pch.h"
#include "NotificationServer.h"
#include "NotificationClient.h"
#include "ChangeNotification.h"
#include "NotificationClientSubscription.h"

namespace HM
{
   NotificationServer::NotificationServer() :
      subscription_counter_(0)
   {

   }

   void 
   NotificationServer::SendNotification(std::shared_ptr<ChangeNotification> pChangeNotification)
   {
      std::shared_ptr<NotificationClient> empty;
      SendNotification(empty, pChangeNotification);
   }

   void 
   NotificationServer::SendNotification(std::shared_ptr<NotificationClient> source, std::shared_ptr<ChangeNotification> pChangeNotification)
   {
      std::set<std::shared_ptr<NotificationClient> > clientsToNotify = GetClientsToNotify_(source, pChangeNotification);

      for(std::shared_ptr<NotificationClient> client : clientsToNotify)
      {
         client->OnNotification(pChangeNotification);
      }
   }

   std::set<std::shared_ptr<NotificationClient> >
   NotificationServer::GetClientsToNotify_(std::shared_ptr<NotificationClient> source, std::shared_ptr<ChangeNotification> changeNotification)
   {
      std::set<std::shared_ptr<NotificationClient> > clientsToNotify;

      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      switch (changeNotification->GetType())
      {
      case ChangeNotification::NotificationMessageAdded:
      case ChangeNotification::NotificationMessageDeleted:
      case ChangeNotification::NotificationMessageFlagsChanged:
         {
            // This is a message change notification.
            std::pair<long long, long long> folderSpecifier = std::make_pair(changeNotification->GetAccountID(), changeNotification->GetFolderID());

            // Locate subscribed client.
            auto iter = message_change_subscribers_.find(folderSpecifier);
            if (iter == message_change_subscribers_.end())
               return clientsToNotify;

            auto iterLast = message_change_subscribers_.upper_bound(folderSpecifier);

            while (iter != iterLast)
            {
               // Notify this client.
               std::shared_ptr<NotificationClientSubscription> subscription = (*iter).second;
               std::weak_ptr<NotificationClient> client = subscription->GetSubscribedClient();

               std::shared_ptr<NotificationClient> safeClient = client.lock();

               if (!safeClient)
               {
                  iter = message_change_subscribers_.erase(iter);
                  ErrorManager::Instance()->ReportError(ErrorManager::Low, 5341, "MailboxChangeNotifier::ReportChange", "A previous folder subscription unsubscription failed. Cleaning up.");
                  continue;
               }

               if (source == safeClient)
               {
                  // let's not notify ourselves.
                  iter++;
                  continue;
               }

               clientsToNotify.insert(safeClient);

               iter++;
            }
         }
         break;
      }

      return clientsToNotify;

   }

   long long
   NotificationServer::SubscribeMessageChanges(long long accountID, long long folderID, std::shared_ptr<NotificationClient> pChangeClient)
   {
      try
      {
         std::pair<long long, long long> folderSpecifier = std::make_pair(accountID, folderID);

         boost::lock_guard<boost::recursive_mutex> guard(mutex_);

         subscription_counter_++;
         std::shared_ptr<NotificationClientSubscription> subscription = 
            std::shared_ptr<NotificationClientSubscription>(new NotificationClientSubscription(subscription_counter_, pChangeClient));

         // Add subscription
         message_change_subscribers_.insert(std::make_pair(folderSpecifier, subscription));

         return subscription_counter_;
      }
      catch (...)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Medium, 4307, "MailboxChangeNotifier::SubscribeFolderChanges", "An unknown error has occurred.");
         throw;
      }

      return 0;
   }

   void 
   NotificationServer::UnsubscribeMessageChanges(long long iAccountID, long long iFolderID, long long subscriptionKey)
   {
      try
      {
         std::pair<long long, long long> folderSpecifier = std::make_pair(iAccountID, iFolderID);

         boost::lock_guard<boost::recursive_mutex> guard(mutex_);

         auto iter = message_change_subscribers_.find(folderSpecifier);
         if (iter == message_change_subscribers_.end())
            return;

         auto iterLast = message_change_subscribers_.upper_bound(folderSpecifier);

         for(; iter != iterLast; iter++)
         {
            std::shared_ptr<NotificationClientSubscription> subscription = (*iter).second;

            if (subscription->GetSubscriptionKey() == subscriptionKey)
            {
               // Unsubscribe
               iter =  message_change_subscribers_.erase(iter);
               return;
            }
         }

      }
      catch (...)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Medium, 4308, "MailboxChangeNotifier::Unsubscribe", "An unknown error has occurred.");
         throw;
      }
   }     

   long long
   NotificationServer::SubscribeFolderListChanges(long long accountID, std::shared_ptr<NotificationClient> pChangeClient)
   {
      try
      {
         boost::lock_guard<boost::recursive_mutex> guard(mutex_);

         subscription_counter_++;
         std::shared_ptr<NotificationClientSubscription> subscription = 
            std::shared_ptr<NotificationClientSubscription>(new NotificationClientSubscription(subscription_counter_, pChangeClient));

         // Add subscription
         folder_list_change_subscribers_.insert(std::make_pair(accountID, subscription));

         return subscription_counter_;
      }
      catch (...)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Medium, 4307, "MailboxChangeNotifier::SubscribeFolderChanges", "An unknown error has occurred.");
         throw;
      }

      return 0;
   }

   void 
   NotificationServer::UnsubscribeFolderListChanges(long long accountID, long long subscriptionKey)
   {
      try
      {
         boost::lock_guard<boost::recursive_mutex> guard(mutex_);

         auto iter = folder_list_change_subscribers_.find(accountID);
         if (iter == folder_list_change_subscribers_.end())
            return;

         auto iterLast = folder_list_change_subscribers_.upper_bound(accountID);

         for(; iter != iterLast; iter++)
         {
            std::shared_ptr<NotificationClientSubscription> subscription = (*iter).second;

            if (subscription->GetSubscriptionKey() == subscriptionKey)
            {
               // Unsubscribe
               iter =  folder_list_change_subscribers_.erase(iter);
               return;
            }
         }

      }
      catch (...)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Medium, 4308, "MailboxChangeNotifier::Unsubscribe", "An unknown error has occurred.");
         throw;
      }
   }     
}
