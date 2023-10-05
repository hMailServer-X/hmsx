#pragma once

#include "IMAPCommand.h"

namespace HM
{
   class IMAPConnection;

   class IMAPCommandGetQuotaRoot : public IMAPCommand
   {
   public:
      IMAPCommandGetQuotaRoot(void);
      ~IMAPCommandGetQuotaRoot(void);

      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };
}