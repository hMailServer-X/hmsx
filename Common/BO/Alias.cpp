#include "pch.h"

#include "Alias.h"

namespace HM
{
   Alias::Alias() :
      domain_id_(0),
      active_(false)
   {

   }

   Alias::~Alias()
   {

   }

   bool 
   Alias::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Alias"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("Value"), value_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));

      return true;
   }

   bool
   Alias::XMLLoad(XNode *pNode, int iOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      value_ = pNode->GetAttrValue(PLATFORM_STRING("Value"));
      active_ = (pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1"));

      return true;
   }


   size_t
   Alias::GetEstimatedCachingSize()
   {
      return 1024;
   }
}
