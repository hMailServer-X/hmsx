#include "pch.h"
#include "./surbl.h"

#include "../../Common/BO/MessageData.h"
#include "../../Common/BO/SURBLServer.h"
#include "../../Common/TCPIP/DNSResolver.h"

#include "../../Common/Util/TLD.h"
#include <boost/regex/v4/regex.hpp>

namespace HM
{
   SURBL::SURBL(void)
   {
      
   }

   SURBL::~SURBL(void)
   {
   }

   

   bool 
   SURBL::Run(std::shared_ptr<SURBLServer> pSURBLServer, std::shared_ptr<MessageData> pMessageData)
   {
      LOG_DEBUG("SURBL: Execute");

      // Extract body
      String sBody = pMessageData->GetBody() + pMessageData->GetHTMLBody(); 

      // Extract URL's from the mail body:
      // Original: (?:(?>https?)?(?>:\/\/|\%3A\%2F\%2F))(?:www\.)?([a-z0-9\-\.\=\r\n]+)

      String sRegex = "(?:(?>https?)?(?>:\\/\\/|\\%3A\\%2F\\%2F))(?:www\\.)?([a-z0-9\\-\\=\\.\\r\\n]+)";

      std::set<String> addresses;

      const int maxURLsToProcess = 15;

      try
      {
         boost::wregex expression(sRegex, boost::wregex::icase);
         boost::wsmatch matches;

         String sRemainingSearchSpace = sBody;

         while (boost::regex_search(sRemainingSearchSpace, matches, expression))
         {
            if (matches.size() < 2)
            {
               ErrorManager::Instance()->ReportError(ErrorManager::Medium, 5702, "SURBL::Run", "A regex match was found, but there were <2 matches in the result");
               break;
            }

            String sURL = matches[1];

            // Clean the URL from linefeeds
            CleanURL_(sURL);

            // Trim away top domain
            if (!CleanHost_(sURL))
            {
               sRemainingSearchSpace = matches.suffix();
               continue;
            }

            if (addresses.find(sURL) == addresses.end())
            {
               String logMessage;
               logMessage.Format(PLATFORM_STRING("SURBL: Found URL: %s"), sURL.c_str());
               LOG_DEBUG(logMessage);

               addresses.insert(sURL);

               if (addresses.size() > maxURLsToProcess)
               {
                  break;
               }
            }
            
            sRemainingSearchSpace = matches.suffix();
         }
      }
      catch (std::runtime_error &err) // regex_match will throw runtime_error if regexp is too complex.
      {
         ErrorManager::Instance()->ReportError(ErrorManager::Medium, 5701, "SURBL::Run", "Parsing HTML body with regular expression threw a runtime_error", err);
         return true;
      }

      if (addresses.size() > 0)
      {
         String logMessage = Formatter::Format("SURBL: {0} unique addresses found.", addresses.size());
         LOG_DEBUG(logMessage);
      }

      
      boost::chrono::system_clock::time_point start_time = boost::chrono::system_clock::now();

      int processedAddresses = 0;
      for (String sURL : addresses)
      {
         boost::chrono::duration<double> elapsed_seconds = boost::chrono::system_clock::now() - start_time;

         if (elapsed_seconds.count() > 10)
         {
            LOG_DEBUG("SURBL: Aborting. Too long time elapsed.");
            return true;
         }

         if (processedAddresses > maxURLsToProcess)
         {
            LOG_DEBUG("SURBL: Aborting. Too many urls.");
            return true;
         }

         String sHostToLookup = sURL + "." + pSURBLServer->GetDNSHost();

         LOG_DEBUG(Formatter::Format(PLATFORM_STRING("SURBL: Lookup: {0}"), sHostToLookup));

         std::vector<String> saFoundNames;
         DNSResolver resolver;
         if (!resolver.GetIpAddresses(sHostToLookup, saFoundNames, false))
         {
            LOG_DEBUG("SURBL: DNS query failed.");
            return true;
         }

         if (saFoundNames.size() > 0)
         {
            LOG_DEBUG("SURBL: Match found");
            return false;
         }

         processedAddresses++;
      }

      LOG_DEBUG("SURBL: Match not found");
      return true;
   }

   void
   SURBL::CleanURL_(String &url) const
   {
      url.Replace(PLATFORM_STRING("=\r\n"), PLATFORM_STRING(""));
      url.Replace(PLATFORM_STRING("=\r"), PLATFORM_STRING(""));
      url.Replace(PLATFORM_STRING("=\n"), PLATFORM_STRING(""));
      url.MakeLower();

      int newLinePosition = url.FindOneOf(PLATFORM_STRING("\r\n"));

      if (newLinePosition >= 0)
         url = url.Left(newLinePosition);
   }

   bool
   SURBL::CleanHost_(String &sDomain) const
   {
      bool bIsIPAddress = false;
      return TLD::Instance()->GetDomainNameFromHost(sDomain, bIsIPAddress);

   }
}