#pragma once

#include "IMAPCommand.h"

namespace HM
{
   class IMAPConnection;

   class IMAPCommandStartTls : public IMAPCommand  
   {
   public:
      IMAPCommandStartTls();
      virtual ~IMAPCommandStartTls();

      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);

   };

}
