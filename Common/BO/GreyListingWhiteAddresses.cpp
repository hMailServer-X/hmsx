#include "pch.h"
#include "GreyListingWhiteAddresses.h"

namespace HM
{
   GreyListingWhiteAddresses::GreyListingWhiteAddresses()
   {
   }

   GreyListingWhiteAddresses::~GreyListingWhiteAddresses(void)
   {
   }


   void 
   GreyListingWhiteAddresses::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all SURBL servers from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_greylisting_whiteaddresses order by whiteipaddress asc";
      DBLoad_(sSQL);
   }


}