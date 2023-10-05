#pragma once

namespace HM
{

   class IMAPFolder;
   class ACL;
   enum PersistenceMode;

   class PersistentIMAPFolder
   {
   private:
	   PersistentIMAPFolder();
	   virtual ~PersistentIMAPFolder();
   public:

      static bool DeleteObject(std::shared_ptr<IMAPFolder> pFolder);
      static bool DeleteObject(std::shared_ptr<IMAPFolder> pFolder, bool forceDelete);
      static bool SaveObject(std::shared_ptr<IMAPFolder> pFolder, String &errorMessage, PersistenceMode mode);
      static bool SaveObject(std::shared_ptr<IMAPFolder> pFolder);
      static bool DeleteByAccount(long long iAccountID);

      static bool GetExistsFolderContainingCharacter(String theChar);

      static unsigned int GetUniqueMessageID(long long accountID, long long folderID);

      static long long GetUserInboxFolder(long long accountID);

   private:

      static bool IncreaseCurrentUID_(long long folderID);
      static unsigned int GetCurrentUID_(long long folderID);


   };
}
