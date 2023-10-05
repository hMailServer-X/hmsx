#pragma once

namespace HM
{
   class SSLCertificate;
   enum  PersistenceMode;

   class PersistentSSLCertificate
   {
   public:
      PersistentSSLCertificate(void);
      ~PersistentSSLCertificate(void);
      
      static bool DeleteObject(std::shared_ptr<SSLCertificate> pObject);
      static bool SaveObject(std::shared_ptr<SSLCertificate> pObject);
      static bool SaveObject(std::shared_ptr<SSLCertificate> pObject, String &errorMessage,  PersistenceMode mode);
      static bool ReadObject(std::shared_ptr<SSLCertificate> pObject, std::shared_ptr<DALRecordset> pRS);

   };
}