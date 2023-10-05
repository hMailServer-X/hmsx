#include "pch.h"
#include "IMAPCommandDelete.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"
#include "../Common/BO/IMAPFolders.h"
#include "../Common/BO/IMAPFolder.h"
#include "../Common/Persistence/PersistentIMAPFolder.h"
#include "../Common/BO/ACLPermission.h"

namespace HM
{
   IMAPResult
   IMAPCommandDELETE::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      String sResponse = pArgument->Tag() + " OK Delete completed\r\n";
   
      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());

      
      pParser->Parse(pArgument);

      if (pParser->ParamCount() != 1)
         return IMAPResult(IMAPResult::ResultBad, "Command requires 1 parameter.");

      // Fetch the folder
      String sFolderName = pParser->GetParamValue(pArgument, 0);

      if (sFolderName.CompareNoCase(PLATFORM_STRING("Inbox")) == 0)
         return IMAPResult(IMAPResult::ResultNo, "You cannot delete the inbox.");
         
      std::shared_ptr<IMAPFolder> pFolder = pConnection->GetFolderByFullPath(sFolderName);
      if (!pFolder)
         return IMAPResult(IMAPResult::ResultNo, "Folder could not be found.");

      // Check if the user has access to rename this folder
      if (!pConnection->CheckPermission(pFolder, ACLPermission::PermissionDeleteMailbox))
         return IMAPResult(IMAPResult::ResultNo, "ACL: DeleteMailbox permission denied (required for DELETE).");
      
      PersistentIMAPFolder::DeleteObject(pFolder);

      RemoveFolder_(pFolder, pConnection);

      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }

   /*
      Removes the folder from the in-memory list.
   */
   void IMAPCommandDELETE::RemoveFolder_( std::shared_ptr<IMAPFolder> pFolder, std::shared_ptr<HM::IMAPConnection>  pConnection )
   {
      long long parentFolderID = pFolder->GetParentFolderID();

      std::shared_ptr<IMAPFolders> parentFolderCollection;

      if (pFolder->IsPublicFolder())
      {
         if (parentFolderID >= 0)
            parentFolderCollection = pConnection->GetPublicFolders()->GetItemByDBIDRecursive(parentFolderID)->GetSubFolders();
         else
            parentFolderCollection = pConnection->GetPublicFolders();
      }
      else
      {
         if (parentFolderID >= 0)
            parentFolderCollection = pConnection->GetAccountFolders()->GetItemByDBIDRecursive(parentFolderID)->GetSubFolders();
         else
            parentFolderCollection = pConnection->GetAccountFolders();
      }

      if (parentFolderCollection)
         parentFolderCollection->RemoveFolder(pFolder);
   }
}