#pragma once

#include "../../Start/pch.h"

#include "DNSRecord.h"

namespace HM
{


   class DNSResolverWinApi
   {
   public:
      DNSResolverWinApi();
      virtual ~DNSResolverWinApi();

      bool Query(const String &query, int resourceType, std::vector<DNSRecord> &foundRecords);

   private:

      bool IsDNSError_(int iErrorMessage);
   };


}
