#include "pch.h"
#include "distributionlist.h"

#include "DistributionListRecipients.h"
#include "../Persistence/PersistentDistributionListRecipient.h"

namespace HM
{
   DistributionList::DistributionList(void) :
      domain_id_(false),
      require_auth_(false),
      list_mode_(LMPublic),
      enabled_(false)
   {
      
   }

   DistributionList::~DistributionList(void)
   {
   }

   bool 
   DistributionList::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("DistributionList"));

      String sListMode;
      sListMode.Format(PLATFORM_STRING("%d"), list_mode_);

      pNode->AppendAttr(PLATFORM_STRING("Name"), address_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), enabled_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("RequiresAuth"), require_auth_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("RequiresAuthAddress"), require_address_);
      pNode->AppendAttr(PLATFORM_STRING("ListMode"), sListMode);

      return GetMembers()->XMLStore(pNode, iOptions);
   }

   bool
   DistributionList::XMLLoad(XNode *pNode, int iRestoreOptions)
   {
      address_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      enabled_ = pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1");
      require_auth_ = pNode->GetAttrValue(PLATFORM_STRING("RequiresAuth")) == PLATFORM_STRING("1");
      require_address_ = pNode->GetAttrValue(PLATFORM_STRING("RequiresAuthAddress"));
      list_mode_ = (ListMode) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("ListMode")));

      return true;
   }

   bool
   DistributionList::XMLLoadSubItems(XNode *pNode, int iRestoreOptions)
   {
      std::shared_ptr<DistributionListRecipients> pDistListRecipients = GetMembers();
      return pDistListRecipients->XMLLoad(pNode, iRestoreOptions);
   }

   std::shared_ptr<DistributionListRecipients>
   DistributionList::GetMembers() const
   {
      std::shared_ptr<DistributionListRecipients> members = std::shared_ptr<DistributionListRecipients> (new DistributionListRecipients(id_)) ;
      members->Refresh();
      return members;
   }

   size_t
   DistributionList::GetEstimatedCachingSize()
   {
      return 1024;
   }

}
