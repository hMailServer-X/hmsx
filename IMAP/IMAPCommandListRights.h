#pragma once

#include "IMAPCommand.h"

namespace HM
{
   class IMAPCommandListRights : public IMAPCommand
   {
      virtual IMAPResult ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };


}