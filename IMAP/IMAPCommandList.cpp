#include "pch.h"
#include "IMAPCommandList.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"
#include "../Common/BO/Account.h"
#include "../Common/BO/IMAPFolders.h"

#include "FolderListCreator.h"
#include "IMAPConfiguration.h"

namespace HM
{
   IMAPCommandLIST::IMAPCommandLIST()
   {

   }

   IMAPCommandLIST::~IMAPCommandLIST()
   {

   }

   IMAPResult
   IMAPCommandLIST::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      String sTag = pArgument->Tag();
      String sCommand = pArgument->Command();

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());

      pParser->Parse(pArgument);

      if (pParser->ParamCount() != 2)
         return IMAPResult(IMAPResult::ResultBad, "LIST Command requires 2 parameters.");

      // Read parameters
      String sReferenceName = pParser->GetParamValue(pArgument, 0);
      String sWildcards = pParser->GetParamValue(pArgument, 1);

      String hierarchyDelimiter = Configuration::Instance()->GetIMAPConfiguration()->GetHierarchyDelimiter();

      String folderSpecifier = sWildcards;
      if (sReferenceName.GetLength() > 0)
         folderSpecifier = sReferenceName + folderSpecifier;

      std::shared_ptr<IMAPFolders> pFolders = pConnection->GetAccountFolders();
      std::shared_ptr<IMAPFolders> pPublicFolders = pConnection->GetPublicFolders();

      if (!pFolders || !pPublicFolders)
         return IMAPResult(IMAPResult::ResultNo, "LIST failed - No folders.");

      String sPublicFolderName = Configuration::Instance()->GetIMAPConfiguration()->GetIMAPPublicFolderName(); 

      String sResult =  FolderListCreator::GetIMAPFolderList(pConnection->GetAccount()->GetID(), pFolders, folderSpecifier, "") + 
                        FolderListCreator::GetIMAPFolderList(pConnection->GetAccount()->GetID(), pPublicFolders, folderSpecifier, sPublicFolderName);

      if (sResult.IsEmpty() && sWildcards.IsEmpty())
      {
         hierarchyDelimiter.Replace(PLATFORM_STRING("\\"), PLATFORM_STRING("\\\\"));
         sResult = PLATFORM_STRING("* LIST (\\Noselect) \"") + hierarchyDelimiter + PLATFORM_STRING("\" \"\"\r\n");
      }

      sResult += sTag + " OK LIST completed\r\n";
      pConnection->SendAsciiData(sResult);   

      return IMAPResult();
   }
}
