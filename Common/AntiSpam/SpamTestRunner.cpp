#include "pch.h"

#include "SpamTestRunner.h"
#include "SpamTestData.h"
#include "SpamTestResult.h"
#include "SpamTestDNSBlackLists.h"
#include "SpamTestHeloHost.h"
#include "SpamTestPTR.h"
#include "SpamTestMXRecords.h"
#include "SpamTestSPF.h"
#include "SpamTestSURBL.h"
#include "SpamTestSpamAssassin.h"
#include "DKIM/SpamTestDKIM.h"

namespace HM
{
   SpamTestRunner::SpamTestRunner(void)
   {

   }

   SpamTestRunner::~SpamTestRunner(void)
   {

   }

   void 
   SpamTestRunner::LoadSpamTests()
   {
      spam_tests_.push_back(std::shared_ptr<SpamTestDNSBlackLists> (new SpamTestDNSBlackLists));
      spam_tests_.push_back(std::shared_ptr<SpamTestHeloHost> (new SpamTestHeloHost));
      spam_tests_.push_back(std::shared_ptr<SpamTestPTR> (new SpamTestPTR));
      spam_tests_.push_back(std::shared_ptr<SpamTestMXRecords> (new SpamTestMXRecords));
      spam_tests_.push_back(std::shared_ptr<SpamTestSPF> (new SpamTestSPF));
      spam_tests_.push_back(std::shared_ptr<SpamTestSURBL> (new SpamTestSURBL));
      spam_tests_.push_back(std::shared_ptr<SpamTestDKIM> (new SpamTestDKIM));
      spam_tests_.push_back(std::shared_ptr<SpamTestSpamAssassin> (new SpamTestSpamAssassin));
   }

   std::set<std::shared_ptr<SpamTestResult> >
   SpamTestRunner::RunSpamTest(std::shared_ptr<SpamTestData> pInputData, SpamTest::SpamTestType iType, int iMaxScore)
   {
      auto iter = spam_tests_.begin(); 
      auto iterEnd = spam_tests_.end();

      std::set<std::shared_ptr<SpamTestResult> > setTotalResult;

      int iTotalScore = 0;

      for (; iter != iterEnd; iter++)
      {
         std::shared_ptr<SpamTest> pSpamTest = (*iter);

         if (!pSpamTest->GetIsEnabled())
            continue;

         // Pre or post transmission?

         if (pSpamTest->GetTestType() != iType)
            continue;
         
         String sName = pSpamTest->GetName();

         std::set<std::shared_ptr<SpamTestResult> > setResult = pSpamTest->RunTest(pInputData);

         auto iter = setResult.begin();
         auto iterEnd = setResult.end();

         int totalScoreBefore = iTotalScore;
         for (; iter != iterEnd; iter++)
         {
            std::shared_ptr<SpamTestResult> pResult = (*iter);
            setTotalResult.insert(pResult);

            iTotalScore += pResult->GetSpamScore();
         }

         int totalDiff = iTotalScore - totalScoreBefore;

         String sSpamTestResult;
         sSpamTestResult.Format(PLATFORM_STRING("Spam test: %s, Score: %d"), sName.c_str(), totalDiff);
         LOG_DEBUG(sSpamTestResult);

         if (iTotalScore >= iMaxScore)
         {
            // Threshold has been reached. No point in running any more tests.
            break;
         }

      }

      String sSpamTestResult;
      sSpamTestResult.Format(PLATFORM_STRING("Total spam score: %d"), iTotalScore);
      LOG_DEBUG(sSpamTestResult);
      
      return setTotalResult;
   }
}