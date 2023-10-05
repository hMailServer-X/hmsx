#include "pch.h"
#include "./domainalias.h"

namespace HM
{
   DomainAlias::DomainAlias(void) :
      domain_id_(0)
   {

   }

   DomainAlias::~DomainAlias(void)
   {

   }

   bool 
   DomainAlias::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("DomainAlias"));
      pNode->AppendAttr(PLATFORM_STRING("Name"), alias_);

      return true;

   }

   bool 
   DomainAlias::XMLLoad(XNode *pAliasNode, int iOptions)
   {
      alias_ = pAliasNode->GetAttrValue(PLATFORM_STRING("Name"));

      return true;
   }

}