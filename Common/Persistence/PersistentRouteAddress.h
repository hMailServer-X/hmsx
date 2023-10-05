#pragma once

namespace HM
{
   class RouteAddress;
   enum PersistenceMode;

   class PersistentRouteAddress
   {
   public:
	   PersistentRouteAddress();
	   virtual ~PersistentRouteAddress();

      static bool SaveObject(std::shared_ptr<RouteAddress> pRA);
      static bool SaveObject(std::shared_ptr<RouteAddress> pRA, String &errorMessage, PersistenceMode mode);
      static bool DeleteObject(std::shared_ptr<RouteAddress> pRA);
      static bool DeleteByRoute(long long RouteID);

      static bool ReadObject(std::shared_ptr<RouteAddress> pRA, long lID);
      static bool ReadObject(std::shared_ptr<RouteAddress> pRA, std::shared_ptr<DALRecordset> pRS);


   };

}
