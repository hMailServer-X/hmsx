#pragma once

namespace HM
{
   class RegularExpression
   {
   public:
      RegularExpression(void);
      ~RegularExpression(void);

      static bool TestExactMatch(const String &sExpression, const String &sValue);

      
   };

   class RegularExpressionTester
   {
   public:
      RegularExpressionTester() {}; 

      static void Test();
   };
}