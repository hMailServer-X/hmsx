#pragma once

#include "IMAPCommand.h"
namespace HM
{
   class IMAPConnection;
   
   class IMAPCommandAUTHENTICATE : public IMAPCommand
   {
      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };
}