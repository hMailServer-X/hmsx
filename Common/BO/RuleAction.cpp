#include "pch.h"
#include "./ruleaction.h"

namespace HM
{
   RuleAction::RuleAction(void) :
      type_(Unknown),
      rule_id_(0),
      sort_order_(0),
      route_id_(0)
   {
   }

   RuleAction::~RuleAction(void)
   {
   }

   bool 
   RuleAction::XMLStore(XNode *pRuleNode, int iOptions)
   {

      XNode *pNode = pRuleNode->AppendChild(PLATFORM_STRING("Action"));

      pNode->AppendAttr(PLATFORM_STRING("Type"), StringParser::IntToString(type_));
      pNode->AppendAttr(PLATFORM_STRING("Subject"), subject_);
      pNode->AppendAttr(PLATFORM_STRING("Body"), body_);
      pNode->AppendAttr(PLATFORM_STRING("FromAddress"), from_address_);
      pNode->AppendAttr(PLATFORM_STRING("FromName"), from_name_);
      pNode->AppendAttr(PLATFORM_STRING("IMAPFolder"), imapfolder_);
      pNode->AppendAttr(PLATFORM_STRING("FileName"), filename_);
      pNode->AppendAttr(PLATFORM_STRING("To"), to_);
      pNode->AppendAttr(PLATFORM_STRING("ScriptFunction"), script_function_);
      pNode->AppendAttr(PLATFORM_STRING("SortOrder"), StringParser::IntToString(sort_order_));
      pNode->AppendAttr(PLATFORM_STRING("Header"), header_name_);
      pNode->AppendAttr(PLATFORM_STRING("Value"), value_);
      pNode->AppendAttr(PLATFORM_STRING("RouteID"), StringParser::IntToString(route_id_));

      return true;
   }

   bool
   RuleAction::XMLLoad(XNode *pNode, int iOptions)
   {
      type_ = (RuleAction::Type) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Type")));
      subject_ = pNode->GetAttrValue(PLATFORM_STRING("Subject"));
      body_ = pNode->GetAttrValue(PLATFORM_STRING("Body"));
      from_address_ = pNode->GetAttrValue(PLATFORM_STRING("FromAddress"));
      from_name_ = pNode->GetAttrValue(PLATFORM_STRING("FromName"));
      imapfolder_ = pNode->GetAttrValue(PLATFORM_STRING("IMAPFolder"));
      filename_ = pNode->GetAttrValue(PLATFORM_STRING("FileName"));
      to_ = pNode->GetAttrValue(PLATFORM_STRING("To"));
      script_function_ = pNode->GetAttrValue(PLATFORM_STRING("ScriptFunction"));
      sort_order_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("SortOrder")));
      header_name_ = pNode->GetAttrValue(PLATFORM_STRING("Header"));
      value_ = pNode->GetAttrValue(PLATFORM_STRING("Value"));
      route_id_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("RouteID")));

      return true;
   }
}