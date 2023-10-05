#include "pch.h"
#include "IMAPCommandLogin.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"

#include "../common/Util/AccountLogon.h"
#include "../common/BO/Account.h"
#include "../common/BO/SecurityRange.h"

#include "../Common/TCPIP/CipherInfo.h"


namespace HM
{
   IMAPResult
   IMAPCommandLOGIN::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (pConnection->GetConnectionSecurity() == CSSTARTTLSRequired)
      {
         if (!pConnection->IsSSLConnection())
         {
            return IMAPResult(IMAPResult::ResultBad, "STARTTLS is required.");
         }
      }

      if (pConnection->GetSecurityRange()->GetRequireTLSForAuth() && !pConnection->IsSSLConnection())
      {
         return IMAPResult(IMAPResult::ResultBad, "A SSL/TLS-connection is required for authentication.");
      }

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());
      
      pParser->Parse(pArgument);
      
      if (pParser->ParamCount() != 2)
      {
         return IMAPResult(IMAPResult::ResultBad, "Command requires 2 parameters");
      }

      // The folder wildcard could be sent in a separate buffer.
      String sUsername = pParser->GetParamValue(pArgument, 0);
      String sPassword = pParser->GetParamValue(pArgument, 1);

      AccountLogon accountLogon;
      bool disconnect = false;
      std::shared_ptr<const Account> pAccount = accountLogon.Logon(pConnection->GetRemoteEndpointAddress(), sUsername, sPassword, disconnect);

      if (disconnect)
      {
         String sResponse = "* Too many invalid logon attempts.\r\n"; 
         sResponse += pArgument->Tag() + " BAD Goodbye\r\n";
         pConnection->Logout(sResponse);   

         return IMAPResult(IMAPResult::ResultOKSupressRead, "");
      } 

      const bool isAuthenticated = pAccount != nullptr;

      if (Configuration::Instance()->GetUseScriptServer())
      {
 
       
         if (pConnection->IsSSLConnection())
         {
            auto cipher_info = pConnection->GetCipherInfo();
    
         }


         String sEventCaller = "OnClientLogon(HMAILSERVER_CLIENT)";

      }

      if (!pAccount)
      {
         if (sUsername.Find(PLATFORM_STRING("@")) == -1)
            return IMAPResult(IMAPResult::ResultNo, "Invalid user name or password. Please use full email address as user name.");
         else
            return IMAPResult(IMAPResult::ResultNo, "Invalid user name or password.");
      }

      // Load mail boxes
      pConnection->Login(pAccount);

      String sResponse = pArgument->Tag() + " OK LOGIN completed\r\n";
      pConnection->SendAsciiData(sResponse);   
      
      return IMAPResult();

   }
}
