#pragma once

#include "IMAPCommand.h"
namespace HM
{
   class IMAPConnection;

   class IMAPCommandCapability : public IMAPCommand
   {
      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };


}
