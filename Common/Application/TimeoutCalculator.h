#pragma once

namespace HM
{
   class TimeoutCalculator  
   {
   public:
      TimeoutCalculator();

      enum Constants
      {
         MaxConnectionCountOptimized = 20000
      };

      int Calculate(int minSecs, int maxSecs);
      int Calculate(int connectionCount, int minSecs, int maxSecs);

   private:
   };

   class TimeoutCalculatorTester
   {
   public:
      void Test();


   };
}
