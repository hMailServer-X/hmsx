#include "pch.h"
#include "Maintenance.h"

namespace HM   
{
   Maintenance::Maintenance()
   {

   }

   Maintenance::~Maintenance()
   {

   }

   bool
   Maintenance::Perform(MaintenanceOperation operation)
   {
      switch (operation)
      {
      case RecalculateFolderUID:
         return RecalculateFolderUID_();
      }

      return false;
   }

   // Goes through all mailboxes and sets the foldercurrentuid to the latest message uid.
   bool
   Maintenance::RecalculateFolderUID_()
   {
      AnsiString recordSQL = "SELECT messagefolderid, MAX(messageuid) as messageuid FROM hm_messages GROUP BY messagefolderid";

      std::shared_ptr<DALRecordset> pRS = Application::Instance()->GetDBManager()->OpenRecordset(SQLCommand(recordSQL));

      if (!pRS)
         return false;

      while (!pRS->IsEOF())
      {
         long long messageFolderID = pRS->GetInt64Value("messagefolderid");
         long long messageUID = pRS->GetInt64Value("messageuid");

         if (messageFolderID <= 0)
            return false;

         if (messageUID <= 0)
            return false;

         AnsiString sqlUpdate = Formatter::Format("UPDATE hm_imapfolders SET foldercurrentuid = {0} WHERE folderid = {1} AND foldercurrentuid < {0}", messageUID, messageFolderID);

         bool result = Application::Instance()->GetDBManager()->Execute(SQLCommand(sqlUpdate));
         if (result == false)
            return false;
            
         pRS->MoveNext();
      }

      return true;
   }

}