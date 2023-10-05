#pragma once

namespace HM
{
   class DateTime;

   class FetchAccountUID : public BusinessObject<FetchAccountUID>
   {
   public:
      FetchAccountUID (long long iID, long long iAccountID, const String &sUID, const String &sDate);
      FetchAccountUID();

	  ~FetchAccountUID();

     String GetName() const { return "FetchAccountUID"; }

      void SetAccountID(long long accountID);

      const String &GetUID() const {return uid_; }
      DateTime GetCreationDate() const;
      long long GetAccountID() const {return account_id_;}

      bool XMLStore(XNode *pUIDsNode, int iBackupOptions);
      bool XMLLoad(XNode *pUIDNode, int iRestoreOptions);
      bool XMLLoadSubItems(XNode *pUIDNode, int iRestoreOptions) {return true; } 

   private:
      long long account_id_;
      String uid_;
      String date_;
   };
}