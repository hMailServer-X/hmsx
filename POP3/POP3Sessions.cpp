#include "pch.h"
#include "POP3Sessions.h"

namespace HM
{

   POP3Sessions::POP3Sessions()
   {

   }

   POP3Sessions::~POP3Sessions()
   {

   }

   bool 
   POP3Sessions::IsLocked(long long iAccount)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      bool bRet = false;
      if (locked_accounts_.find(iAccount) != locked_accounts_.end())
         bRet = true;

      return bRet;
   }

   bool 
   POP3Sessions::Lock(long long iAccount)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      if (locked_accounts_.find(iAccount) == locked_accounts_.end())
      {
         locked_accounts_.insert(iAccount);
         return true;
      }
      else
      {
         return false;
      }
   }
      
   void 
   POP3Sessions::Unlock(long long iAccount)
   {
      boost::lock_guard<boost::recursive_mutex> guard(mutex_);

      auto iter =  locked_accounts_.find(iAccount);
      if (iter != locked_accounts_.end())
         locked_accounts_.erase(iter);
   }
}
