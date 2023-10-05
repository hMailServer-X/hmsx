#pragma once

#include "SpamTest.h"

namespace HM
{
   class IPAddress;

   class SpamTestHeloHost : public SpamTest
   {
   public:
      
      virtual SpamTestType GetTestType()
      {
         return SpamTest::PreTransmission;
      }

      virtual String GetName() const;
      virtual bool GetIsEnabled();

      virtual std::set<std::shared_ptr<SpamTestResult> > RunTest(std::shared_ptr<SpamTestData> pTestData);

   private:

      bool CheckHostInHelo_(const String &sHeloHost, const IPAddress &iIPAddress);

   };

}