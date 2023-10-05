#pragma once

#include "../Common/Cache/Cache.h"

namespace HM
{
   class Messages;
   class CachedMessages;

   class MessagesContainer : public Singleton<MessagesContainer>
   {
   public:

      MessagesContainer();

      std::shared_ptr<Messages> GetMessages(long long account_id, long long folder_id);
      std::shared_ptr<Messages> GetMessages(long long account_id, long long folder_id, std::set<long long> &recent_messages, bool update_recent_messages);

      void SetFolderNeedsRefresh(long long folder_id);
      void UncacheAccount(long long account_id);
      void Clear();

   private:
      
      Cache<CachedMessages> messages_cache_;


   };
}
