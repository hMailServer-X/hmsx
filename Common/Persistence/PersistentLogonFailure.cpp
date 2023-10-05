#include "pch.h"

#include "PersistentLogonFailure.h"
#include "../SQL/IPAddressSQLHelper.h"

namespace HM   
{
   PersistentLogonFailure::PersistentLogonFailure()
   {

   }

   PersistentLogonFailure::~PersistentLogonFailure()
   {

   }

   int 
   PersistentLogonFailure::GetCurrrentFailureCount(const IPAddress &ipaddress)
   {
      IPAddressSQLHelper helper;

      String sql;
      sql.Format(PLATFORM_STRING("select count(*) as c from hm_logon_failures where ipaddress1 %s and ipaddress2 %s"), 
         String(helper.GetAddress1Equals(ipaddress)).c_str(),
         String(helper.GetAddress2Equals(ipaddress)).c_str());

      SQLCommand command(sql);

      std::shared_ptr<DALRecordset> pRS = Application::Instance()->GetDBManager()->OpenRecordset(command);
      if (!pRS)
         return 0;

      long count = pRS->GetLongValue("c");

      return count;
   }
   
   bool 
   PersistentLogonFailure::AddFailure(const IPAddress &ipaddress)
   {
      SQLStatement statement;

      IPAddressSQLHelper helper;
      helper.AppendStatement(statement, ipaddress, "ipaddress1", "ipaddress2");

      statement.AddColumnCommand("failuretime", SQLStatement::GetCurrentTimestamp());
      statement.SetStatementType(SQLStatement::STInsert);
      statement.SetTable("hm_logon_failures");

      return Application::Instance()->GetDBManager()->Execute(statement);
   }

   bool 
   PersistentLogonFailure::ClearFailuresByIP(const IPAddress &ipaddress)
   {
      IPAddressSQLHelper helper;

      String whereClause;
      whereClause.Format(PLATFORM_STRING("ipaddress1 %s and ipaddress2 %s"), 
         String(helper.GetAddress1Equals(ipaddress)).c_str(),
         String(helper.GetAddress2Equals(ipaddress)).c_str());

      SQLStatement statement;
      statement.SetStatementType(SQLStatement::STDelete);
      statement.SetWhereClause(whereClause);
      statement.SetTable("hm_logon_failures");

      return Application::Instance()->GetDBManager()->Execute(statement);
   }

   bool 
   PersistentLogonFailure::ClearOldFailures(int olderThanMinutes)
   {
      String whereClause;
      whereClause.Format(PLATFORM_STRING("failuretime < %s"), SQLStatement::GetCurrentTimestampPlusMinutes(-olderThanMinutes).c_str());

      SQLStatement statement;
      statement.SetStatementType(SQLStatement::STDelete);
      statement.SetWhereClause(whereClause);
      statement.SetTable("hm_logon_failures");

      return Application::Instance()->GetDBManager()->Execute(statement);

   }
}