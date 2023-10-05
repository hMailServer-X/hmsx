#include "pch.h"
#include "DNSBlackList.h"

namespace HM
{
   DNSBlackList::DNSBlackList(void) :
      score_(0),
      active_(false)
   {
      
   }

   DNSBlackList::~DNSBlackList(void)
   {
   }

   bool 
   DNSBlackList::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("DNSBlackList"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), dnshost_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("RejectMessage"), reject_message_);
      pNode->AppendAttr(PLATFORM_STRING("ExpectedResult"), expected_result_);
      pNode->AppendAttr(PLATFORM_STRING("Score"), StringParser::IntToString(score_));

      return true;
   }

   bool 
   DNSBlackList::XMLLoad(XNode *pNode, int iOptions)
   {
      dnshost_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      active_ = pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1");
      reject_message_ = pNode->GetAttrValue(PLATFORM_STRING("RejectMessage"));
      expected_result_ = pNode->GetAttrValue(PLATFORM_STRING("ExpectedResult"));
      score_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Score")));

      return true;

   }
}