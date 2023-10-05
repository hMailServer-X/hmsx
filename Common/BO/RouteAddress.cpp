#include "pch.h"
#include "RouteAddress.h"

namespace HM
{
   RouteAddress::RouteAddress()
   {
      route_id_ = 0;
   }

   RouteAddress::~RouteAddress()
   {

   }

   bool 
   RouteAddress::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("RouteAddress"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), address_);

      return true;
   }

   bool 
   RouteAddress::XMLLoad(XNode *pNode, int iOptions)
   {
      address_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));

      return true;
   }

}
