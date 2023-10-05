#pragma once

namespace HM
{
   class DefaultDomain
   {
   public:
      DefaultDomain(void);
      ~DefaultDomain(void);

      static String ApplyDefaultDomain(const String &sAddress);
   };
}