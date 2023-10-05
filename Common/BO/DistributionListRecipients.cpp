#include "pch.h"
#include "distributionlistrecipients.h"

#include "../Persistence/PersistentDistributionListRecipient.h"

namespace HM
{
   DistributionListRecipients::DistributionListRecipients(long long iListID) :
      list_id_(iListID)   
   {

   }

   DistributionListRecipients::~DistributionListRecipients(void)
   {

   }

   void
   DistributionListRecipients::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_distributionlistsrecipients where distributionlistrecipientlistid = %I64d order by distributionlistrecipientaddress asc "), list_id_);
     
      DBLoad_(sSQL);
   }

   bool
   DistributionListRecipients::PreSaveObject(std::shared_ptr<DistributionListRecipient> pListRecipient, XNode *node)
   {
      pListRecipient->SetListID(list_id_);

      return true;
   }
}
