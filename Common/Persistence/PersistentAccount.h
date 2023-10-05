#pragma once

namespace HM
{
   class Account;
   enum PersistenceMode;

   class PersistentAccount 
   {
   public:
	   PersistentAccount();
	   virtual ~PersistentAccount();

      static bool DeleteObject(std::shared_ptr<Account> pAccount);
      static bool SaveObject(std::shared_ptr<Account> pAccount);
      static bool SaveObject(std::shared_ptr<Account> pAccount, String &sErrorMessage, PersistenceMode mode);
      static bool SaveObject(std::shared_ptr<Account> pAccount, String &sErrorMessage, bool createInbox, PersistenceMode mode);
      static bool DeleteMessages(std::shared_ptr<Account> pAccount);

      static long long GetMessageBoxSize(long long iAccountID);
      // Returns the current message box size, 
      // counted in bytes.

      static bool ReadObject(std::shared_ptr<Account> pAccount,std::shared_ptr<DALRecordset> pRS);
      static bool ReadObject(std::shared_ptr<Account> pAccount,const String & sAddress);
      static bool ReadObject(std::shared_ptr<Account> pAccount,long long ObjectID);

      static bool UpdateLastLogonTime(std::shared_ptr<const Account> pAccount);

      static bool GetIsVacationMessageOn(std::shared_ptr<const Account> pAccount);
      static bool CreateInbox(const Account &account);

      static bool DisableVacationMessage(std::shared_ptr<const Account> pAccount);

   private:

      static bool ReadObject(std::shared_ptr<Account> pAccount,const SQLCommand &command);
      
   };


}