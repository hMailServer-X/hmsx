#pragma once

#include "../Common/BO/FetchAccountUID.h"

namespace HM
{
   class FetchAccountUIDList
   {
   public:
      FetchAccountUIDList(void);
      ~FetchAccountUIDList(void);

      void Refresh(long long iFAID);

      bool IsUIDInList(const String&sUID) const;
      void DeleteUID(const String &sUID);
      void DeleteUIDsNotInSet(std::set<String> &vecUIDs);
      void AddUID(const String &sUIDValue);

      std::shared_ptr<FetchAccountUID> GetUID(const String &sUID);
   private:

      std::map<String, std::shared_ptr<FetchAccountUID> > fetched_uids_;

      long long faid_;
   };
}
