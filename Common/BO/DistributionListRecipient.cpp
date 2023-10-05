#include "pch.h"
#include "distributionlistrecipient.h"

namespace HM
{
   DistributionListRecipient::DistributionListRecipient(void) :
      list_id_(0)
   {

   }

   DistributionListRecipient::~DistributionListRecipient(void)
   {
   }

   void
   DistributionListRecipient::SetAddress(const String & sAddress)
   {
      address_ = sAddress;
   }

   bool 
   DistributionListRecipient::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Recipient"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), address_);

      return true;
   }

   bool 
   DistributionListRecipient::XMLLoad(XNode *pNode, int iOptions)
   {
      address_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));

      return true;
   }
}