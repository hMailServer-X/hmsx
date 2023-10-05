#pragma once

namespace HM
{
   class GroupMember : public BusinessObject<GroupMember>
   {
   public:
      GroupMember(void);
      ~GroupMember(void);

      String GetName();

      long long GetGroupID();
      void SetGroupID(long long iNewVal);

      long long GetAccountID();
      void SetAccountID(long long iNewVal);

      bool XMLStore(XNode *pParentNode, int iOptions);
      bool XMLLoad(XNode *pParentNode, int iOptions);
      bool XMLLoadSubItems(XNode *pParentNode, int iOptions) {return true;};

   private:

      long long group_id_;
      long long account_id_;
   };
}