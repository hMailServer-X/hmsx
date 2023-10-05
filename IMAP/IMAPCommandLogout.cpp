#include "pch.h"
#include "IMAPCommandLogout.h"
#include "IMAPConnection.h"

namespace HM
{
   IMAPResult
   IMAPCommandLOGOUT::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      String sResponse = "* BYE Have a nice day\r\n"; 
      sResponse += pArgument->Tag() + " OK Logout completed\r\n";

      pConnection->Logout(sResponse);

      return IMAPResult(IMAPResult::ResultOKSupressRead, "");
   }
}