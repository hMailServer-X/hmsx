#pragma once

namespace HM
{
   class FetchAccountUID;
   enum PersistenceMode;

   class PersistentFetchAccountUID
   {
   public:
      PersistentFetchAccountUID(void);
      ~PersistentFetchAccountUID(void);

      static long long AddUID(long long iFAID, const String &sValue);
      static bool DeleteUID(long long iUIDID);
      
      static bool SaveObject(std::shared_ptr<FetchAccountUID> pUID, String &result, PersistenceMode mode);
      static bool DeleteObject(std::shared_ptr<FetchAccountUID> fetchAccountUID);
   };
}