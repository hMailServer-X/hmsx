#pragma once

namespace HM
{
   class DomainAlias : public BusinessObject<DomainAlias>
   {
   public:
      DomainAlias(void);
      ~DomainAlias(void);

      String GetName() const {return alias_; }

      long long GetDomainID() const {return domain_id_; }
      void SetDomainID(long long newval) {domain_id_ = newval; }

      String GetAlias() const {return alias_; }
      void SetAlias(const String &newval) {alias_ = newval; }

      bool XMLStore(XNode *pParentNode, int iOptions);
      bool XMLLoad(XNode *pAliasNode, int iOptions);
      bool XMLLoadSubItems(XNode *pAliasNode, int iOptions) {return true;};

   private:
      
      long long domain_id_;
      String alias_;
   };
}