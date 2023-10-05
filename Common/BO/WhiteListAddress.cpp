#include "pch.h"
#include "WhiteListAddress.h"

namespace HM
{
   WhiteListAddress::WhiteListAddress(void)
   {
      
   }

   WhiteListAddress::~WhiteListAddress(void)
   {
   }
   
   String
   WhiteListAddress::GetName() const
   {  
      String sName = white_lower_ipaddress_.ToString() + white_upper_ipaddress_.ToString();
      return sName;
   }

   bool 
   WhiteListAddress::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("WhiteAddress"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), GetName());
      pNode->AppendAttr(PLATFORM_STRING("LowerIPAddress"), String(white_lower_ipaddress_.ToString()));
      pNode->AppendAttr(PLATFORM_STRING("UpperIPAddress"), String(white_upper_ipaddress_.ToString()));
      pNode->AppendAttr(PLATFORM_STRING("EMailAddress"), white_email_address_);
      pNode->AppendAttr(PLATFORM_STRING("Description"), white_description_);

      return true;

      
   }

   bool 
   WhiteListAddress::XMLLoad(XNode *pNode, int iOptions)
   {
      white_lower_ipaddress_.TryParse(pNode->GetAttrValue(PLATFORM_STRING("LowerIPAddress")));
      white_upper_ipaddress_.TryParse(pNode->GetAttrValue(PLATFORM_STRING("UpperIPAddress")));
      white_email_address_ = pNode->GetAttrValue(PLATFORM_STRING("EMailAddress"));
      white_description_ = pNode->GetAttrValue(PLATFORM_STRING("Description"));

      return true;
   }

   bool
   WhiteListAddress::SetLowerIPAddress(const String &iIPAddress)
   {
      return white_lower_ipaddress_.TryParse(iIPAddress);
   }

   bool
   WhiteListAddress::SetUpperIPAddress(const String &iIPAddress)
   {
      return white_upper_ipaddress_.TryParse(iIPAddress);
   }
}
