#include "pch.h"
#include "./fetchaccounts.h"

namespace HM
{

   FetchAccounts::FetchAccounts(long long iAccountID) :
      account_id_(iAccountID)         
   {

   }

   FetchAccounts::~FetchAccounts(void)
   {
   }

   void 
   FetchAccounts::RefreshPendingList()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_fetchaccounts where fanexttry <= %s and falocked = 0 and faactive = 1 order by faid asc"), SQLStatement::GetCurrentTimestamp().c_str());

      DBLoad_(sSQL);
   }


   void 
   FetchAccounts::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_fetchaccounts where faaccountid = %I64d")
                        PLATFORM_STRING(" order by faid asc"), account_id_);

      DBLoad_(sSQL);
   }

   bool
   FetchAccounts::PreSaveObject(std::shared_ptr<FetchAccount> pFA, XNode *node)
   {
      pFA->SetAccountID(account_id_);
      return true;
   }


}