#include "pch.h"
#include "SURBLServers.h"


namespace HM
{
   SURBLServers::SURBLServers()
   {
   }

   SURBLServers::~SURBLServers(void)
   {
   }


   void 
   SURBLServers::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all SURBL servers from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = String("select * from hm_surblservers order by surblid asc");
      DBLoad_(sSQL);
   }
}