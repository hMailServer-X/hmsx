#pragma once

namespace HM
{
   class IMAPFolders;
   class IMAPFolder;

   class FolderListCreator
   {
   public:

      FolderListCreator();
      virtual ~FolderListCreator();


      static String GetIMAPFolderList(long long iAccountID, std::shared_ptr<IMAPFolders> pStartFolders, const String &sWildcard, const String &sPrefix);
      static String GetIMAPLSUBFolderList(long long iAccountID, std::shared_ptr<IMAPFolders> pStartFolders, const String &sWildcard, const String &sPrefix);

   private:

      static String CreateFolderLine_(std::shared_ptr<IMAPFolder> currentFolder, bool bOnlySubscribed, bool hasSubFolders, String &sFullPath, const String &sWildcard, bool isSelectable, String hierarchyDelimiter);
      static void CreateIMAPFolderList_(long long iAccountID, std::shared_ptr<IMAPFolders> pStartFolders, const String &sWildcard, bool bOnlySubscribed, const String &sPrefix, std::vector<String> &vecCurrentFolder, std::vector<String> &vecMatchingFolders);

      static bool FolderWildcardMatch_(const String &sFolderName, const String &sWildcard, const String &hierarchyDelimiter_);
      static void AdjustCaseToClientCase_(String &sPath, const String &sWildcard, const String &hierarchyDelimiter);

   };


}