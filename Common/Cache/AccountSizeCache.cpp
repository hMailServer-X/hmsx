#include "pch.h"

#include "AccountSizeCache.h"
#include "../Persistence/PersistentAccount.h"

namespace HM
{
   AccountSizeCache::AccountSizeCache(void)
   {

   }

   AccountSizeCache::~AccountSizeCache(void)
   {

   }

   void
   AccountSizeCache::ModifySize(long long accountID, long long iSize, bool bIncrease)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      auto iter = account_sizes_.find(accountID);
      if (iter == account_sizes_.end())
         return;

      long long currentSize = (*iter).second;

      if (bIncrease)
         currentSize += iSize;
      else
         currentSize -= iSize;

      account_sizes_[accountID] = currentSize;
   }
   
   void
   AccountSizeCache::Reset(long long accountID)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      auto iter = account_sizes_.find(accountID);
      if (iter == account_sizes_.end())
         return;

      account_sizes_.erase(iter);
   }


   long long
   AccountSizeCache::GetSize(long long accountID)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      auto iter = account_sizes_.find(accountID);
      if (iter == account_sizes_.end())
      {
         long long size = PersistentAccount::GetMessageBoxSize(accountID);
         account_sizes_[accountID] = size;
         return size;
      }

      return (*iter).second;
   }
   
}