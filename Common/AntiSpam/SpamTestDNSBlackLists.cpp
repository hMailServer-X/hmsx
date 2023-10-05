#include "pch.h"
#include "SpamTestDNSBlackLists.h"

#include "SpamTestData.h"
#include "SpamTestResult.h"
#include "../BO/DNSBlackLists.h"
#include "../../SMTP/BLCheck.h"

namespace HM
{
   String 
   SpamTestDNSBlackLists::GetName() const
   {
      return "SpamTestDNSBlackLists";
   }

   bool 
   SpamTestDNSBlackLists::GetIsEnabled()
   {
      std::shared_ptr<DNSBlackLists> pDNSBlackLists = Configuration::Instance()->GetAntiSpamConfiguration().GetDNSBlackLists();

      std::vector<std::shared_ptr<DNSBlackList> > vec = pDNSBlackLists->GetVector();
      auto iter = vec.begin();
      auto iterEnd = vec.end();
      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<DNSBlackList> pDNSBL = (*iter);

         if (pDNSBL->GetIsActive())
            return true;
      }

      return false;
   }

   std::set<std::shared_ptr<SpamTestResult> >
   SpamTestDNSBlackLists::RunTest(std::shared_ptr<SpamTestData> pTestData)
   {
      std::set<std::shared_ptr<SpamTestResult> > setSpamTestResults;

      String sMessage = "";
      int iScore = 0;

      const IPAddress &addr = pTestData->GetOriginatingIP();
      if (addr.IsAny())
         return setSpamTestResults;

      std::shared_ptr<DNSBlackLists> pDNSBlackLists = HM::Configuration::Instance()->GetAntiSpamConfiguration().GetDNSBlackLists();
      
      for(std::shared_ptr<DNSBlackList> pDNSBL : pDNSBlackLists->GetVector())
      {
         if (pDNSBL->GetIsActive() && 
            BLCheck::ClientExistsInDNSBL(addr, pDNSBL->GetDNSHost(), pDNSBL->GetExpectedResult()))
         {
            int iSomeScore = pDNSBL->GetScore();
            std::shared_ptr<SpamTestResult> pResult = std::shared_ptr<SpamTestResult>(new SpamTestResult(GetName(), SpamTestResult::Fail, iSomeScore, pDNSBL->GetRejectMessage()));
            
            setSpamTestResults.insert(pResult);
         }
      }

     return setSpamTestResults;
   }

}