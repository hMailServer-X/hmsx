#include "pch.h"
#include "IncomingRelay.h"

namespace HM
{

   IncomingRelay::IncomingRelay()
   {

   }

   IncomingRelay::~IncomingRelay()
   {

   }

   String 
   IncomingRelay::GetLowerIPString() const 
   {
	   return lower_ip_.ToString();
   }

   bool
   IncomingRelay::SetLowerIPString(const String & sValue)
   {
      return lower_ip_.TryParse(sValue);
   }

   String 
   IncomingRelay::GetUpperIPString() const 
   {
	   return upper_ip_.ToString();
   }


   bool
   IncomingRelay::SetUpperIPString(const String & sValue)
   {
      return upper_ip_.TryParse(sValue);
   }

   bool
   IncomingRelay::IPIsWithinRange(const IPAddress &address) const
   {  
      if (address.GetAddress1() >= lower_ip_.GetAddress1() && address.GetAddress1() <= upper_ip_.GetAddress1())
      {
         if (address.GetType() == IPAddress::IPV4)
            return true;

         if (address.GetAddress2() >= lower_ip_.GetAddress2() && address.GetAddress2() <= upper_ip_.GetAddress2())
            return true;
      }

      return false;
   }

   bool 
   IncomingRelay::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("IncomingRelay"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("LowerIP"), String(lower_ip_.ToString()));
      pNode->AppendAttr(PLATFORM_STRING("UpperIP"), String(upper_ip_.ToString()));

      return true;
   }

   bool 
   IncomingRelay::XMLLoad(XNode *pIncomingRelayNode, int iOptions)
   {
      name_ = pIncomingRelayNode->GetAttrValue(PLATFORM_STRING("Name"));
      
      lower_ip_.TryParse(pIncomingRelayNode->GetAttrValue(PLATFORM_STRING("LowerIP")));
      upper_ip_.TryParse(pIncomingRelayNode->GetAttrValue(PLATFORM_STRING("UpperIP")));

      return true;
   }
}