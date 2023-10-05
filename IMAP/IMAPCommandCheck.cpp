#include "pch.h"
#include "IMAPCommandCheck.h"
#include "IMAPConnection.h"

namespace HM
{
   IMAPResult
   IMAPCommandCHECK::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      String sResponse; 
      sResponse += pArgument->Tag() + " OK CHECK completed\r\n";
      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }
}