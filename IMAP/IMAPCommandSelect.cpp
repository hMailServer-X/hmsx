#include "pch.h"
#include "IMAPCommandSelect.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"
#include "IMAPConfiguration.h"
#include "MessagesContainer.h"

#include "../Common/BO/IMAPFolders.h"
#include "../Common/BO/IMAPFolder.h"

namespace HM
{
   IMAPResult
   IMAPCommandSELECT::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {

      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());

      pParser->Parse(pArgument);

      if (pParser->ParamCount() < 1)
         return IMAPResult(IMAPResult::ResultBad, "SELECT Command requires at least 1 parameter.");

      String sFolderName = pParser->GetParamValue(pArgument, 0);
      if (sFolderName == Configuration::Instance()->GetIMAPConfiguration()->GetIMAPPublicFolderName())
         return IMAPResult(IMAPResult::ResultBad, "SELECT Only sub folders of the root shared folder can be selected.");
         
      std::shared_ptr<IMAPFolder> pSelectedFolder = pConnection->GetFolderByFullPath(sFolderName);
      if (!pSelectedFolder)
         return IMAPResult(IMAPResult::ResultBad, "Folder could not be found.");

      bool readAccess = false;
      bool writeAccess = false;
      pConnection->CheckFolderPermissions(pSelectedFolder, readAccess, writeAccess);

      // Check if the user has access to read this folder.
      if (!readAccess)
         return IMAPResult(IMAPResult::ResultBad, "ACL: Read permission denied (Required for SELECT command).");

      pConnection->SetCurrentFolder(pSelectedFolder, false);

      std::set<long long> recent_messages;
      auto messages = MessagesContainer::Instance()->GetMessages(pSelectedFolder->GetAccountID(), pSelectedFolder->GetID(), recent_messages, true);

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

      sResponse += PLATFORM_STRING("* OK [PERMANENTFLAGS (\\Deleted \\Seen \\Draft \\Answered \\Flagged)] limited\r\n");

      if (writeAccess)
         sResponse += pArgument->Tag() + PLATFORM_STRING(" OK [READ-WRITE] SELECT completed\r\n");
      else
         sResponse += pArgument->Tag() + PLATFORM_STRING(" OK [READ-ONLY] SELECT completed\r\n");


      pConnection->SendAsciiData(sResponse);   
 
      return IMAPResult();
   }
}