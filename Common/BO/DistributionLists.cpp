#include "pch.h"
#include "distributionlists.h"

namespace HM
{
   DistributionLists::DistributionLists(long long iDomainID) :
      domain_id_(iDomainID)
   {

   }

   DistributionLists::~DistributionLists(void)
   {
   }

   std::shared_ptr<DistributionList>
   DistributionLists::GetItemByAddress(const String & sAddress)
   {

      for(std::shared_ptr<DistributionList> Item : vecObjects)
      {
         if (Item->GetAddress().CompareNoCase(sAddress) == 0)
            return Item;
      }

      std::shared_ptr<DistributionList> pEmpty;
      return pEmpty;
   }


   void
   DistributionLists::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_distributionlists where distributionlistdomainid = %I64d order by distributionlistaddress asc"), domain_id_);

      DBLoad_(sSQL);
   }


   bool
   DistributionLists::PreSaveObject(std::shared_ptr<DistributionList> pList, XNode *node)
   {
      pList->SetDomainID(domain_id_);

      return true;
   }
}
