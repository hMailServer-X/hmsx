#pragma once

namespace HM
{
   class GreyListTriplet;

   class PersistentGreyList
   {
   public:
      PersistentGreyList(void);
      ~PersistentGreyList(void);

      static std::shared_ptr<GreyListTriplet> GetRecord(const String &sSenderAddress, const String &sRecipientAddress, const IPAddress &remoteIP);
      static bool AddObject(std::shared_ptr<GreyListTriplet> pTriplet);

      static bool ResetDeletionTime(std::shared_ptr<GreyListTriplet> pTriplet);

      static void IncreaseBlocked(long long iTripletID);
      static void ClearExpiredRecords();
      static void ClearAllRecords();
   private:

   };
}