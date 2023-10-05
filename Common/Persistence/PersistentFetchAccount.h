#pragma once

namespace HM
{
   class FetchAccount;
   class FetchAccountUIDs;
   enum PersistenceMode;

   class PersistentFetchAccount
   {
   public:
      PersistentFetchAccount(void);
      ~PersistentFetchAccount(void);

      static void Lock(long long ID);
      static void Unlock(long long ID);
      static void UnlockAll();
		static bool IsLocked(long long ID);
      static bool ReadObject(std::shared_ptr<FetchAccount> pFA, const SQLCommand& command);
      static bool ReadObject(std::shared_ptr<FetchAccount> oFA, std::shared_ptr<DALRecordset> pRS);
      static bool SaveObject(std::shared_ptr<FetchAccount> oFA, String &errorMessage,PersistenceMode mode);
      static bool SaveObject(std::shared_ptr<FetchAccount> oFA);
      static bool DeleteObject(std::shared_ptr<FetchAccount> pFA);
      static void DeleteByAccountID(long long ID);

      static void SetRetryNow(long long iFAID);
      static void SetNextTryTime(std::shared_ptr<FetchAccount> pFA);
   };
}