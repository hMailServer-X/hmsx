#pragma once

namespace HM
{
   class ChangeNotification
   {
   public:

      enum NotificationType
      {
         NotificationMessageAdded = 1,
         NotificationMessageDeleted = 2,
         NotificationMessageFlagsChanged = 3,
      };


      ChangeNotification(NotificationType type);
      ChangeNotification(long long accountID, long long folderID, NotificationType type);
      ChangeNotification(long long accountID, long long folderID, NotificationType type, const std::vector<long long>& affectedMessages);
      ChangeNotification(long long accountID, long long folderID, NotificationType type, long long data);

      virtual ~ChangeNotification();

      const std::vector<long long>& GetAffectedMessages() const;
      long long GetFolderID() const;
      long long GetAccountID() const;
      NotificationType GetType() const;
      long long GetData() const;

   private:

      long long account_id_;
      long long folder_id_;
      long long data_;
      std::vector<long long> affected_messages_;
      NotificationType type_;

   };
}
