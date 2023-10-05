#include "pch.h"
#include "IncomingRelays.h"

namespace HM
{
   IncomingRelays::IncomingRelays()
   {

   }

   IncomingRelays::~IncomingRelays()
   {

   }


   bool
   IncomingRelays::Refresh()
   //---------------------------------------------------------------------------
   // DESCRIPTION:
   // Refreshes the collection from the database.
   //---------------------------------------------------------------------------
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_incoming_relays order by relayname asc"));

      return DBLoad_(sSQL);
   }

   bool
   IncomingRelays::IsIncomingRelay(const IPAddress &address) const
   {
      if (vecObjects.size() == 0)
      {
         // If no security ranges exist, default is deny.
         return false;
      }

      for(std::shared_ptr<IncomingRelay> relay : vecObjects)
      {
         if (relay->IPIsWithinRange(address))
         {
            return true;
         }
      }

      return false;
   }

}
