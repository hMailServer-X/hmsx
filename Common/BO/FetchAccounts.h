#pragma once
#include "Collection.h"
#include "../Persistence/PersistentFetchAccount.h"
#include "FetchAccount.h"

namespace HM
{
   class FetchAccounts : public Collection<FetchAccount, PersistentFetchAccount>
   {
   public:
      FetchAccounts(long long iAccountID);
      ~FetchAccounts(void);

      void RefreshPendingList();
      
      void Refresh();

      long long GetAccountID () {return account_id_; }

   protected:
      virtual bool PreSaveObject(std::shared_ptr<FetchAccount> pFA, XNode *node);
      virtual String GetCollectionName() const {return "FetchAccounts"; }
   private:

      long long account_id_;
   };

}