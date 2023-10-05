#pragma once

namespace HM
{
   class RuleCriteria;
   enum PersistenceMode;

   class PersistentRuleCriteria
   {
   public:
      PersistentRuleCriteria(void);
      ~PersistentRuleCriteria(void);

      static bool ReadObject(std::shared_ptr<RuleCriteria> pRuleCriteria, const SQLCommand &sSQL);
      static bool ReadObject(std::shared_ptr<RuleCriteria> pRuleCriteria, std::shared_ptr<DALRecordset> pRS);

      
      static bool SaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria, String &errorMessage, PersistenceMode mode);
      static bool SaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria);
      static bool DeleteObject(std::shared_ptr<RuleCriteria> pRuleCriteria);

      static bool DeleteObjects(long long iRuleID);
   };
}