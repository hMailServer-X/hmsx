#include "pch.h"
#include "DefaultDomain.h"

namespace HM
{
   DefaultDomain::DefaultDomain(void)
   {
   }

   DefaultDomain::~DefaultDomain(void)
   {
   }

   String 
   DefaultDomain::ApplyDefaultDomain(const String &sAddress)
   {     
      if (sAddress.Find(PLATFORM_STRING("@")) >= 0 || sAddress.IsEmpty())
         return sAddress;

      // Append default domain
      String sDefaultDomain = Configuration::Instance()->GetDefaultDomain();

      if (sDefaultDomain.IsEmpty())
         return sAddress;

      return sAddress + "@" + sDefaultDomain;
   }
}