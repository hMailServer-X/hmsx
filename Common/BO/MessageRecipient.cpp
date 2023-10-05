#include "pch.h"
#include "messagerecipient.h"

namespace HM
{
   MessageRecipient::MessageRecipient()  :
      result_ (ResultUndefined),
      local_account_id_(0),
      message_id_(0),
      requires_authentication_(false),
      is_local_name_(false)
   {

   }

   void
   MessageRecipient::CopyFrom(std::shared_ptr<MessageRecipient> pRecip)
   {
      address_ = pRecip->GetAddress();
      local_account_id_ = pRecip->GetLocalAccountID();
      message_id_ = pRecip->GetMessageID();
      original_address_ = pRecip->GetOriginalAddress();

      requires_authentication_ = pRecip->GetRequireAuth();
      required_sender_ = pRecip->GetRequiredSender();

      is_local_name_ = pRecip->GetIsLocalName();
   }

   MessageRecipient::~MessageRecipient(void)
   {
   }



}
