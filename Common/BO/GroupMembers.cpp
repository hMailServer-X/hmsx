#include "pch.h"

#include "GroupMembers.h"
#include "../BO/Account.h"
#include "../Cache/CacheContainer.h"
#include "../Persistence/PersistentGroupMember.h"
#include "../Persistence/PersistentAccount.h"

namespace HM
{
   GroupMembers::GroupMembers(long long iGroupID) :
      group_id_(iGroupID)
   {

   }

   GroupMembers::~GroupMembers(void)
   {
   }

   void 
   GroupMembers::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all group members from the database
   //---------------------------------------------------------------------------()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_group_members where membergroupid = %I64d order by memberid asc"), group_id_);

      DBLoad_(sSQL);      
   }

   bool 
   GroupMembers::UserIsMember(long long iAccountID)
   {
      auto iter = vecObjects.begin();
      auto iterEnd = vecObjects.end();

      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<GroupMember> pMember = (*iter);

         if (pMember->GetAccountID() == iAccountID)
            return true;
      }

      return false;
   }

   void 
   GroupMembers::PostStoreObject(std::shared_ptr<GroupMember> pGroupMember, XNode *pChildNode)
   {
      std::shared_ptr<const Account> pAccount = CacheContainer::Instance()->GetAccount(pGroupMember->GetAccountID());
      if (!pAccount)
         return;

      String sAddress = pAccount->GetAddress();

      pChildNode->AppendAttr(PLATFORM_STRING("Name"), sAddress);
   }

   bool
   GroupMembers::PreSaveObject(std::shared_ptr<GroupMember> pGroupMember, XNode *pNode)
   {
      String sAddress = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      std::shared_ptr<const Account> pAccount = CacheContainer::Instance()->GetAccount(sAddress);

      if (!pAccount)
      {
         // The group member is connected to an account which no longer exists.
         return false;
      }

      pGroupMember->SetGroupID(group_id_);
      pGroupMember->SetAccountID(pAccount->GetID());

      return true;
   }

}