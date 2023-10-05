#include "pch.h"
#include "WhiteListAddresses.h"

namespace HM
{
   WhiteListAddresses::WhiteListAddresses()
   {
   }

   WhiteListAddresses::~WhiteListAddresses(void)
   {
   }


   void 
   WhiteListAddresses::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all SURBL servers from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_whitelist order by whiteloweripaddress1 asc, whiteloweripaddress2 asc";
      DBLoad_(sSQL);
   }



}