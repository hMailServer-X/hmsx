#pragma once

#include "../Common/Tracking/NotificationClient.h"

namespace HM
{
   class IMAPConnection;
   class ChangeNotification;

   class IMAPNotificationClient : public NotificationClient,
                                  public std::enable_shared_from_this<IMAPNotificationClient>
   {
   public:

      IMAPNotificationClient();
      virtual ~IMAPNotificationClient();

      void SetConnection(std::weak_ptr<IMAPConnection> connection);
      virtual void OnNotification(std::shared_ptr<ChangeNotification> notification);

      void SendCachedNotifications(bool send_expunge);

      static String GenerateRecentString(int recentMessages);
      static String GenerateExistsString(int recentMessages);

      void SubscribeMessageChanges(long long accountID, long long folderID);

      void UnsubscribeMessageChanges();

   private:

      void CacheChangeNotification_(std::shared_ptr<ChangeNotification> pChangeNotification);
      void SendChangeNotification_(std::shared_ptr<ChangeNotification> pChangeNotification);

      void SendEXISTS_(int iExists);
      void SendRECENT_(int recent);
      void SendEXPUNGE_(const std::vector<long long> & vecMessages);
      void SendFLAGS_(const std::set<long long> & vecMessages);

      boost::recursive_mutex mutex_;
      std::vector<std::shared_ptr<ChangeNotification> > cached_changes_;
      
      std::weak_ptr<IMAPConnection> parent_connection_;

      long long account_id_;
      long long folder_id_;
      long long message_change_subscription_id_;
      long long folder_list_change_subscription_id_;

   };


}