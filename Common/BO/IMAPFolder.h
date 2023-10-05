#pragma once

#include "Messages.h"
#include "../Util/VariantDateTime.h"

namespace HM
{
   class IMAPFolders;
   //class IMAPFolder;
   class ACLPermissions;

   class IMAPFolder 
   {
   public:

      enum
      {
         MaxFolderDepth = 25
      };
   
      IMAPFolder();
      IMAPFolder(long long iAccountID, long long iParentFolderID);

	   virtual ~IMAPFolder();

      long long GetID() const { return dbid_; }
      void SetID(long long lNewVal) { dbid_ = lNewVal;}

      long long GetParentFolderID() const;
      void SetParentFolderID(long long value) {parent_folder_id_ = value;}

      long long GetAccountID() const { return account_id_;} 
      void SetAccountID(long long newVal) {account_id_ = newVal;}

      unsigned int GetCurrentUID() const { return current_uid_;} 
      void SetCurrentUID(unsigned int currentUID) {current_uid_ = currentUID;}

      const DateTime &GetCreationTime() const { return create_time_;} 
      void SetCreationTime(const DateTime &currentUID) {create_time_ = currentUID;}


      bool GetIsSubscribed() const { return folder_is_subscribed_;} 
      void SetIsSubscribed(bool bNewVal) { folder_is_subscribed_ = bNewVal;}

      String GetFolderName() const { return folder_name_;}
      void SetFolderName(const String & sNewVal) { folder_name_ =sNewVal; }

      String GetName() const {return GetFolderName(); }
      
      std::shared_ptr<Messages> GetMessages();

      std::shared_ptr<IMAPFolders> GetSubFolders();
      std::shared_ptr<ACLPermissions> GetPermissions();

      static void EscapeFolderString(String &sFolderString);
      static void UnescapeFolderString(String &sFolderString);
      
      int GetFolderDepth(int &iRecursion);

      bool XMLStore(XNode *pParentNode, int iBackupOptions);
      bool XMLLoad(XNode *pFolderNode, int iRestoreOptions);
      bool XMLLoadSubItems(XNode *pFolderNode, int iRestoreOptions);

      static bool IsValidFolderName(const std::vector<String> &vecPath, bool bIsPublicFolder);

      bool IsPublicFolder();

   protected:

      long long dbid_;
      long long account_id_;
      long long parent_folder_id_;
      unsigned int current_uid_;

      bool folder_is_subscribed_;
      AnsiString folder_name_;

      std::shared_ptr<Messages> messages_;
      std::shared_ptr<IMAPFolders> sub_folders_;   
 
      DateTime create_time_;
   };

}

