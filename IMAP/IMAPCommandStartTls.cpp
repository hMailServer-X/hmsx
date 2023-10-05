#include "pch.h"

#include "IMAPCommandStartTls.h"
#include "IMAPConnection.h"


namespace HM
{
   IMAPCommandStartTls::IMAPCommandStartTls()
   {

   }

   IMAPCommandStartTls::~IMAPCommandStartTls()
   {

   }

   IMAPResult
   IMAPCommandStartTls::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (pConnection->GetConnectionSecurity() == CSSTARTTLSOptional ||
         pConnection->GetConnectionSecurity() == CSSTARTTLSRequired)
      {
         pConnection->SendAsciiData(pArgument->Tag() + " OK Begin TLS negotiation now\r\n");

         pConnection->StartHandshake();

         return IMAPResult(IMAPResult::ResultOKSupressRead, "");
      }
      else
      {
         return IMAPResult(IMAPResult::ResultBad, "Unknown or NULL command");
      }
      
   }
}
