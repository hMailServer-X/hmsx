#pragma once

namespace HM
{
   class Message;
   class Account;
   class IMAPFolder;

   class FolderManager
   {
   public:
      FolderManager(void);
      ~FolderManager(void);

      bool GetInboxMessages(int accountID, std::vector<std::shared_ptr<Message> > &result);
      bool DeleteInboxMessages(int accountID, std::set<int> uids, const std::function<void()> &callbackEvery1000Message);

      bool UpdateMessageFlags(int accountID, int folderID, long long messageID, int flags);

	private:


   };
}