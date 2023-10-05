 #pragma once

namespace HM
{
   class DistributionListRecipient : public BusinessObject<DistributionListRecipient>
   {
   public:
      DistributionListRecipient(void);
      ~DistributionListRecipient(void);

      String GetName() const {return address_; }

      void SetAddress(const String & sAddress);
      String GetAddress(void) const {return address_;}

      long long GetListID() const  {return list_id_;}
      void SetListID(long long newVal) {list_id_ = newVal; }


      bool XMLStore(XNode *pParentNode, int iOptions);
      bool XMLLoad(XNode *pParentNode, int iOptions);
      bool XMLLoadSubItems(XNode *pParentNode, int iOptions) {return true; }

   protected:

      String address_;
      long long list_id_;
   };
}
