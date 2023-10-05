#include "pch.h"

#include "SpamTestHeloHost.h"

#include "SpamTestData.h"
#include "SpamTestResult.h"

#include "AntiSpamConfiguration.h"

#include "../TCPIP/DNSResolver.h"
#include "../TCPIP/IPAddress.h"
#include "../TCPIP/LocalIPAddresses.h"
#include <boost/algorithm/string/predicate.hpp>

namespace HM
{
   String 
   SpamTestHeloHost::GetName() const
   {
      return "SpamTestHeloHost";
   }

   bool 
   SpamTestHeloHost::GetIsEnabled()
   {
      if (Configuration::Instance()->GetAntiSpamConfiguration().GetCheckHostInHelo())
         return true;
      else
         return false;
   }

   std::set<std::shared_ptr<SpamTestResult> >
   SpamTestHeloHost::RunTest(std::shared_ptr<SpamTestData> pTestData)
   {
      std::set<std::shared_ptr<SpamTestResult> > setSpamTestResults;

      const IPAddress &iIPAdress = pTestData->GetOriginatingIP();
      String sHeloHost = pTestData->GetHeloHost();

      if (sHeloHost.IsEmpty())
      {
         // Not possible to run this test without a host.
         return setSpamTestResults;
      }

      if (LocalIPAddresses::Instance()->IsWithinLoopbackRange(iIPAdress))
      {
         // Ignore this test if send thru localhost.
         return setSpamTestResults;
      }

      if (!CheckHostInHelo_(sHeloHost, iIPAdress))
      {
         // Incorrect host in helo
         String sMessage = "The host name specified in HELO does not match IP address.";
         int iScore = Configuration::Instance()->GetAntiSpamConfiguration().GetCheckHostInHeloScore();

         std::shared_ptr<SpamTestResult> pResult = std::shared_ptr<SpamTestResult>(new SpamTestResult(GetName(), SpamTestResult::Fail, iScore, sMessage));
         setSpamTestResults.insert(pResult);   

      }
      
      return setSpamTestResults;
   }


   bool 
   SpamTestHeloHost::CheckHostInHelo_(const String &sHeloHost, const IPAddress &address)
   {
      String sIPAddress = address.ToString();

      if (sHeloHost.Left(1) == PLATFORM_STRING("["))
      {
         String sTempHost = sHeloHost;
         sTempHost.TrimLeft(PLATFORM_STRING("["));
         // IPv6 
         if (sTempHost.Left(5) == PLATFORM_STRING("IPv6:"))
            sTempHost.TrimLeft(PLATFORM_STRING("IPv6:"));
         sTempHost.TrimRight(PLATFORM_STRING("]"));

         // IPv6 is alphanumeric therefore uppercase and lowercase characters are equivalent
         if (boost::iequals(sTempHost, sIPAddress))
         {
            return true;
         }
      }
      else
      {
         // Check that the host name given in helo actually matches
         // the senders IP address.
         std::vector<String> saFoundNames;
         DNSResolver resolver;
         if (!resolver.GetIpAddresses(sHeloHost, saFoundNames, true))
         {
            // DNS failure. Assume it's not spam.
            return true;
         }

         // Check that the IP address is one of these A or AAAA records.
         for (auto iter = saFoundNames.begin(); iter < saFoundNames.end(); iter++)
         {
            // IPv6 is alphanumeric therefore uppercase and lowercase characters are equivalent
            if (boost::iequals((*iter), sIPAddress))
            {
               return true;
            }
         }
      }

      return false;

   }

}