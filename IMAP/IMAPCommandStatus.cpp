#include "pch.h"
#include "IMAPCommandStatus.h"

#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"
#include "../Common/BO/IMAPFolders.h"
#include "../Common/BO/ACLPermission.h"
#include "../Common/BO/IMAPFolder.h"

namespace HM
{
   
   IMAPResult
   IMAPCommandSTATUS::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {

      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());

      pParser->Parse(pArgument);

      if (pParser->ParamCount() != 1 && pParser->ParamCount() != 2)
         return IMAPResult(IMAPResult::ResultBad, "STATUS Command requires 1 or 2 parameters.");

      String sFolderName = pParser->GetParamValue(pArgument, 0);
      String sFlags = pParser->GetParamValue(pArgument, 1);

      std::shared_ptr<IMAPFolder> pTheFolder = pConnection->GetFolderByFullPath(sFolderName);
      if (!pTheFolder)
         return IMAPResult(IMAPResult::ResultBad, "Folder could not be found.");

      // Check if ther user has access to read this folder.
      if (!pConnection->CheckPermission(pTheFolder, ACLPermission::PermissionRead))
         return IMAPResult(IMAPResult::ResultBad, "ACL: Read permission denied (Required for STATUS command).");

      // Check if ther user has access to read this folder.
      if (!pConnection->CheckPermission(pTheFolder, ACLPermission::PermissionRead))
         return IMAPResult(IMAPResult::ResultBad, "ACL: Read permission denied.");

      std::shared_ptr<Messages> pMessages = pTheFolder->GetMessages();
      
      String sResponse = "";

      bool bAddSpace = false;

      sResponse = "* STATUS \"" + sFolderName + "\" ";

      sResponse+= "(";
      if (sFlags.FindNoCase(PLATFORM_STRING("MESSAGES")) >= 0)
      {
         String sTemp;
         sTemp.Format(PLATFORM_STRING("MESSAGES %d"), pMessages->GetCount());
         
         if (bAddSpace)
            sResponse += " ";
         else
            bAddSpace = true;

         sResponse +=sTemp;
        
      }

      if (sFlags.FindNoCase(PLATFORM_STRING("UNSEEN")) >= 0)
      {
         String sTemp;
         long lMsgCount = pMessages->GetCount();
         long lSeen = pMessages->GetNoOfSeen();
         long lUnseen = lMsgCount - lSeen;
         sTemp.Format(PLATFORM_STRING("UNSEEN %d"), lUnseen);


         if (bAddSpace)
            sResponse += " ";
         else
            bAddSpace = true;

         sResponse +=sTemp;
      }

      if (sFlags.FindNoCase(PLATFORM_STRING("RECENT")) >= 0)
      {
         String sTemp;
         long lNoOfRecent = (int) pConnection->GetRecentMessages().size();
         sTemp.Format(PLATFORM_STRING("RECENT %d"), lNoOfRecent);

         if (bAddSpace)
            sResponse += " ";
         else
            bAddSpace = true;

         sResponse +=sTemp;
      }

      if (sFlags.FindNoCase(PLATFORM_STRING("UIDNEXT")) >= 0)
      {
         String sTemp;
         sTemp.Format(PLATFORM_STRING("UIDNEXT %u"),  pTheFolder->GetCurrentUID() + 1);

         if (bAddSpace)
            sResponse += " ";
         else
            bAddSpace = true;

         sResponse += sTemp;
      }

      if (sFlags.FindNoCase(PLATFORM_STRING("UIDVALIDITY")) >= 0)
      {

         String sTemp;
         sTemp.Format(PLATFORM_STRING("UIDVALIDITY %d"), pTheFolder->GetCreationTime().ToInt());

         if (bAddSpace)
            sResponse += " ";
         else
            bAddSpace = true;

         sResponse +=sTemp;
      }


      sResponse+= ")\r\n";

      sResponse += pArgument->Tag() + " OK Status completed\r\n";

      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }  
}