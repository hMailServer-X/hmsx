#pragma once

#include "Collection.h"
#include "../Persistence/PersistentGroupMember.h"
#include "GroupMember.h"

namespace HM
{
   class GroupMembers : public Collection<GroupMember, PersistentGroupMember>
   {
   public:
      GroupMembers(long long iGroupID);
      ~GroupMembers(void);

      // Refreshes this collection from the database.
      void Refresh();

      long long GetGroupID() {return group_id_; }
      bool UserIsMember(long long iAccountID);

   protected:

      virtual String GetCollectionName() const {return "GroupMembers"; }

      void PostStoreObject(std::shared_ptr<GroupMember> pGroupMember, XNode *pChildNode);
      bool PreSaveObject(std::shared_ptr<GroupMember> pGroupMember, XNode *pNode);

   private:
 
      long long group_id_;
   };
}