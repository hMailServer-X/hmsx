#include "pch.h"
#include "SpamTestResult.h"

namespace HM
{
   SpamTestResult::SpamTestResult(const String &testName, Result result, int iSpamScore, const String &sMessage) :
      spam_score_(iSpamScore),
      message_(sMessage),
      testName_(testName),
      result_(result)
   {

   }

   SpamTestResult::~SpamTestResult(void)
   {

   }

}