#pragma once

#include "Collection.h"

#include "../Persistence/PersistentAccount.h"
#include "../BO/Account.h"

namespace HM
{
   class Account;
   class PersistentAccount;

   class Accounts : public Collection<Account, PersistentAccount>
   {
   public:
	   Accounts (long long iDomainID);
      Accounts (long long iDomainID, long long iAccountID);
	   virtual ~Accounts();

      void Refresh();
  
   protected:
      
      virtual bool PreSaveObject(std::shared_ptr<Account> pAccount, XNode *node);
      virtual String GetCollectionName() const {return "Accounts"; }


   private:

      long long domain_id_;
      long long account_id_;
  
   };

}