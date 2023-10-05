#include "pch.h"
#include "Rule.h"
#include "RuleActions.h"
#include "RuleAction.h"
#include "../Persistence/PersistentRuleAction.h"
#include "RuleCriterias.h"
#include "RuleCriteria.h"
#include "../Persistence/PersistentRuleCriteria.h"

namespace HM
{
   Rule::Rule(void) :
      active_(true),
      account_id_(0),
      use_and_(true),
      sort_order_(0)
   {

   }

   Rule::~Rule(void)
   {

   }

   std::shared_ptr<RuleCriterias>
   Rule::GetCriterias()
   {
      if (!criterias_)
      {
         criterias_ = std::shared_ptr<RuleCriterias>(new RuleCriterias(id_));
         criterias_->Refresh();
      }

      return criterias_;
   }

   std::shared_ptr<RuleActions>
   Rule::GetActions()
   {
      if (!actions_)
      {
         actions_ = std::shared_ptr<RuleActions>(new RuleActions(id_));
         actions_->Refresh();
      }

      return actions_;
   }

   bool
   Rule::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Rule"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("UseAND"), use_and_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("SortOrder"), StringParser::IntToString(sort_order_));
   
      GetCriterias()->XMLStore(pNode, iOptions);
      GetActions()->XMLStore(pNode, iOptions);

      return true;
   }

   bool
   Rule::XMLLoad(XNode *pNode, int iOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      active_ = (pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1"));
      use_and_ = (pNode->GetAttrValue(PLATFORM_STRING("UseAND")) == PLATFORM_STRING("1"));
      sort_order_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("SortOrder")));

      return true;
   }

   bool
   Rule::XMLLoadSubItems(XNode *pNode, int iOptions)
   {
      if (GetCriterias()->GetCount() == 0)
         if (!GetCriterias()->XMLLoad(pNode, iOptions))
            return false;

      if (GetActions()->GetCount() == 0)
         if (!GetActions()->XMLLoad(pNode, iOptions))
            return false;

      return true;
   }
}