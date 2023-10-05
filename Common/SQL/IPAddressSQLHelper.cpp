#include "pch.h"
#include "IPAddressSQLHelper.h"

namespace HM
{
   IPAddressSQLHelper::IPAddressSQLHelper()
   {

   }

   AnsiString 
   IPAddressSQLHelper::GetAddress1String(const IPAddress &address) const
   {
      String s;
      s.Format(PLATFORM_STRING("%I64d"), address.GetAddress1());
      
      return s;
   }

   AnsiString 
   IPAddressSQLHelper::GetAddress2String(const IPAddress &address) const
   {
      if (address.GetType() == IPAddress::IPV4)
         return "NULL";

      String s;
      s.Format(PLATFORM_STRING("%I64d"), address.GetAddress2());
      return s;
   }
   
   AnsiString 
   IPAddressSQLHelper::GetAddress1Equals(const IPAddress &address) const
   {
      String s;
      s.Format(PLATFORM_STRING("= %I64d"), address.GetAddress1());

      return s;
   }

   AnsiString 
   IPAddressSQLHelper::GetAddress2Equals(const IPAddress &address) const
   {
      if (address.GetType() == IPAddress::IPV4)
         return "IS NULL";

      String s;
      s.Format(PLATFORM_STRING("= %I64d"), address.GetAddress2());
      return s;
   }

   IPAddress 
   IPAddressSQLHelper::Construct(std::shared_ptr<DALRecordset> recordset, const AnsiString &address1Column, const AnsiString &address2Column) const
   {
      long long address1 = recordset->GetInt64Value(address1Column);

      if (recordset->GetIsNull(address2Column))
      {
         return IPAddress(address1);
      }
      
      long long address2 = recordset->GetInt64Value(address2Column);

      return IPAddress(address1, address2);
   }

   void 
   IPAddressSQLHelper::AppendStatement(SQLStatement &statement, const IPAddress &address, const AnsiString &address1Column, const AnsiString &address2Column) const
   {
      statement.AddColumnInt64(address1Column, address.GetAddress1());
      
      if (address.GetType() == IPAddress::IPV6)
         statement.AddColumnInt64(address2Column, address.GetAddress2());
      else
         statement.AddColumnNULL(address2Column);

   }

}
