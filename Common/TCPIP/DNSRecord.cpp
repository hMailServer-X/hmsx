#include "pch.h"

#include "DNSRecord.h"

namespace HM
{
   DNSRecord::DNSRecord(AnsiString value, int recordType, int preference)
   {
      value_ = value;
      record_type_ = recordType;
      preference_ = preference;
   }
}
