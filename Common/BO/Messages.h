#pragma once

#include "Collection.h"
#include "../BO/Message.h"
#include "../Persistence/PersistentMessage.h"

namespace HM
{

   class Messages : public Collection<Message, PersistentMessage>
   {
   public:
	   Messages(long long iAccountID, long long iFolderID);
	   virtual ~Messages();

      void Save();

      long GetSize() const;
      long long GetFirstUnseenUID() const;
      long GetNoOfSeen() const;
      
      std::vector<std::shared_ptr<Message>> GetCopy();

      std::shared_ptr<Message> GetItemByUID(unsigned int uid);
      std::shared_ptr<Message> GetItemByUID(unsigned int uid, unsigned int &foundIndex);

      void DeleteMessages(std::function<bool(int, std::shared_ptr<Message>)> &filter);

      void Refresh(bool update_recent_flags);

      void AddToCollection(std::shared_ptr<DALRecordset> pRS);
      
      void Remove(long long iDBID);

      void RemoveRecentFlags();

      long long GetAccountID() {return account_id_; }
      long long GetFolderID() {return folder_id_; }

   protected:
      virtual String GetCollectionName() const {return "Messages"; }
      virtual bool PreSaveObject(std::shared_ptr<Message> pMessage, XNode *node);
   private:

      unsigned int last_refreshed_uid_;

      long long account_id_;
      long long folder_id_;
   };
}
