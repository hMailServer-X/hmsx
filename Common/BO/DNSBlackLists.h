#pragma once

#include "Collection.h"

#include "DNSBlackList.h"
#include "../Persistence/PersistentDNSBlackList.h"

namespace HM
{

   class DNSBlackLists : public Collection<DNSBlackList, PersistentDNSBlackList>
   {
   public:
      DNSBlackLists();
      ~DNSBlackLists(void);

      // Refreshes this collection from the database.
      void Refresh();

      virtual String GetCollectionName() const {return "DNSBlackLists"; }

   private:
      
   };
}