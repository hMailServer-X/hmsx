#include "Collection.h"
#include "../Persistence/PersistentRouteAddress.h"
#include "RouteAddress.h"

namespace HM
{
   class RouteAddresses : public Collection<RouteAddress, PersistentRouteAddress>
   {
   public:
	   RouteAddresses(long long iRouteID);
	   virtual ~RouteAddresses();

      void Refresh();

      void DeleteByAddress(const String &sAddress);

      long long GetRouteID() {return route_id_; }
      
   protected:
      virtual String GetCollectionName() const {return "RouteAddresses"; }
      bool PreSaveObject(std::shared_ptr<RouteAddress> routeAddress, XNode *node);

   private:
      long long route_id_;
   };

}
