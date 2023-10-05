#pragma once

namespace HM
{
   class GreyListingWhiteAddress;
   enum PersistenceMode;

   class PersistentGreyListingWhiteAddress
   {
   public:
      PersistentGreyListingWhiteAddress(void);
      ~PersistentGreyListingWhiteAddress(void);
      
      static bool DeleteObject(std::shared_ptr<GreyListingWhiteAddress> pObject);
      static bool SaveObject(std::shared_ptr<GreyListingWhiteAddress> pObject, String &errorMessage, PersistenceMode mode);
      static bool SaveObject(std::shared_ptr<GreyListingWhiteAddress> pObject);
      static bool ReadObject(std::shared_ptr<GreyListingWhiteAddress> pObject, std::shared_ptr<DALRecordset> pRS);

      static bool IsSenderWhitelisted(const String &address);
   };
}