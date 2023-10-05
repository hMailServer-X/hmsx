#include "pch.h"

#include "CacheConfiguration.h"
#include "CacheContainer.h"

namespace HM
{
   CacheConfiguration::CacheConfiguration()
   { 
   
   }

   CacheConfiguration::~CacheConfiguration()
   {
   
   }

   std::shared_ptr<PropertySet> 
   CacheConfiguration::GetSettings_() const
   {
      return Configuration::Instance()->GetSettings();
   }

   bool
   CacheConfiguration::GetUseCache() const
   {
      return (GetSettings_()->GetBool(PROPERTY_USECACHE));
   }

   void
   CacheConfiguration::SetUseCache(bool bEnabled)
   {
      GetSettings_()->SetBool(PROPERTY_USECACHE, bEnabled);
   }


   int
   CacheConfiguration::GetDomainCacheTTL() const
   {
      return (GetSettings_()->GetLong(PROPERTY_DOMAINCACHETTL));
   }

   void
   CacheConfiguration::SetDomainCacheTTL(int iNewVal)
   {
      GetSettings_()->SetLong(PROPERTY_DOMAINCACHETTL, iNewVal);
   }


   int
   CacheConfiguration::GetAccountCacheTTL() const
   {
      return (GetSettings_()->GetLong(PROPERTY_ACCOUNTCACHETTL));
   }

   void
   CacheConfiguration::SetAccountCacheTTL(int iNewVal)
   {
      GetSettings_()->SetLong(PROPERTY_ACCOUNTCACHETTL, iNewVal);
   }

   int
   CacheConfiguration::GetAliasCacheTTL() const
   {
      return (GetSettings_()->GetLong(PROPERTY_ALIASCACHETTL));
   }

   void
   CacheConfiguration::SetAliasCacheTTL(int iNewVal)
   {
      GetSettings_()->SetLong(PROPERTY_ALIASCACHETTL, iNewVal);
   }

   int
   CacheConfiguration::GetDistributionListCacheTTL() const
   {
      return (GetSettings_()->GetLong(PROPERTY_DISTRIBUTIONLISTCACHETTL));
   }

   void
   CacheConfiguration::SetDistributionListCacheTTL(int iNewVal)
   {
      GetSettings_()->SetLong(PROPERTY_DISTRIBUTIONLISTCACHETTL, iNewVal);
   }

   bool 
   CacheConfiguration::XMLStore(XNode *pBackupNode, int iOptions)
   {
      return true;
   }

   bool
   CacheConfiguration::XMLLoad(XNode *pBackupNode, int iRestoreOptions)
   {
      return true;
   }

}
