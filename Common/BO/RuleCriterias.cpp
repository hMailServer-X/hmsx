#include "pch.h"

#include "RuleCriterias.h"
#include "RuleCriteria.h"
#include "../Persistence/PersistentRuleCriteria.h"

namespace HM
{
   RuleCriterias::RuleCriterias(long long iRuleID) :
      rule_id_(iRuleID)
   {
   }

   RuleCriterias::~RuleCriterias(void)
   {

   }

   void 
   RuleCriterias::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_rule_criterias where criteriaruleid = %I64d order by criteriaid asc"), rule_id_);

      DBLoad_(sSQL);
   }


   bool
   RuleCriterias::PreSaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria, XNode *node)
   {
      pRuleCriteria->SetRuleID(rule_id_);
      return true;
   }   
}