#include "pch.h"
#include "./externalfetchtask.h"

#include "ExternalFetch.h"
#include "../Common/BO/FetchAccount.h"
#include "../Common/Persistence/PersistentFetchAccount.h"

namespace HM
{
   ExternalFetchTask::ExternalFetchTask(std::shared_ptr<FetchAccount> pFA) : 
      Task("ExternalFetchTask"),
      fetch_account_(pFA)
   {
   }

   ExternalFetchTask::~ExternalFetchTask(void)
   {
   }

   void 
   ExternalFetchTask::DoWork()
   {
      // Do the actual delivery of the message.
      ExternalFetch oFetcher;
      oFetcher.Start(fetch_account_);

      // Set next fetch time 
      PersistentFetchAccount::SetNextTryTime(fetch_account_);

      // Unlock the account
      PersistentFetchAccount::Unlock(fetch_account_->GetID());
   }

}