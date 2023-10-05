#include "pch.h"
#include "./passwordvalidator.h"

#include "../Application/ObjectCache.h"
#include "../Application/DefaultDomain.h"
#include "../Cache/CacheContainer.h"
#include "../BO/Account.h"
#include "../BO/Domain.h"
#include "../BO/DomainAliases.h"
#include "../Util/Crypt.h"

namespace HM
{
   PasswordValidator::PasswordValidator(void)
   {
   }

   PasswordValidator::~PasswordValidator(void)
   {
   }

   std::shared_ptr<const Account>
   PasswordValidator::ValidatePassword(const String &sUsername, const String &sPassword)
   {
	   return PasswordValidator::ValidatePassword(PLATFORM_STRING(""), sUsername, sPassword);
   }

   std::shared_ptr<const Account>
   PasswordValidator::ValidatePassword(const String &sMasqname, const String &sUsername, const String &sPassword)
   {
      std::shared_ptr<Account> pEmpty;

      // Apply domain name aliases to this domain name.
      std::shared_ptr<DomainAliases> pDA = ObjectCache::Instance()->GetDomainAliases();
      String sAccountAddress = pDA->ApplyAliasesOnAddress(sUsername);

      // Apply default domain
      sAccountAddress = DefaultDomain::ApplyDefaultDomain(sAccountAddress);

      std::shared_ptr<const Account> pAccount = CacheContainer::Instance()->GetAccount(sAccountAddress);
      
      if (!pAccount)
         return pEmpty;

      if (!pAccount->GetActive())
         return pEmpty;

      // Check that the domain is active as well.
      
      String sDomain = StringParser::ExtractDomain(sAccountAddress);
      std::shared_ptr<const Domain> pDomain = CacheContainer::Instance()->GetDomain(sDomain);

      if (!pDomain)
         return pEmpty;

      if (!pDomain->GetIsActive())
         return pEmpty;

      if (!ValidatePassword(pAccount, sPassword))
         return pEmpty;

      if (sMasqname.GetLength() == 0)
	      return pAccount;

      // if we get this far, we are authenticating against one username, but will actually login
      // as a second username (rfc-4616)

      // Apply domain name aliases to this domain name.
      pDA = ObjectCache::Instance()->GetDomainAliases();
      sAccountAddress = pDA->ApplyAliasesOnAddress(sMasqname);

      // Apply default domain
      sAccountAddress = DefaultDomain::ApplyDefaultDomain(sAccountAddress);

      pAccount = CacheContainer::Instance()->GetAccount(sAccountAddress);

      if (!pAccount)
	      return pEmpty;

      if (!pAccount->GetActive())
	      return pEmpty;

      // Check that the domain is active as well.

      sDomain = StringParser::ExtractDomain(sAccountAddress);
      pDomain = CacheContainer::Instance()->GetDomain(sDomain);

      if (!pDomain)
	      return pEmpty;

      if (!pDomain->GetIsActive())
	      return pEmpty;

      return pAccount;
   }

   bool 
   PasswordValidator::ValidatePassword(std::shared_ptr<const Account> pAccount, const String &sPassword)
   {

     

      if (sPassword.GetLength() == 0)
      {
         // Empty passwords are not permitted.
         return false;
      }


      Crypt::EncryptionType iPasswordEncryption = (Crypt::EncryptionType) pAccount->GetPasswordEncryption();

      String sComparePassword = pAccount->GetPassword();

      if (iPasswordEncryption == 0)
      {
         // Do plain text comparision

         // POTENTIAL TO BREAK BACKWARD COMPATIBILITY
         // Unencrypted passwords are not case sensitive so these changes WOULD fix that
         // but could cause problems for people who've been relying on them not being
         // case sensitive. Perhaps this needs to be optional before implementing.
         // 
         // if (sPassword.Compare(sComparePassword) != 0)
         //   return false;
         //
         sComparePassword.MakeLower();
         if (sPassword.CompareNoCase(sComparePassword) != 0)
            return false;
      }
      else if (iPasswordEncryption == Crypt::ETMD5 ||
               iPasswordEncryption == Crypt::ETSHA256)
      {
         // Compare hashs
         bool result = Crypt::Instance()->Validate(sPassword, sComparePassword, iPasswordEncryption);

         if (!result)
            return false;
      }
      else if (iPasswordEncryption == Crypt::ETBlowFish)
      {
         String decrypted = Crypt::Instance()->DeCrypt(sComparePassword, iPasswordEncryption);

         if (sPassword.CompareNoCase(decrypted) != 0)
            return false;
      }
      else
         return false;

      return true;
   }

}