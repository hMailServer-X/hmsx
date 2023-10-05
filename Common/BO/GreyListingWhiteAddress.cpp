#include "pch.h"
#include "GreyListingWhiteAddress.h"

namespace HM
{
   GreyListingWhiteAddress::GreyListingWhiteAddress(void) 
   {
      
   }

   GreyListingWhiteAddress::~GreyListingWhiteAddress(void)
   {
   }

   
   String
   GreyListingWhiteAddress::GetName() const
   {  
      return white_ipaddress_;
   }

   bool 
   GreyListingWhiteAddress::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("WhiteAddress"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), GetName());
      pNode->AppendAttr(PLATFORM_STRING("WhiteIPDescription"), white_ipdescription_);

      return true;
   }

   bool 
   GreyListingWhiteAddress::XMLLoad(XNode *pNode, int iOptions)
   {
      white_ipaddress_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      white_ipdescription_ = pNode->GetAttrValue(PLATFORM_STRING("WhiteIPDescription"));

      return true;
   }

   String 
   GreyListingWhiteAddress::GetIPAddress() const
   {
      return white_ipaddress_;
   }


   void
   GreyListingWhiteAddress::SetIPAddress(const String &sIPAddress)
   {
      white_ipaddress_ = sIPAddress;
   }

   String 
   GreyListingWhiteAddress::GetUserEditableIPAddress() const
   {
      return SQLStatement::ConvertLikeToWildcard(white_ipaddress_);
   }


   void
   GreyListingWhiteAddress::SetUserEditableIPAddress(const String &sIPAddress)
   {
      white_ipaddress_ = SQLStatement::ConvertWildcardToLike(sIPAddress);
   }
}
