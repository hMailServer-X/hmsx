#pragma once

#include "Collection.h"
#include "../Persistence/PersistentDomainAlias.h"
#include "DomainAlias.h"

namespace HM
{
   class DomainAliases : public Collection<DomainAlias, PersistentDomainAlias> 
   {
   public:
      DomainAliases(long long iDomainID);
      ~DomainAliases(void);

      void Refresh();

      String ApplyAliasesOnAddress(const String &sAddress);
      long long GetDomainID() {return domain_id_; }

   protected:
      virtual bool PreSaveObject(std::shared_ptr<DomainAlias> pDA, XNode *node);
      virtual String GetCollectionName() const {return "DomainAliases"; }
   private:

      long long domain_id_;
   };
}