
#include "pch.h"
#include "./messagerecipients.h"
#include "./MessageRecipient.h"

namespace HM
{
   MessageRecipients::MessageRecipients(void)
   {
   }

   MessageRecipients::~MessageRecipients(void)
   {
   }

   void
   MessageRecipients::Clear()
   {
      recipients_.clear();
   }


   void
   MessageRecipients::Add(std::shared_ptr<MessageRecipient> pRecipient)
   {
      recipients_.push_back(pRecipient);
   }

   String 
   MessageRecipients::GetCommaSeperatedRecipientList()
   {
      String sRecipientList;

      for(std::shared_ptr<MessageRecipient> recipient : recipients_)
      {
         if (!sRecipientList.IsEmpty())
            sRecipientList += ", ";

         sRecipientList += recipient->GetAddress();
      }

      return sRecipientList;

   }

   void 
   MessageRecipients::RemoveNonLocalAccounts()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Removes all non-local recipients.
   //---------------------------------------------------------------------------()
   {
      // Remove recipients that are local, but does not exist.
      auto iterRecipient = recipients_.begin();
      while (iterRecipient != recipients_.end())
      {
         std::shared_ptr<MessageRecipient> pRecipient = (*iterRecipient);

         if (pRecipient->GetLocalAccountID() == 0)
         {     
            iterRecipient = recipients_.erase(iterRecipient);
            continue;
         }

         iterRecipient++;

      }
   }

   void 
   MessageRecipients::RemoveExternal()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Removes recipients not considered local.
   //---------------------------------------------------------------------------()
   {
      // Remove recipients that are local, but does not exist.
      auto iterRecipient = recipients_.begin();
      while (iterRecipient != recipients_.end())
      {
         std::shared_ptr<MessageRecipient> pRecipient = (*iterRecipient);

         if (!pRecipient->GetIsLocalName())
         {     
            iterRecipient = recipients_.erase(iterRecipient);
            continue;
         }

         iterRecipient++;

      }
   }

}