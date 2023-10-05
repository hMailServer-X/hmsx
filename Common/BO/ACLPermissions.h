#pragma once

#include "Collection.h"

#include "ACLPermission.h"
#include "../Persistence/PersistentACLPermission.h"

namespace HM
{
   class ACLPermissions : public Collection<ACLPermission, PersistentACLPermission>
   {
   public:
      ACLPermissions();
      ACLPermissions(long long iFolderID);
      ~ACLPermissions(void);

      // Refreshes this collection from the database.
      void Refresh();

      std::shared_ptr<ACLPermission> GetPermissionForAccount(long long iAccountID);
      std::shared_ptr<ACLPermission> GetPermissionForGroup(long long iGroupID);
      bool DeletePermissionsForAccount(long long iAccountID);

      bool PreSaveObject(std::shared_ptr<ACLPermission> pPermission, XNode *pNode);
   protected:
      
      virtual String GetCollectionName() const {return "ACLs"; }

   private:
 
      long long folder_id_;
   };
}