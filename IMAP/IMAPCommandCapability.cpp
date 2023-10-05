#include "pch.h"
#include "IMAPCommandCapability.h"
#include "IMAPConnection.h"
#include "IMAPConfiguration.h"

namespace HM
{
   IMAPResult
   IMAPCommandCapability::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      String sResponse = "* CAPABILITY IMAP4 IMAP4rev1 CHILDREN";
      
      std::shared_ptr<IMAPConfiguration> pConfig = Configuration::Instance()->GetIMAPConfiguration();

      if (pConfig->GetUseIMAPIdle())
         sResponse += " IDLE";

      if (pConfig->GetUseIMAPQuota())
         sResponse += " QUOTA";

      if (pConfig->GetUseIMAPSort())
         sResponse += " SORT";

      if (pConfig->GetUseIMAPACL())
         sResponse += " ACL";

      if (pConnection->GetConnectionSecurity() == CSSTARTTLSOptional ||
          pConnection->GetConnectionSecurity() == CSSTARTTLSRequired)
         sResponse += " STARTTLS";

      if (pConfig->GetUseIMAPSASLPlain() && (pConnection->IsSSLConnection() || pConnection->GetConnectionSecurity() != CSSTARTTLSRequired))
	      sResponse += " AUTH=PLAIN";

      if (pConfig->GetUseIMAPSASLInitialResponse())
	      sResponse += " SASL-IR";

      sResponse += " NAMESPACE RIGHTS=texk";

      sResponse += "\r\n";
      sResponse += pArgument->Tag() + " OK CAPABILITY completed\r\n";

      pConnection->SendAsciiData(sResponse);   
 
      return IMAPResult();
   }
}