#pragma once

#include "Collection.h"
#include "../Persistence/PersistentRuleAction.h"
#include "RuleAction.h"

namespace HM
{
   class RuleActions : public Collection<RuleAction, PersistentRuleAction>
   {
   public:
      RuleActions(long long RuleID);
      ~RuleActions(void);
      
      void Refresh(); 

      long long GetRuleID() const {return rule_id_; }

      void MoveUp(std::shared_ptr<RuleAction> pRuleAction);
      void MoveDown(std::shared_ptr<RuleAction> pRuleAction);

   protected:
      virtual String GetCollectionName() const {return "RuleActions"; } 
      virtual bool PreSaveObject(std::shared_ptr<RuleAction> pRuleAction, XNode *node);
   private:

      std::vector<std::shared_ptr<RuleAction> >::iterator GetRuleActionIterator_(std::shared_ptr<RuleAction> pRuleAction);
      void UpdateSortOrder_();

      long long rule_id_;
   };
}