#pragma once

namespace HM
{
   class Account;

   class PersistentLogonFailure
   {
   public:
	   PersistentLogonFailure();
	   virtual ~PersistentLogonFailure();

      int GetCurrrentFailureCount(const IPAddress & ipaddress);
      bool AddFailure(const IPAddress &ipaddress);
      bool ClearOldFailures(int olderThanMinutes);
      bool ClearFailuresByIP(const IPAddress &ipaddress);
   };


}