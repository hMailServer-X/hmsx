#pragma once

namespace HM
{
   class IMAPFolders;
   class IMAPFolder;

   class IMAPFolderUtilities
   {
   private:
	   IMAPFolderUtilities();
	   virtual ~IMAPFolderUtilities();

   public:

      static bool IsPublicFolder(const std::vector<String> &vecFolderPath);

      static std::shared_ptr<IMAPFolder> GetTopMostExistingFolder(std::shared_ptr<IMAPFolders> pContainer, const std::vector<String> &vecFolderPath);
   };
}
