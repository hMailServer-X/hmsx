#include "pch.h"
#include "Aliases.h"

namespace HM
{
   Aliases::Aliases(long long iDomainID) :
      domain_id_(iDomainID)
   {

   }

   Aliases::~Aliases()
   {
   }

   void
   Aliases::Refresh()
   {
      String sSQL;
      sSQL.Format(PLATFORM_STRING("select * from hm_aliases where aliasdomainid = %I64d order by aliasname asc"), domain_id_);

      DBLoad_(sSQL);
   }

   bool
   Aliases::PreSaveObject(std::shared_ptr<Alias> pAlias, XNode *node)
   {
      pAlias->SetDomainID(domain_id_);

      return true;
   }

}
