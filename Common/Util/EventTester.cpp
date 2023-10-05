#include "pch.h"
#include "EventTester.h"

namespace HM
{
   void
   EventTester::Test()
   {
      TestSetBeforeWait();
      TestWaitTimeoutNotSet();
      TestWaitTimeoutSet();
   }

   void
   EventTester::TestSetBeforeWait()
   {
      Event ev;
      ev.Set();
      ev.Wait();
   }

   void
   EventTester::TestWaitTimeoutNotSet()
   {
      Event ev;
      ev.WaitFor(boost::chrono::milliseconds(1));
   }

   void
   EventTester::TestWaitTimeoutSet()
   {
      Event ev;
      ev.Set();
      ev.WaitFor(boost::chrono::milliseconds(1));
   }

}