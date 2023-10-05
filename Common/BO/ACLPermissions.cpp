#include "pch.h"

#include "ACLPermissions.h"
#include "../Application/ACLManager.h"

namespace HM
{
   ACLPermissions::ACLPermissions() :
      folder_id_(0)
   {

   }

      ACLPermissions::ACLPermissions(long long iFolderID) :
      folder_id_(iFolderID)
   {

   }

   ACLPermissions::~ACLPermissions(void)
   {
   }

   void 
   ACLPermissions::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all groups form the database
   //---------------------------------------------------------------------------()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_acl where aclsharefolderid = %I64d"), folder_id_);

      DBLoad_(sSQL);
   }

   std::shared_ptr<ACLPermission> 
   ACLPermissions::GetPermissionForAccount(long long iAccountID)
   {
      auto iter = vecObjects.begin();
      auto iterEnd = vecObjects.end();

      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<ACLPermission> pPermission = (*iter);
         if (pPermission->GetPermissionType() == 0 && pPermission->GetPermissionAccountID() == iAccountID)
         {
            return pPermission;
         }
      }

      std::shared_ptr<ACLPermission> pEmpty;
      return pEmpty;
   }

   std::shared_ptr<ACLPermission> 
   ACLPermissions::GetPermissionForGroup(long long iGroupID)
   {
      auto iter = vecObjects.begin();
      auto iterEnd = vecObjects.end();

      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<ACLPermission> pPermission = (*iter);
         if (pPermission->GetPermissionType() == ACLPermission::PTGroup && pPermission->GetPermissionGroupID() == iGroupID)
         {
            return pPermission;
         }
      }

      std::shared_ptr<ACLPermission> pEmpty;
      return pEmpty;
   }

   // Called before save in DB
   bool
   ACLPermissions::PreSaveObject(std::shared_ptr<ACLPermission> pPermission, XNode *pNode)
   {
      pPermission->SetShareFolderID(folder_id_);

      return true;
   }

   bool 
   ACLPermissions::DeletePermissionsForAccount(long long iAccountID)
   {
      auto iter = vecObjects.begin();

      while (iter != vecObjects.end())
      {
         std::shared_ptr<ACLPermission> pPermission = (*iter);
         if (pPermission->GetPermissionType() == 0 && pPermission->GetPermissionAccountID() == iAccountID)
         {
            if (!PersistentACLPermission::DeleteObject(pPermission))
               return false;

            iter = vecObjects.erase(iter);
         }
         else
            iter++;
      }

      return true;
   }
}