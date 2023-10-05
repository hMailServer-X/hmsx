#pragma once

#include <set>

namespace HM
{

   class POP3Sessions : public Singleton<POP3Sessions>
   {
   public:
	   POP3Sessions();
	   virtual ~POP3Sessions();

      bool IsLocked(long long iAccount);
      bool Lock(long long iAccount);
      void Unlock(long long iAccount);
   
   private:

      std::set<long long> locked_accounts_;

      boost::recursive_mutex mutex_;
   };

}
