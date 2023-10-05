#pragma once

namespace HM
{
   class ACLPermission;
   enum PersistenceMode;
   class PersistentACLPermission
   {
   public:
      PersistentACLPermission(void);
      ~PersistentACLPermission(void);
      
      static bool Validate(std::shared_ptr<ACLPermission> pObject);
      static bool DeleteOwnedByAccount(long long iAccountID);
      static bool DeleteOwnedByGroup(long long groupID);
      static bool DeleteObject(std::shared_ptr<ACLPermission> pObject);
      static bool SaveObject(std::shared_ptr<ACLPermission> pObject);
      static bool SaveObject(std::shared_ptr<ACLPermission> pObject, String &errorMessage, PersistenceMode mode);
      static bool ReadObject(std::shared_ptr<ACLPermission> pObject, std::shared_ptr<DALRecordset> pRS);

   };
}