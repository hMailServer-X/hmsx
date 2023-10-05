#include "pch.h"

#include "SPF.h"
#include "rmspf.h"

#include <string>
#include <cstring>
#include <cstdlib>


namespace HM
{
   SPF::SPF(void)
   {
      // Initialize. This is only done once.
      SPFInit(NULL,0, SPF_Multithread);
   }

   SPF::~SPF(void)
   {

   }

   std::string ConvertStringToUTF8(const HM::String& s)
   {
       // Hier führen wir die Konvertierung von HM::String zu UTF-8 durch.
       std::wstring wideStr = s;
       std::string utf8Str;
       int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
       if (utf8Size > 0)
       {
           utf8Str.resize(utf8Size - 1); // Exclude null terminator
           WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Size, nullptr, nullptr);
       }
       return utf8Str;
   }

    
   bool SPFTester::ConvertStringToSockAddr(const String & sIP, int family, struct sockaddr_storage* addrStorage)
   {
       memset(addrStorage, 0, sizeof(struct sockaddr_storage));

       if (family == AF_INET)
       {
           struct sockaddr_in* addrIPv4 = (struct sockaddr_in*)addrStorage;
           std::string utf8IP = ConvertStringToUTF8(sIP);
           if (inet_pton(AF_INET, utf8IP.c_str(), &(addrIPv4->sin_addr)) != 1)
               return false;
           addrIPv4->sin_family = AF_INET;
       }
       else if (family == AF_INET6)
       {
           struct sockaddr_in6* addrIPv6 = (struct sockaddr_in6*)addrStorage;
           std::string utf8IP = ConvertStringToUTF8(sIP);
           if (inet_pton(AF_INET6, utf8IP.c_str(), &(addrIPv6->sin6_addr)) != 1)
               return false;
           addrIPv6->sin6_family = AF_INET6;
       }
       else
       {
           return false; // Ungültige Adressfamilie
       }

       return true;
   }

   SPF::Result SPF::Test(const String& sSenderIP, const String& sSenderEmail, const String& sHeloHost, String& sExplanation)
   {
       String sDomain = StringParser::ExtractDomain(sSenderEmail);

       int family;
       if (sSenderIP.find(PLATFORM_STRING(":")) != String::npos)
           family = AF_INET6;
       else
           family = AF_INET;

       // Convert the IP address from a dotted string
       // to a binary form. We use the SPF library to
       // do this.

       struct sockaddr_storage addrStorage;
       if (!SPFTester::ConvertStringToSockAddr(sSenderIP, family, &addrStorage))
           return Neutral;

       const char* explain;
       int result = SPFQuery(family, &addrStorage, (char*) sSenderEmail.c_str(), nullptr, (char*) sHeloHost.c_str(), nullptr, &explain);

       if (explain != nullptr)
       {
           sExplanation = explain;
           free((void*)explain); // Freigabe des vom SPF-Systems allozierten Speichers
       }

       if (result == SPF_Fail)
       {
           // FAIL
           return Fail;
       }
       else if (result == SPF_Pass)
       {
           return Pass;
       }

       return Neutral;
   }

   void SPFTester::Test()
   {
      String sExplanation;
      
      if (SPF::Instance()->Test("185.216.75.37", "example@hmailserver.com", "mail.hmailserver.com", sExplanation) != SPF::Pass)
      {
         // Should be allowed. 
         throw;
      }

      if (SPF::Instance()->Test("1.2.3.4", "example@hmailserver.com", "mail.hmailserver.com", sExplanation) != SPF::Fail)
      {
         // Should not be allowed.
         throw;
      }
   }


}