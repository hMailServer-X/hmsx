#include "pch.h"

#include "IMAPCommandGetQuotaRoot.h"
#include "IMAPConnection.h"
#include "IMAPConfiguration.h"
#include "IMAPSimpleCommandParser.h"
#include "../Common/BO/Account.h"
#include "../Common/Cache/CacheContainer.h"
#include "../Common/Cache/AccountSizeCache.h"

namespace HM
{
   IMAPCommandGetQuotaRoot::IMAPCommandGetQuotaRoot(void)
   {
   }

   IMAPCommandGetQuotaRoot::~IMAPCommandGetQuotaRoot(void)
   {
   }


   IMAPResult 
   IMAPCommandGetQuotaRoot::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      if (!Configuration::Instance()->GetIMAPConfiguration()->GetUseIMAPQuota())
         return IMAPResult(IMAPResult::ResultNo, "IMAP QUOTA is not enabled.");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());
      
      pParser->Parse(pArgument);

      if (pParser->ParamCount() < 1)
         return IMAPResult(IMAPResult::ResultBad, "GETQUOTAROOT Command requires at least 1 parameter.");

      String sFolderName = pParser->GetParamValue(pArgument, 0);

      if (pParser->Word(1)->Quoted())
      {
         // If there was quotes in the command, readd
         // them now. For example, if there's a space
         // in the folder name it should be in quotes.
         sFolderName = "\"" + sFolderName + "\"";
      }
      

      std::shared_ptr<const Account> pAccount = CacheContainer::Instance()->GetAccount(pConnection->GetAccount()->GetID());

      // According to the RFC, these values should be counted in kilobytes.
      long long iCurrentSize = AccountSizeCache::Instance()->GetSize(pAccount->GetID()) / 1024; // Convert from Bytes to KB
      long long iMaxSize = ((long long) pAccount->GetAccountMaxSize() * 1024); // Convert from MB to KB
      
      String sResponse;
      if (iMaxSize > 0)
      {
         sResponse.Format(PLATFORM_STRING("* QUOTAROOT %s \"\"\r\n")
                        PLATFORM_STRING("* QUOTA \"\" (STORAGE %I64d %I64d)\r\n")
                        PLATFORM_STRING("%s OK GETQUOTAROOT completed\r\n"), 
                        sFolderName.c_str(), iCurrentSize, iMaxSize, pArgument->Tag().c_str());
      }
      else
      {
         // NO QUOTA DEFINED

         sResponse.Format(PLATFORM_STRING("* QUOTAROOT %s \"\"\r\n")
            PLATFORM_STRING("* QUOTA \"\" ()\r\n")
            PLATFORM_STRING("%s OK GETQUOTAROOT completed\r\n"), 
            sFolderName.c_str(), pArgument->Tag().c_str());
         
      }

      pConnection->SendAsciiData(sResponse);  

      return IMAPResult();
      
   }

}