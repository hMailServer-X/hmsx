#include "pch.h"
#include "Domains.h"

namespace HM
{
   Domains::Domains()
   {
      
   }

   Domains::~Domains()
   {
   
   }

   void
   Domains::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all domains from the database
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_domains order by domainname asc";
      DBLoad_(sSQL);
   }

   void 
   Domains::Refresh(long long iDomainID)
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads a specific domain from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_domains where domainid = %I64d"), iDomainID);

      DBLoad_(sSQL);
   }

   String 
   Domains::GetNames()
   {
      bool first = true;
      String result;
      for(std::shared_ptr<Domain> domain : vecObjects)
      {
         if (first)
            first = false;

         String append;
         append.Format(PLATFORM_STRING("%I64d\t%s\t%d\r\n"), domain->GetID(), domain->GetName().c_str(), domain->GetIsActive() ? 1 : 0);

         result += append;
      }

      return result;
   }
}
