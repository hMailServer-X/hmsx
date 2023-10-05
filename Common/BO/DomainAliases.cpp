#include "pch.h"

#include "DomainAliases.h"
#include "DomainAlias.h"
#include "Domain.h"

#include "../Persistence/PersistentDomain.h"
#include "../Cache/CacheContainer.h"

namespace HM
{
   DomainAliases::DomainAliases(long long iDomainID) :
      domain_id_(iDomainID)
   {
   }

   DomainAliases::~DomainAliases(void)
   {
   }

   void 
   DomainAliases::Refresh()
   {
      String sSQL;

      if (domain_id_)
         sSQL.Format(PLATFORM_STRING("select * from hm_domain_aliases where dadomainid = %I64d order by daid asc"), domain_id_);
      else
         sSQL.Format(PLATFORM_STRING("select * from hm_domain_aliases order by daid asc"), domain_id_);

      DBLoad_(sSQL);
   }

   String 
   DomainAliases::ApplyAliasesOnAddress(const String &sAddress)
   {
      const String sDomainName = StringParser::ExtractDomain(sAddress);
      const String sMailbox = StringParser::ExtractAddress(sAddress);

      // Iterate over the domains to find a match.
      auto iterAccount = vecObjects.begin();
      
      for(std::shared_ptr<DomainAlias> pFA : vecObjects)
      {
         if (pFA->GetAlias().CompareNoCase(sDomainName) == 0)
         {
            // We found the domain ID
            long long iDomainID = pFA->GetDomainID();
         
            std::shared_ptr<const Domain> pDomain = CacheContainer::Instance()->GetDomain(iDomainID);
            
            if (!pDomain)
               return sAddress;

            String sRetVal = sMailbox + "@" + pDomain->GetName();
         
            return sRetVal; 
         }
      }

      return sAddress;
   }

   bool
   DomainAliases::PreSaveObject(std::shared_ptr<DomainAlias> pDA, XNode *node)
   {
      pDA->SetDomainID(domain_id_);
      return true;
   }
}