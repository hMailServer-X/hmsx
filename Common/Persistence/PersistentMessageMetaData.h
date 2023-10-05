#pragma once

#include "../BO/MessageMetaData.h"

namespace HM
{
   class Message;

   class PersistentMessageMetaData
   {
   public:

      class MessageInfo
      {
      public:
         long long MessageID;
         int AccountID;
         int FolderID;
         String FileName;
      };

      PersistentMessageMetaData(void);
      ~PersistentMessageMetaData(void);

      // quickIndex param added to choose new faster/limiting option
      std::set<std::shared_ptr<MessageInfo> > GetMessagesToIndex(bool quickIndex);

      bool DeleteForMessage(std::shared_ptr<Message> message);
      void GetMetaData(int accountID, int folderID, const String &headerField, std::map<long long, String > &result);
      bool SaveObject(std::shared_ptr<MessageMetaData> metaData);
      bool DeleteOrphanedItems();
      int GetTotalMessageCount();
      void Clear();
   };
}