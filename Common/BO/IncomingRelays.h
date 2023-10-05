#pragma once

#include "Collection.h"
#include "../Persistence/PersistentIncomingRelay.h"
#include "../BO/IncomingRelay.h"

namespace HM
{
   class IncomingRelays : public Collection<IncomingRelay, PersistentIncomingRelay> 
   {
   public:
	   IncomingRelays();
	   virtual ~IncomingRelays();

      bool Refresh();

      bool IsIncomingRelay(const IPAddress &address) const;

   protected:
      virtual String GetCollectionName() const {return "IncomingRelays"; } 
   private:

   };

}