#include "pch.h"
#include "BlockedAttachment.h"

namespace HM
{
   BlockedAttachment::BlockedAttachment(void)
   {
      
   }

   BlockedAttachment::~BlockedAttachment(void)
   {
   }

   bool 
   BlockedAttachment::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("BlockedAttachment"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), wildcard_);
      pNode->AppendAttr(PLATFORM_STRING("Description"), description_);

      return true;
   }

   bool 
   BlockedAttachment::XMLLoad(XNode *pNode, int iOptions)
   {
      wildcard_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      description_ = pNode->GetAttrValue(PLATFORM_STRING("Description"));

      return true;
   }
}