#include "pch.h"
#include "ChangeNotification.h"

namespace HM
{

   ChangeNotification::ChangeNotification(NotificationType type) :
      type_(type)
   {

   }

   ChangeNotification::ChangeNotification(long long accountID, long long folderID, NotificationType type) :
      account_id_(accountID),
      folder_id_(folderID),
      type_(type)
   {

   }

   ChangeNotification::ChangeNotification(long long accountID, long long folderID, NotificationType type, const std::vector<long long>& affectedMessages) :
      account_id_(accountID),
      folder_id_(folderID),
      type_(type),
      affected_messages_(affectedMessages)
   {

   }

   ChangeNotification::ChangeNotification(long long accountID, long long folderID, NotificationType type, long long data) :
      account_id_(accountID),
      folder_id_(folderID),
      type_(type),
      data_(data)
   {

   }

   ChangeNotification::~ChangeNotification()
   {

   }

   long long
   ChangeNotification::GetFolderID() const
   {
      return folder_id_;
   }

   long long
   ChangeNotification::GetAccountID() const
   {
      return account_id_;
   }

   long long
   ChangeNotification::GetData() const
   {
      return data_;
   }

   ChangeNotification::NotificationType
   ChangeNotification::GetType() const
   {
      return type_;
   }

   const std::vector<long long>&
   ChangeNotification::GetAffectedMessages() const
   {
      return affected_messages_;
   }

}
