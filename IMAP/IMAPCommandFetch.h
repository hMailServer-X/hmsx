#pragma once

#include "IMAPCommand.h"

namespace HM
{
   class IMAPConnection;

   class IMAPCommandFETCH : public HM::IMAPCommand
   {
   public:
	   IMAPCommandFETCH();
	   virtual ~IMAPCommandFETCH();

      virtual IMAPResult ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument);

   };

}