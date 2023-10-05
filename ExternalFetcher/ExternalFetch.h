#pragma once

namespace boost
{
   namespace system
   {
      class error_code;
   }
}
namespace HM
{
   class FetchAccount;
   class ClientInfo;

   class ExternalFetch
   {
   public:
      ExternalFetch(void);
      ~ExternalFetch(void);

      void Start(std::shared_ptr<FetchAccount> pFA);
   };
}