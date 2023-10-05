#include "pch.h"
#include "Accounts.h"

namespace HM
{
   Accounts::Accounts(long long iDomainID) :
      domain_id_(iDomainID),
      account_id_(0)
   {
   
   }

   Accounts::Accounts(long long iDomainID, long long iAccountID) :
      domain_id_(iDomainID),
      account_id_(iAccountID)
   {

   }

   Accounts::~Accounts  ()
   {
   }


   void
   Accounts::Refresh()
   {
      SQLCommand command;

      String sSQL;
      if (domain_id_ == 0)
      {
         command.SetQueryString(PLATFORM_STRING("select * from hm_accounts order by accountaddress asc"));
      }
      else if (account_id_ == 0)
      {
         command.SetQueryString("select * from hm_accounts where accountdomainid = @DOMAINID order by accountaddress asc");
         command.AddParameter("@DOMAINID", domain_id_);
      }
      else
      {
         command.SetQueryString("select * from hm_accounts where accountdomainid = @DOMAINID and accountid = @ACCOUNTID order by accountaddress asc");
         command.AddParameter("@DOMAINID", domain_id_);
         command.AddParameter("@ACCOUNTID", account_id_);
      }

      DBLoad_(command);
   }

   bool
   Accounts::PreSaveObject(std::shared_ptr<Account> pAccount, XNode *node)
   {
      pAccount->SetDomainID(domain_id_);
      return true;
   }

}
