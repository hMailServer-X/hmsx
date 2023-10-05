#pragma once

#include "Collection.h"

#include "../Persistence/PersistentRuleCriteria.h"
#include "RuleCriteria.h"

namespace HM
{
   class RuleCriterias : public Collection<RuleCriteria, PersistentRuleCriteria>
   {
   public:
      RuleCriterias(long long iRuleID);
      ~RuleCriterias(void);

      void Refresh();

      long long GetRuleID() const {return rule_id_; }

   protected:
      virtual String GetCollectionName() const {return "RuleCriterias"; }
      virtual bool PreSaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria, XNode *node);
   private:
      long long rule_id_;
   };
}