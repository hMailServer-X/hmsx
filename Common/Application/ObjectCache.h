#pragma once

namespace HM
{
   class DomainAliases;
   class Rules;

   class ObjectCache : public Singleton<ObjectCache>
   {
   public:
      ObjectCache(void);
      ~ObjectCache(void);

      void SetDomainAliasesNeedsReload();
      std::shared_ptr<DomainAliases> GetDomainAliases();

      void SetGlobalRulesNeedsReload();
      std::shared_ptr<Rules> GetGlobalRules();

      void SetAccountRulesNeedsReload(long long iAccountID);
      std::shared_ptr<Rules> GetAccountRules(long long iAccountID);

      void ClearRuleCaches();

   private:

      std::shared_ptr<DomainAliases> domain_aliases_;
      bool domain_aliases_needs_reload_;

      std::shared_ptr<Rules> global_rules_;
      bool global_rules_needs_reload_;

      std::map<long long, std::shared_ptr<Rules> > account_rules_;
      std::set<long long> account_rules_to_refresh_;

      boost::recursive_mutex domain_aliases_mutex_;
      boost::recursive_mutex global_rules_mutex_;
      boost::recursive_mutex account_rules_mutex_;

   };
}