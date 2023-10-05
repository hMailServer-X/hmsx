#pragma once

namespace HM
{

   class DistributionListRecipients;
   
   class DistributionList : public BusinessObject<DistributionList>
   {
   public:
      DistributionList(void);
      ~DistributionList(void);

      enum ListMode
      {
         LMPublic = 0,
         LMMembership = 1,
         LMAnnouncement = 2,
         LMDomainMembers = 3,
      };

      String GetName() {return address_; }

      long long GetDomainID() const {return domain_id_;}
      void SetDomainID(long long newVal) {domain_id_ = newVal;}

      String GetAddress() const {return address_;}
      void SetAddress(const String & sNewVal) {address_ = sNewVal;}

      bool GetActive() const {return enabled_;}
      void SetActive(bool bNewVal) {enabled_ = bNewVal;}

      bool GetRequireAuth() const {return require_auth_;}
      void SetRequireAuth(bool bNewVal) {require_auth_ = bNewVal;}

      String GetRequireAddress() const {return require_address_;}
      void SetRequireAddress(const String & sNewVal) {require_address_ = sNewVal;}

      ListMode GetListMode() const {return list_mode_; }
      void SetListMode(ListMode m) {list_mode_ = m; }

      bool XMLStore(XNode *pParentNode, int iOptions);
      bool XMLLoad(XNode *pParentNode, int iRestoreOptions);
      bool XMLLoadSubItems(XNode *pParentNode, int iRestoreOptions);

      std::shared_ptr<DistributionListRecipients> GetMembers() const;

      size_t GetEstimatedCachingSize();

   protected:

      String address_;
      long long domain_id_;
      bool enabled_;

      bool require_auth_;
      String require_address_;

      ListMode list_mode_;
   };
}
