#pragma once

namespace HM
{
   class Domain;

   class PlusAddressing
   {
   public:
      PlusAddressing(void);
      ~PlusAddressing(void);
   
      static String ExtractAccountAddress(const String &sAddress, std::shared_ptr<const Domain> pDomain);
      
   private:
   };
}