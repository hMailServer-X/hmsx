#pragma once

namespace HM
{
   class ACL;
   class IMAPFolders;
   class IMAPFolder;

   class IMAPFolderContainer : public Singleton<IMAPFolderContainer>
   {
   public:
	   IMAPFolderContainer();
	   virtual ~IMAPFolderContainer();

      std::shared_ptr<HM::IMAPFolders> GetFoldersForAccount(long long AccountID);
      // Returns a list of all folders for the specified account.

      std::shared_ptr<HM::IMAPFolders> GetPublicFolders();

      void UncacheAccount(long long iAccountID);

      void UpdateCurrentUID(long long accountID, long long folderID, unsigned int currentUID);

      bool Clear();

      static bool IsPublicFolder(const std::vector<String> &vecFolderPath);

      static std::shared_ptr<IMAPFolder> GetTopMostExistingFolder(std::shared_ptr<IMAPFolders> pContainer, const std::vector<String> &vecFolderPath);

   private:

      std::map<long long, std::shared_ptr<IMAPFolders> > folders_;
      
      static boost::recursive_mutex fetch_list_mutex_;
   };
}
