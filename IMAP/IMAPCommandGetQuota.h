#pragma once


#include "IMAPCommand.h"

namespace HM
{
   class IMAPConnection;

   class IMAPCommandGetQuota : public IMAPCommand
   {
   public:
      IMAPCommandGetQuota(void);
      ~IMAPCommandGetQuota(void);

      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);
   };
}