#include "pch.h"
#include "SpamTestSPF.h"
#include "SpamTestData.h"
#include "SpamTestResult.h"
#include "AntiSpamConfiguration.h"
#include "../../SMTP/SPF/SPF.h"

namespace HM
{
   String 
   SpamTestSPF::GetName() const
   {
      return GetTestName();
   }

   String 
   SpamTestSPF::GetTestName() 
   {
      return "SpamTestSPF";
   }


   bool 
   SpamTestSPF::GetIsEnabled()
   {
      if (Configuration::Instance()->GetAntiSpamConfiguration().GetUseSPF())
         return true;
      else
         return false;
   }

   std::set<std::shared_ptr<SpamTestResult> > 
   SpamTestSPF::RunTest(std::shared_ptr<SpamTestData> pTestData)
   {
      std::set<std::shared_ptr<SpamTestResult> > setSpamTestResults;

      String sMessage = "";
      int iScore = 0;

      const IPAddress &originatingAddress = pTestData->GetOriginatingIP();

      if (originatingAddress.IsAny())
         return setSpamTestResults;

      String sExplanation;
      SPF::Result result = SPF::Instance()->Test(originatingAddress.ToString(), pTestData->GetEnvelopeFrom(), pTestData->GetHeloHost(), sExplanation);
      
      if (result == SPF::Fail)
      {
         // Blocked by SPF.s
         if (!sExplanation.IsEmpty())
            sMessage.Format(PLATFORM_STRING("Blocked by SPF. (%s)"), sExplanation.c_str());
         else
            sMessage = "Blocked by SPF.";
         iScore = Configuration::Instance()->GetAntiSpamConfiguration().GetUseSPFScore();

         std::shared_ptr<SpamTestResult> pResult = std::shared_ptr<SpamTestResult>(new SpamTestResult(GetName(), SpamTestResult::Fail, iScore, sMessage));
         setSpamTestResults.insert(pResult);
      }      
      else if (result == SPF::Pass)
      {
         std::shared_ptr<SpamTestResult> pResult = std::shared_ptr<SpamTestResult>(new SpamTestResult(GetName(), SpamTestResult::Pass, 0, ""));
         setSpamTestResults.insert(pResult);
      }


      return setSpamTestResults;
   }

}