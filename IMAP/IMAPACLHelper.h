#pragma once

namespace HM
{
   class IMAPFolder;

   class IMAPACLHelper
   {
   public:

      IMAPACLHelper();
      virtual ~IMAPACLHelper();

      static String CreateACLList(std::shared_ptr<IMAPFolder> pFolder, const String &sEscapedFolderName);
      static bool IsValidPermissionString(const String &sPermissions);

   private:

   };


}