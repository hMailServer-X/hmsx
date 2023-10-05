#pragma once

#include "Collection.h"

#include "../Persistence/PersistentAlias.h"
#include "../BO/Alias.h"

namespace HM
{
  
   class Aliases : public Collection<Alias, PersistentAlias>
   {
   public:
	   Aliases(long long iDomainID);
	   virtual ~Aliases();

      // Deletes all aliases in this collection
      void Refresh();
            
   protected:
      virtual bool PreSaveObject(std::shared_ptr<Alias> pAlias, XNode *node);
      virtual String GetCollectionName() const {return "Aliases"; }
   private:

      long long domain_id_;

   };
}
