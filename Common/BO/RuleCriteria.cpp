#include "pch.h"
#include "./rulecriteria.h"

namespace HM
{
   RuleCriteria::RuleCriteria(void) :
      field_type_(FTFrom),
      match_type_(Equals),
      rule_id_(0),
      use_predefined_field_(true)
   {
   }

   RuleCriteria::~RuleCriteria(void)
   {
   }

   bool 
   RuleCriteria::XMLStore(XNode *pRuleNode, int iOptions)
   {
      XNode *pNode = pRuleNode->AppendChild(PLATFORM_STRING("Criteria"));

      pNode->AppendAttr(PLATFORM_STRING("MatchString"), match_string_);
      pNode->AppendAttr(PLATFORM_STRING("FieldType"), StringParser::IntToString(field_type_));
      pNode->AppendAttr(PLATFORM_STRING("MatchType"), StringParser::IntToString(match_type_));
      pNode->AppendAttr(PLATFORM_STRING("HeaderField"), header_field_);
      pNode->AppendAttr(PLATFORM_STRING("UsePredefinedField"), use_predefined_field_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));

      return true;
   }

   bool
   RuleCriteria::XMLLoad(XNode *pNode, int iOptions)
   {
      match_string_ = pNode->GetAttrValue(PLATFORM_STRING("MatchString"));
      field_type_ = (PredefinedField) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("FieldType")));
      match_type_ = (MatchType) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MatchType")));
      header_field_ = pNode->GetAttrValue(PLATFORM_STRING("HeaderField"));
      use_predefined_field_ = (pNode->GetAttrValue(PLATFORM_STRING("UsePredefinedField")) == PLATFORM_STRING("1"));

      return true;
   }

}