#pragma once

#include "Collection.h"

#include "../Persistence/PersistentSecurityRange.h"
#include "../BO/SecurityRange.h"

namespace HM
{
   class SecurityRanges : public Collection<SecurityRange, PersistentSecurityRange> 
   {
   public:
	   SecurityRanges();
	   virtual ~SecurityRanges();

      void Refresh();

      void SetDefault();

   protected:
      virtual String GetCollectionName() const {return "SecurityRanges"; } 
   private:

   };

}