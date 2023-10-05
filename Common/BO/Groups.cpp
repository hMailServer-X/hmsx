#include "pch.h"
#include "Groups.h"
#include "../Persistence/PersistentGroup.h"


namespace HM
{
   Groups::Groups()
   {
      
   }

   Groups::~Groups(void)
   {
   }

   void 
   Groups::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all groups form the database
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_groups order by groupname asc";

      DBLoad_(sSQL);
   }
}