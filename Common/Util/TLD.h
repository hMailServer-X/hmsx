#pragma once

namespace HM
{
   class TLD : public Singleton<TLD>
   {
   public:

      TLD(void);
      ~TLD(void);

      void Initialize();
      bool IsTLD(const String &sName);

      bool GetDomainNameFromHost(String &sHost, bool &bIsIPAddress);

   private:

      std::set<String> tld_;
   };
}