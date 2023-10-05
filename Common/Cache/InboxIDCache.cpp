#include "pch.h"

#include "InboxIDCache.h"
#include "../Persistence/PersistentIMAPFolder.h"

namespace HM
{
   InboxIDCache::InboxIDCache() :
      enabled_ (true)
   {

   }

   InboxIDCache::~InboxIDCache(void)
   {
   }

   void 
   InboxIDCache::Clear()
   {
      if (!enabled_)
         return;
   
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      inbox_id_.clear();
   }

   long long
   InboxIDCache::GetUserInboxFolder(long long accountID)
   {
      if (enabled_)
      {
         boost::lock_guard<boost::recursive_mutex> guard(mutex_);
         auto iter = inbox_id_.find(accountID);

         if (iter != inbox_id_.end())
         {
            long long result = (*iter).second;
            return result;
         }
      }

      long long inboxID = PersistentIMAPFolder::GetUserInboxFolder(accountID);

      if (enabled_)
      {
         boost::lock_guard<boost::recursive_mutex> guard(mutex_);
         inbox_id_[accountID] = inboxID;
      }

      return inboxID;
   }
}