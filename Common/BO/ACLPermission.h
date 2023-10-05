#pragma once

namespace HM
{

   class ACLPermission : public BusinessObject<ACLPermission>
   {
   public:
      ACLPermission(void);
      ~ACLPermission(void);

      String GetName() const
      {
         String sName;
         sName.Format(PLATFORM_STRING("ACLPermission-%I64d"), id_);

         return sName;
      }

      enum ePermissionType
      {
         PTUser = 0,
         PTGroup = 1,
         PTAnyone = 2
      };

      enum ePermission
      {
         PermissionNone = 0,
         PermissionLookup = 1,
         PermissionRead = 2,
         PermissionWriteSeen = 4,
         PermissionWriteOthers = 8,
         PermissionInsert = 16,
         PermissionPost = 32,
         PermissionCreate = 64,
         PermissionDeleteMailbox = 128,
         PermissionWriteDeleted = 256,
         PermissionExpunge = 512,
         PermissionAdminister = 1024
      };

      /*
         l - lookup (mailbox is visible to LIST/LSUB commands, SUBSCRIBE
         mailbox)
         r - read (SELECT the mailbox, perform STATUS)
         s - keep seen/unseen information across sessions (set or clear
         \SEEN flag via STORE, also set \SEEN during APPEND/COPY/
         FETCH BODY[...])
         w - write (set or clear flags other than \SEEN and \DELETED via
         STORE, also set them during APPEND/COPY)
         i - insert (perform APPEND, COPY into mailbox)
         p - post (send mail to submission address for mailbox,
         not enforced by IMAP4 itself)
         k - create mailboxes (CREATE new sub-mailboxes in any
         implementation-defined hierarchy, parent mailbox for the new
         mailbox name in RENAME)
         x - delete mailbox (DELETE mailbox, old mailbox name in RENAME)
         t - delete messages (set or clear \DELETED flag via STORE, set
         \DELETED flag during APPEND/COPY)
         e - perform EXPUNGE and expunge as a part of CLOSE
         a - administer (perform SETACL/DELETEACL/GETACL/LISTRIGHTS)
      */


      long long GetShareFolderID();
      void SetShareFolderID(long long iNewVal);

      long long GetPermissionGroupID();
      void SetPermissionGroupID(long long iNewVal);

      long long GetPermissionAccountID();
      void SetPermissionAccountID(long long iNewVal);

      ePermissionType GetPermissionType();
      void SetPermissionType(ePermissionType iNewVal);

      long long GetValue();
      void SetValue(long long iNewVal);

      bool GetAllow(ACLPermission::ePermission p) const;
      void SetAllow(ACLPermission::ePermission p, bool bValue);

      void GrantAll();
      
      String GetRights() const;
      
      void AppendPermissions(const String &sRights);

      static ACLPermission::ePermission GetPermission(wchar_t);

      bool XMLStore(XNode *pParentNode, int iBackupOptions);
      bool XMLLoad(XNode *pAccountNode, int iRestoreOptions);
      bool XMLLoadSubItems(XNode *pAccountNode, int iRestoreOptions) {return true; }

   private:

      String GetPermissionHolderName_(ACLPermission *pPermission) const;

      long long share_folder_id_;

      ePermissionType permission_type_;

      long long permission_group_id_;
      long long permission_account_id_;
      
      long long value_;
   };
}