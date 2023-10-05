#include "pch.h"
#include "SecurityRanges.h"

namespace HM
{
   SecurityRanges::SecurityRanges()
   {

   }

   SecurityRanges::~SecurityRanges()
   {

   }


   void
   SecurityRanges::Refresh()
   //---------------------------------------------------------------------------
   // DESCRIPTION:
   // Refreshes the collection from the database.
   //---------------------------------------------------------------------------
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_securityranges order by rangeexpires asc, rangepriorityid desc, rangename asc"));

      DBLoad_(sSQL);

      return;
   }
   void
   SecurityRanges::SetDefault()
   //---------------------------------------------------------------------------
   // DESCRIPTION:
   // Reverts back to the default IP ranges
   //---------------------------------------------------------------------------
   {
      Refresh();

      // Delete all existing ports and then add new ones.
      DeleteAll();

      std::shared_ptr<SecurityRange> pSecurityRange = std::shared_ptr<SecurityRange>(new SecurityRange);
      pSecurityRange->SetName("My computer");
      pSecurityRange->SetPriority(30);
      pSecurityRange->SetLowerIPString("127.0.0.1");
      pSecurityRange->SetUpperIPString("127.0.0.1");
      pSecurityRange->SetOptions(71627);
      PersistentSecurityRange::SaveObject(pSecurityRange);

      pSecurityRange = std::shared_ptr<SecurityRange>(new SecurityRange);
      pSecurityRange->SetName("Internet");
      pSecurityRange->SetPriority(10);
      pSecurityRange->SetLowerIPString("0.0.0.0");
      pSecurityRange->SetUpperIPString("255.255.255.255");
      pSecurityRange->SetOptions(96203);
      PersistentSecurityRange::SaveObject(pSecurityRange);

      Refresh();

      return;
   }
}

