#include "pch.h"
#include "IMAPCommandGetQuota.h"
#include "IMAPConnection.h"
#include "IMAPConfiguration.h"
#include "IMAPSimpleCommandParser.h"
#include "../Common/BO/Account.h"
#include "../Common/Cache/CacheContainer.h"
#include "../Common/Cache/AccountSizeCache.h"

namespace HM
{
   IMAPCommandGetQuota::IMAPCommandGetQuota(void)
   {
   }

   IMAPCommandGetQuota::~IMAPCommandGetQuota(void)
   {

   }
   
   IMAPResult 
   IMAPCommandGetQuota::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {

      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      if (!Configuration::Instance()->GetIMAPConfiguration()->GetUseIMAPQuota())
         return IMAPResult(IMAPResult::ResultNo, "IMAP QUOTA is not enabled.");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());
      pParser->Parse(pArgument);
      if (pParser->WordCount() < 2)
         return IMAPResult(IMAPResult::ResultBad, "GETQUOTA Command requires at least 1 parameter.");

      std::shared_ptr<const Account> pAccount = CacheContainer::Instance()->GetAccount(pConnection->GetAccount()->GetID());

      // According to the RFC, these values should be counted in kilobytes.
      long long iCurrentSize = AccountSizeCache::Instance()->GetSize(pAccount->GetID()) / 1024;
      long long iMaxSize = ((long long) pAccount->GetAccountMaxSize()) * 1024; // Convert from MB to KB

      String sResponse;
      if (iMaxSize > 0)
      {
         sResponse.Format(PLATFORM_STRING("* QUOTA \"\" (STORAGE %I64d %I64d)\r\n")
                        PLATFORM_STRING("%s OK GETQUOTA completed\r\n"), 
                        iCurrentSize, iMaxSize, pArgument->Tag().c_str());
      }
      else
      {
         // NO QUOTA DEFINED
         sResponse.Format(PLATFORM_STRING("* QUOTA \"\" (STORAGE)\r\n")
            PLATFORM_STRING("%s OK GETQUOTA completed\r\n"), 
            pArgument->Tag().c_str());

      }
      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }
}