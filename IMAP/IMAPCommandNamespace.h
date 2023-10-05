#pragma once

#include "IMAPCommand.h"

namespace HM
{
   class IMAPCommandNamespace : public IMAPCommand
   {
      virtual IMAPResult ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };


}