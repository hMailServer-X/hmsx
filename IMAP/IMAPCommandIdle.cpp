#include "pch.h"
#include "IMAPCommandIdle.h"
#include "IMAPConnection.h"
#include "IMAPConfiguration.h"
#include "IMAPStore.h"

namespace HM
{

   IMAPCommandIdle::IMAPCommandIdle(std::shared_ptr<IMAPConnection> pConnection) :
      connection_(pConnection)
   {

   }

   IMAPCommandIdle::~IMAPCommandIdle()
   {
      try
      {
         std::shared_ptr<IMAPConnection> safeConnection = connection_.lock();
         if (!safeConnection)
            return;

         if (safeConnection->GetIsIdling())
         {
            Finish(false);
         }
      }
      catch (...)
      {

      }

   }

   IMAPResult
   IMAPCommandIdle::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Handles an IMAP idle command from the client. Switches to IDLE mode by
   // adding us to the IMAP notification thingy.
   //---------------------------------------------------------------------------()
   {
      if (!Configuration::Instance()->GetIMAPConfiguration()->GetUseIMAPIdle())
         return IMAPResult(IMAPResult::ResultNo, "IMAP IDLE is not enabled.");
         
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultBad, "Command requires authentication.");

      pConnection->SetIsIdling(true);
      pConnection->SendAsciiData("+ idling\r\n");

      tag_ = pArgument->Tag();

      return IMAPResult();
   }

   void 
   IMAPCommandIdle::Finish(bool sendNotificationToClient)
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Switches out of IDLE mode.
   //---------------------------------------------------------------------------()
   {  
      std::shared_ptr<IMAPConnection> safeConnection = connection_.lock ();
      if (!safeConnection)
         return;

      safeConnection->SetIsIdling(false);

      if (sendNotificationToClient)
      {
         String sResponse = tag_ + " OK IDLE terminated\r\n";
         safeConnection->SendAsciiData(sResponse);
      }
   }



}
