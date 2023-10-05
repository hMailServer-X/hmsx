#include "pch.h"
#include "BlockedAttachments.h"
#include "../Persistence/PersistentBlockedAttachment.h"

namespace HM
{
   BlockedAttachments::BlockedAttachments()
   {
   }

   BlockedAttachments::~BlockedAttachments(void)
   {
   }


   void 
   BlockedAttachments::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all SURBL servers from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = PLATFORM_STRING("select * from hm_blocked_attachments order by bawildcard asc");
      DBLoad_(sSQL);
   }

}