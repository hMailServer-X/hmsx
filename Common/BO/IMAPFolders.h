#pragma once

#include "IMAPFolder.h"
#include "Collection.h"
#include "../Persistence/PersistentIMAPFolder.h"

namespace HM
{
   class IMAPFolders : public Collection<IMAPFolder, PersistentIMAPFolder>
   {
   public:
	   IMAPFolders(long long iAccountID, long long iParentFolderID);
      IMAPFolders();

	   virtual ~IMAPFolders();
      void Refresh();

      std::shared_ptr<IMAPFolder> GetItemByDBIDRecursive(long long lFolderID);
      std::shared_ptr<IMAPFolder> GetFolderByName(const String &sName, bool bRecursive = false);
      std::shared_ptr<IMAPFolder> GetFolderByFullPath(const String &sPath);
      std::shared_ptr<IMAPFolder> GetFolderByFullPath(const std::vector<String> &vecFolders);
      
      void RemoveFolder(std::shared_ptr<IMAPFolder> pFolder);

      void CreatePath(std::shared_ptr<IMAPFolders> pParentContainer, const std::vector<String> &vecFolderPath, bool bAutoSubscribe);
      
      virtual bool PreSaveObject(std::shared_ptr<IMAPFolder> pObject, XNode *node);

      long long GetParentID();
      // Returns the ID of the IMAP folder in which these folder exists. If this is
      // a top level collection, -1 is returned.

      long long GetAccountID();
      // Returns the ID of the account in which these folders exist

   protected:
      virtual String GetCollectionName() const;

   private:

      bool GetIsPublicFolders_() const;

      long long account_id_;
      long long parent_folder_id_;
   };

}
