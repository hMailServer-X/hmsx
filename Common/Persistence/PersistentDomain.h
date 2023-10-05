#pragma once

namespace HM
{
   class Domain;
   enum PersistenceMode;

   class PersistentDomain
   {
   public:
	   PersistentDomain();
	   virtual ~PersistentDomain();

      static bool DeleteObject(std::shared_ptr<Domain> pDomain);
      static bool SaveObject(std::shared_ptr<Domain> pDomain);
      static bool SaveObject(std::shared_ptr<Domain> pDomain, String &sErrorMessage, PersistenceMode mode);

      static bool ReadObject(std::shared_ptr<Domain> pDomain, std::shared_ptr<DALRecordset> pRS);
      static bool ReadObject(std::shared_ptr<Domain> pDomain, const String & sDomainName);
      static bool ReadObject(std::shared_ptr<Domain> pDomain, const SQLCommand &command);
      static bool ReadObject(std::shared_ptr<Domain> pDomain, long long ObjectID);

      static bool DomainExists(const String &DomainName, bool &bIsActive);

      static int GetSize(std::shared_ptr<Domain> pDomain);
      static long long GetAllocatedSize(std::shared_ptr<Domain> pDomain);

   };

}
