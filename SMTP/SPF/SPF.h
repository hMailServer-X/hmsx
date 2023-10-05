#pragma once

namespace HM
{
   class SPF : public Singleton<SPF>
   {
   public:
      SPF(void);
      ~SPF(void);

      enum Result
      {
         Neutral = 0,
         Fail = 1,
         Pass = 2
      };

      Result Test(const String &sSenderIP, const String &sSenderEmail, const String &sHeloHost, String &sExplanation);  

   private:
      
   };

   class SPFTester
   {
   public :
      SPFTester () {};
      ~SPFTester () {};      
      static bool SPFTester::ConvertStringToSockAddr(const String& sIP, int family, struct sockaddr_storage* addrStorage);
      void Test();
   };
}