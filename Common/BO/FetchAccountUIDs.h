#pragma once

#include "Collection.h"
#include "FetchAccountUID.h"
#include "../Persistence/PersistentFetchAccountUID.h"

namespace HM
{
   class FetchAccountUID;

   class FetchAccountUIDs : public Collection<FetchAccountUID, PersistentFetchAccountUID>
   {
   public:
      FetchAccountUIDs(void);
      ~FetchAccountUIDs(void);

      void Refresh(long long iFAID);

      bool PreSaveObject(std::shared_ptr<FetchAccountUID> pUID, XNode *node);

   protected:
      virtual String GetCollectionName() const {return "FetchAccountUIDs"; }

   private:

      std::map<String, std::shared_ptr<FetchAccountUID> > fetched_uids_;

      long long faid_;
   };
}
