#include "pch.h"
#include "SURBLServer.h"

namespace HM
{
   SURBLServer::SURBLServer(void) :
      score_(0),
      active_(false)
   {
       
   }

   SURBLServer::~SURBLServer(void)
   {
   }

   bool 
   SURBLServer::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("SURBLServer"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), dnshost_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("RejectMessage"), reject_message_);
      pNode->AppendAttr(PLATFORM_STRING("Score"), StringParser::IntToString(score_));

      return true;
   }

   bool 
   SURBLServer::XMLLoad(XNode *pNode, int iOptions)
   {
      dnshost_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      active_ = pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1");
      reject_message_ = pNode->GetAttrValue(PLATFORM_STRING("RejectMessage"));
      score_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Score")));

      return true;
   }
}