#pragma once

namespace HM
{
   class AccountSizeCache : public Singleton<AccountSizeCache>
   {
   public:
      AccountSizeCache(void);
      virtual ~AccountSizeCache(void);

      void ModifySize(long long accountID, long long iSize, bool bIncrease);
      void Reset(long long accountID);
      long long GetSize(long long accountID);

   private:

      std::map<long long, long long> account_sizes_;

      boost::recursive_mutex mutex_;
   };
}