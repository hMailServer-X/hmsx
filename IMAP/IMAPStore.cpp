#include "pch.h"
#include "IMAPStore.h"
#include "IMAPConnection.h"

#include "../Common/Application/FolderManager.h"
#include "../Common/BO/Message.h"
#include "../Common/BO/IMAPFolder.h"
#include "../Common/BO/ACLPermission.h"

#include "../Common/Tracking/ChangeNotification.h"
#include "../Common/Tracking/NotificationServer.h"

namespace HM
{

   IMAPStore::IMAPStore()
   {

   }

   IMAPStore::~IMAPStore()
   {
      
   }


   IMAPResult
   IMAPStore::DoAction(std::shared_ptr<IMAPConnection> pConnection, int messageIndex,  std::shared_ptr<Message> pMessage, const std::shared_ptr<IMAPCommandArgument> pArgument)
   {
      if (!pMessage || !pArgument)
         return IMAPResult(IMAPResult::ResultBad, "Invalid parameters");

      if (pConnection->GetCurrentFolderReadOnly())
      {
         return IMAPResult(IMAPResult::ResultNo, "Store command on read-only folder.");
      }

      bool bSilent = false;

      String sCommand = pArgument->Command();
      if (sCommand.FindNoCase(PLATFORM_STRING("FLAGS.SILENT")) >= 0)
         bSilent = true;
      else
         bSilent = false;

      // Read flags from command.
      bool bSeen = (sCommand.FindNoCase(PLATFORM_STRING("\\Seen")) >= 0);
      bool bDeleted = (sCommand.FindNoCase(PLATFORM_STRING("\\Deleted")) >= 0);
      bool bDraft = (sCommand.FindNoCase(PLATFORM_STRING("\\Draft")) >= 0);
      bool bAnswered = (sCommand.FindNoCase(PLATFORM_STRING("\\Answered")) >= 0);
      bool bFlagged = (sCommand.FindNoCase(PLATFORM_STRING("\\Flagged")) >= 0);
   
      if (bSeen)
      {
         // ACL: If user tries to change the Seen flag, check that he has permission to do so.
         if (!pConnection->CheckPermission(pConnection->GetCurrentFolder(), ACLPermission::PermissionWriteSeen))
            return IMAPResult(IMAPResult::ResultNo, "ACL: WriteSeen permission denied (Required for STORE command).");
      }

      if (bDeleted)
      {
         if (!pConnection->CheckPermission(pConnection->GetCurrentFolder(), ACLPermission::PermissionWriteDeleted))
            return IMAPResult(IMAPResult::ResultNo, "ACL: DeleteMessages permission denied (Required for STORE command).");
      }

      if (bDraft || bAnswered || bFlagged)
      {
         if (!pConnection->CheckPermission(pConnection->GetCurrentFolder(), ACLPermission::PermissionWriteOthers))
            return IMAPResult(IMAPResult::ResultNo, "ACL: WriteOthers permission denied (Required for STORE command).");
      }


      if (sCommand.FindNoCase(PLATFORM_STRING("-FLAGS")) >= 0)
      {
         // Remove flags
         if (bSeen)
            pMessage->SetFlagSeen(false);
         if (bDeleted)
            pMessage->SetFlagDeleted(false);
         if (bDraft)
            pMessage->SetFlagDraft(false);
         if (bAnswered)
            pMessage->SetFlagAnswered(false);
         if (bFlagged)
            pMessage->SetFlagFlagged(false);



      }
      else if (sCommand.FindNoCase(PLATFORM_STRING("+FLAGS")) >= 0)
      {
         // Add flags
         if (bSeen)
            pMessage->SetFlagSeen(true);
         if (bDeleted)
            pMessage->SetFlagDeleted(true);
         if (bDraft)
            pMessage->SetFlagDraft(true);
         if (bAnswered)
            pMessage->SetFlagAnswered(true);
         if (bFlagged)
            pMessage->SetFlagFlagged(true);
       
      }
      else if (sCommand.FindNoCase(PLATFORM_STRING("FLAGS")) >= 0)
      {
         // Set flags
         pMessage->SetFlagSeen(bSeen);
         pMessage->SetFlagDeleted(bDeleted);
         pMessage->SetFlagDraft(bDraft);
         pMessage->SetFlagAnswered(bAnswered);
         pMessage->SetFlagFlagged(bFlagged);
      }

      bool result = Application::Instance()->GetFolderManager()->UpdateMessageFlags(
         (int) pConnection->GetCurrentFolder()->GetAccountID(), 
         (int) pConnection->GetCurrentFolder()->GetID(),
         pMessage->GetID(), pMessage->GetFlags());

      if (!result)
      {
         return IMAPResult(IMAPResult::ResultNo, "Unable to store message flags.");
      }

      if (!bSilent)
      {
         pConnection->SendAsciiData(GetMessageFlags(pMessage, messageIndex));
      }

      // BEGIN IMAP IDLE

      // Notify the mailbox notifier that the mailbox contents have changed.
      std::vector<long long> effectedMessages;
      effectedMessages.push_back(pMessage->GetID());

      std::shared_ptr<ChangeNotification> pNotification = 
         std::shared_ptr<ChangeNotification>(new ChangeNotification(pConnection->GetCurrentFolder()->GetAccountID(), pConnection->GetCurrentFolder()->GetID(),  ChangeNotification::NotificationMessageFlagsChanged, effectedMessages));

      Application::Instance()->GetNotificationServer()->SendNotification(pConnection->GetNotificationClient(), pNotification);
      // END IMAP IDLE

      return IMAPResult();
   }

   String 
   IMAPStore::GetMessageFlags(std::shared_ptr<Message> pMessage, int messageIndex)
   {
      // Build a flags string.
      String sFlags;

      if (pMessage->GetFlagDeleted())
      {
         if (!sFlags.IsEmpty()) 
            sFlags += " ";

         sFlags += "\\Deleted";
      }

      if (pMessage->GetFlagAnswered())
      {
         if (!sFlags.IsEmpty()) 
            sFlags += " ";

         sFlags += "\\Answered";
      }

      if (pMessage->GetFlagFlagged())
      {
         if (!sFlags.IsEmpty()) 
            sFlags += " ";

         sFlags += "\\Flagged";
      }

      if (pMessage->GetFlagDraft())
      {
         if (!sFlags.IsEmpty()) 
            sFlags += " ";

         sFlags += "\\Draft";
      }

      if (pMessage->GetFlagSeen())
      {
         if (!sFlags.IsEmpty()) 
            sFlags += " ";

         sFlags += "\\Seen";
      }


      // It really should be FETCH below...
      String sRet;
      sRet.Format(PLATFORM_STRING("* %d FETCH (FLAGS (%s) UID %u)\r\n"), messageIndex, sFlags.c_str(), pMessage->GetUID());
      return sRet;
   }
      

}
