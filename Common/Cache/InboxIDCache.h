#pragma once

namespace HM
{
   class InboxIDCache
   {
   public:
      InboxIDCache(void);
      virtual ~InboxIDCache(void);

      void Clear();

      long long GetUserInboxFolder(long long accountID);

   private:

      boost::recursive_mutex mutex_;
      std::map<long long, long long > inbox_id_;

      bool enabled_;
   };
}