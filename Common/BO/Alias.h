#pragma once

namespace HM
{
   class Alias : public BusinessObject<Alias>
   {
   public:
	   Alias();
	   virtual ~Alias();

      long long GetDomainID() const { return domain_id_; }
      String GetName() const { return name_; }
      String GetValue() const { return value_; }
      bool GetIsActive() const { return active_; }

      void SetDomainID(long long newVal) { domain_id_ = newVal; }
      void SetName(const String & newVal) {  name_ = newVal; }
      void SetValue(const String & newVal) { value_ = newVal; }
      void SetIsActive(bool newVal) { active_ = newVal; }

      bool XMLStore(XNode *pParentNode, int iOptions);     
      bool XMLLoad(XNode *pNode, int iOptions);
      bool XMLLoadSubItems(XNode *pNode, int iOptions) {return true; }

      size_t GetEstimatedCachingSize();

   protected:

      long long domain_id_;
      String name_;
      String value_;
      bool active_;


   };
}
