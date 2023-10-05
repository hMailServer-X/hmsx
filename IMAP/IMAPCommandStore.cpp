#include "pch.h"
#include "IMAPCommandStore.h"
#include "IMAPStore.h"
#include "IMAPConnection.h"

namespace HM
{
   IMAPCommandStore::IMAPCommandStore()
   {

   }

   IMAPCommandStore::~IMAPCommandStore()
   {

   }

   IMAPResult
   IMAPCommandStore::ExecuteCommand(std::shared_ptr<IMAPConnection> pConnection, std::shared_ptr<IMAPCommandArgument> pArgument)
   {


      String sTag = pArgument->Tag();
      String sCommand = pArgument->Command();

      if (!pConnection->IsAuthenticated())
         return IMAPResult(IMAPResult::ResultNo, "Authenticate first");

      if (!pConnection->GetCurrentFolder())
         return IMAPResult(IMAPResult::ResultNo, "No folder selected.");


      std::shared_ptr<IMAPStore> pStore = std::shared_ptr<IMAPStore>(new IMAPStore());
      pStore->SetIsUID(false);

      String sResponse; 
      long lMailNoStart = 6;
      long lMailNoEnd = sCommand.Find(PLATFORM_STRING(" "), lMailNoStart);
      long lMailNoLen = lMailNoEnd - lMailNoStart;
      String sMailNo = sCommand.Mid(lMailNoStart, lMailNoLen);
      String sShowPart = sCommand.Mid(lMailNoEnd);

      pArgument->Command(sShowPart);

      IMAPResult result = pStore->DoForMails(pConnection, sMailNo, pArgument);

      if (result.GetResult() == IMAPResult::ResultOK)
         pConnection->SendAsciiData(pArgument->Tag() + " OK STORE completed\r\n");

      return result;
   }
}
