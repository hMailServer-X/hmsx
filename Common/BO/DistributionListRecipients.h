#pragma once

#include "Collection.h"

namespace HM
{
   class DistributionListRecipient;
   class PersistentDistributionListRecipient;

   class DistributionListRecipients : public Collection<DistributionListRecipient, PersistentDistributionListRecipient>
   {
   public:
      DistributionListRecipients(long long iListID);
      ~DistributionListRecipients(void);

      void Refresh();

   protected:

      virtual String GetCollectionName() const {return "DistributionList"; }
      virtual bool PreSaveObject(std::shared_ptr<DistributionListRecipient> pListRecipient, XNode *node);

   private:

      long long list_id_;
   };
}
