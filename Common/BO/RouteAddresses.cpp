#include "pch.h"
#include "RouteAddresses.h"

namespace HM
{
   RouteAddresses::RouteAddresses(long long iRouteID) :
      route_id_(iRouteID)
   {
      
   }

   RouteAddresses::~RouteAddresses()
   {

   }

   void 
   RouteAddresses::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_routeaddresses where routeaddressrouteid = %I64d"), route_id_);;

      DBLoad_(sSQL);
   }

   void
   RouteAddresses::DeleteByAddress(const String &sAddress)
   {
      auto iterRoute = vecObjects.begin();

      while (iterRoute != vecObjects.end())
      {  
         std::shared_ptr<RouteAddress> pRoute = (*iterRoute);

         if (pRoute->GetAddress().CompareNoCase(sAddress) == 0)
         {
            PersistentRouteAddress::DeleteObject(pRoute);
            vecObjects.erase(iterRoute);
            return;
         }

         iterRoute++;
      }
   }

   bool
   RouteAddresses::PreSaveObject(std::shared_ptr<RouteAddress> routeAddress, XNode *node)
   {
      routeAddress->SetRouteID(route_id_);

      return true;
   }

}
