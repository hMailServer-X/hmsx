#include "pch.h"
#include "IMAPCommandClose.h"
#include "IMAPConnection.h"
#include "MessagesContainer.h"
#include "../Common/BO/ACLPermission.h"
#include "../Common/BO/IMAPFolder.h"

namespace HM
{
   IMAPResult
   IMAPCommandCLOSE::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");
      
      // Iterate through mail boxes and delete messages marked for deletion.
      std::shared_ptr<IMAPFolder> pCurFolder = pConnection->GetCurrentFolder();   

      if (!pCurFolder)
         return IMAPResult(IMAPResult::ResultBad, "No folder selected.");

      // Check if user has permission to expunge. If so, do that.
      if (!pConnection->GetCurrentFolderReadOnly() &&
          pConnection->CheckPermission(pConnection->GetCurrentFolder(), ACLPermission::PermissionExpunge))
      {
         std::function<bool(int, std::shared_ptr<Message>)> filter = [](int index, std::shared_ptr<Message> message)
            {
               return message->GetFlagDeleted();
            };

         auto messages = MessagesContainer::Instance()->GetMessages(pCurFolder->GetAccountID(), pCurFolder->GetID());
         messages->DeleteMessages(filter);
      }
      
      pConnection->CloseCurrentFolder();

      String sResponse = pArgument->Tag() + " OK CLOSE completed\r\n";
      pConnection->SendAsciiData(sResponse);  

      return IMAPResult();

   }
}