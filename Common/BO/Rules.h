#pragma once

#include "Collection.h"

#include "../Persistence/PersistentRule.h"
#include "Rule.h"

namespace HM
{
   class Rules : public Collection<Rule, PersistentRule>
   {
   public:
      Rules(long long iAccountID);
      ~Rules(void);

      void Refresh();

      long long GetAccountID() const {return account_id_; }
 
      void MoveUp(long long iRuleID);
      void MoveDown(long long iRuleID);

   protected:
      virtual String GetCollectionName() const {return "Rules"; }
      virtual bool PreSaveObject(std::shared_ptr<Rule> pRule, XNode *node);
   private:
      
      std::vector<std::shared_ptr<Rule> >::iterator GetRuleIterator_(long long iRuleID);
      void UpdateSortOrder_();

      long long account_id_;
   };
}