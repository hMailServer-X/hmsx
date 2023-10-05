#include "pch.h"
#include "Routes.h"

namespace HM
{
   Routes::Routes()
   {
      
   }

   Routes::~Routes()
   {

   }

   void 
   Routes::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reloads all routes from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_routes order by routedomainname asc";
      DBLoad_(sSQL);
   }

   std::shared_ptr<Route> 
   Routes::GetItemByNameWithWildcardMatch(const String &domainName)
   {
      auto iter = vecObjects.begin();
      auto iterEnd = vecObjects.end();

      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<Route> pRoute = (*iter);

         if (StringParser::WildcardMatchNoCase(pRoute->DomainName(), domainName))
         {
            return pRoute;
         }
      }

      std::shared_ptr<Route> empty;
      return empty;
   }

}
