#pragma once

namespace HM
{
   class IMAPFolder;
   class IMAPFolders;
   class ACLPermission;
   class ACLPermissions;

   class ACLManager
   {
   public:
      ACLManager(void);
      ~ACLManager(void);
      
      std::shared_ptr<ACLPermission> GetPermissionForFolder(long long iAccountID, std::shared_ptr<IMAPFolder> pFolder);

      bool SetACL(std::shared_ptr<IMAPFolder> pFolder, const String& sIdentifier, const String &sPermissions);

	private:

      std::shared_ptr<ACLPermission> GetPermissionForAccount_(std::shared_ptr<ACLPermissions> pPermissions, long long iAccountID);
   };
}