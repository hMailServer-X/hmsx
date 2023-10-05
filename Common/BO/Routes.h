#pragma once

#include "Collection.h"

#include "../Persistence/PersistentRoute.h"
#include "Route.h"

namespace HM
{
   class Routes : public Collection<Route, PersistentRoute>
   {
   public:
	   Routes();
	   virtual ~Routes();

      // Refreshes this collection from the database.
      void Refresh();

      std::shared_ptr<Route>  GetItemByNameWithWildcardMatch(const String &domainName);
   protected:

      virtual String GetCollectionName() const {return "Routes"; }

   };

}
