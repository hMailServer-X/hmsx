#include "pch.h"
#include "IMAPCommandExamine.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"

#include "MessagesContainer.h"

#include "../Common/BO/ACLPermission.h"
#include "../Common/BO/IMAPFolders.h"
#include "../Common/BO/IMAPFolder.h"


namespace HM
{
   IMAPResult
   IMAPCommandEXAMINE::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());

      pParser->Parse(pArgument);

      if (pParser->ParamCount() < 1)
         return IMAPResult(IMAPResult::ResultBad, "EXAMINE Command requires at least 1 parameter.");

      // Fetch the folder
      String sFolderName = pParser->GetParamValue(pArgument, 0);
      std::shared_ptr<IMAPFolder> pSelectedFolder = pConnection->GetFolderByFullPath(sFolderName);
      
      if (!pSelectedFolder)
         return IMAPResult(IMAPResult::ResultBad, "Folder could not be found.");

      if (!pConnection->CheckPermission(pSelectedFolder, ACLPermission::PermissionRead))
         return IMAPResult(IMAPResult::ResultBad, "ACL: Read permission denied (Required for EXAMINE command).");

      pConnection->SetCurrentFolder(pSelectedFolder, true);
      
      std::set<long long> recent_messages;
      auto messages = MessagesContainer::Instance()->GetMessages(pSelectedFolder->GetAccountID(), pSelectedFolder->GetID(), recent_messages, false);

      pConnection->SetRecentMessages(recent_messages);

      long lCount = messages->GetCount();
      long long lFirstUnseenID = messages->GetFirstUnseenUID();
      long lRecentCount = (int) recent_messages.size();

      String sRespTemp;
   
      sRespTemp.Format(PLATFORM_STRING("* %d EXISTS\r\n"), lCount);
      String sResponse = sRespTemp; // EXISTS

      sRespTemp.Format(PLATFORM_STRING("* %d RECENT\r\n"), lRecentCount);
      sResponse += sRespTemp;

      sResponse += PLATFORM_STRING("* FLAGS (\\Deleted \\Seen \\Draft \\Answered \\Flagged)\r\n");
   
      sRespTemp.Format(PLATFORM_STRING("* OK [UIDVALIDITY %d] current uidvalidity\r\n"), pSelectedFolder->GetCreationTime().ToInt());   
      sResponse += sRespTemp;

      if (lFirstUnseenID > 0)
      {
         sRespTemp.Format(PLATFORM_STRING("* OK [UNSEEN %d] unseen messages\r\n"), lFirstUnseenID);
         sResponse += sRespTemp;
      }

      sRespTemp.Format(PLATFORM_STRING("* OK [UIDNEXT %d] next uid\r\n"), pSelectedFolder->GetCurrentUID()+1);
      sResponse += sRespTemp;

      sResponse += PLATFORM_STRING("* OK [PERMANENTFLAGS ()] limited\r\n");

      sResponse += pArgument->Tag() + PLATFORM_STRING(" OK [READ-ONLY] EXAMINE completed\r\n");

      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }
}