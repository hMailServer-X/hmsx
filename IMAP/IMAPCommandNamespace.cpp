#include "pch.h"

#include "IMAPCommandNamespace.h"
#include "IMAPConnection.h"
#include "IMAPSimpleCommandParser.h"
#include "IMAPConfiguration.h"

namespace HM
{
   IMAPResult
   IMAPCommandNamespace::ExecuteCommand(std::shared_ptr<HM::IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      std::shared_ptr<IMAPSimpleCommandParser> pParser = std::shared_ptr<IMAPSimpleCommandParser>(new IMAPSimpleCommandParser());
      pParser->Parse(pArgument);

      if (pParser->WordCount() < 1)
         return IMAPResult(IMAPResult::ResultBad, "NAMESPACE command requires exactly 0 parameter.");

      String sPublicFolderName = Configuration::Instance()->GetIMAPConfiguration()->GetIMAPPublicFolderName();
      String hierarchyDelimiter = Configuration::Instance()->GetIMAPConfiguration()->GetHierarchyDelimiter();
      hierarchyDelimiter.Replace(PLATFORM_STRING("\\"), PLATFORM_STRING("\\\\"));

      String sPersonalNamespace = "((\"\" \"" + hierarchyDelimiter + "\"))";
      String sOtherUsersNamespace = "NIL";
      String sSharedNamespaces = "((\"" + sPublicFolderName + "\" \"" + hierarchyDelimiter + "\"))";
      String sResponse;
      
      sResponse.Format(PLATFORM_STRING("* NAMESPACE %s %s %s\r\n"), sPersonalNamespace.c_str(), sOtherUsersNamespace.c_str(), sSharedNamespaces.c_str());
      sResponse += pArgument->Tag() + PLATFORM_STRING(" OK namespace command complete\r\n");

      pConnection->SendAsciiData(sResponse);   

      return IMAPResult();
   }
}