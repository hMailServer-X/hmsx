#pragma once

namespace HM
{
   class EventTester
   {
   public:
      void Test();
   private:

      void TestSetBeforeWait();
      void TestWaitTimeoutNotSet();
      void TestWaitTimeoutSet();
   };
}