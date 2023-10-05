#pragma once

#include "Collection.h"
#include "../Persistence/PersistentDomain.h"
#include "Domain.h"

namespace HM
{
   class Domains : public Collection<Domain, PersistentDomain>
   {
   public:
	   Domains();
	   virtual ~Domains();

      void Refresh();
      void Refresh(long long iDomainID);
      String GetNames();

   protected:
      virtual String GetCollectionName() const {return "Domains"; }
   private:

   };
}
