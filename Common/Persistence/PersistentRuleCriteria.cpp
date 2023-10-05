#include "pch.h"
#include "./persistentrulecriteria.h"
#include "../BO/RuleCriteria.h"

namespace HM
{
   PersistentRuleCriteria::PersistentRuleCriteria(void)
   {
   }

   PersistentRuleCriteria::~PersistentRuleCriteria(void)
   {
   }

   bool
   PersistentRuleCriteria::ReadObject(std::shared_ptr<RuleCriteria> pRuleCriteria, const SQLCommand &command)
   {

      std::shared_ptr<DALRecordset> pRS = Application::Instance()->GetDBManager()->OpenRecordset(command);
      if (!pRS)
         return false;

      bool bRetVal = false;
      if (!pRS->IsEOF())
      {
         bRetVal = ReadObject(pRuleCriteria, pRS);
      }

      return bRetVal;
   }

   bool
   PersistentRuleCriteria::ReadObject(std::shared_ptr<RuleCriteria> pRuleCriteria, std::shared_ptr<DALRecordset> pRS)
   {
      if (pRS->IsEOF())
         return false;

      pRuleCriteria->SetID(pRS->GetLongValue("criteriaid"));
      pRuleCriteria->SetRuleID(pRS->GetLongValue("criteriaruleid"));
      pRuleCriteria->SetMatchValue(pRS->GetStringValue("criteriamatchvalue"));
      pRuleCriteria->SetPredefinedField((RuleCriteria::PredefinedField) pRS->GetLongValue("criteriapredefinedfield"));
      pRuleCriteria->SetMatchType((RuleCriteria::MatchType) pRS->GetLongValue("criteriamatchtype"));
      pRuleCriteria->SetHeaderField(pRS->GetStringValue("criteriaheadername"));
      pRuleCriteria->SetUsePredefined(pRS->GetLongValue("criteriausepredefined") ? true : false);

      return true;
   }

   bool
   PersistentRuleCriteria::SaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria, String &errorMessage, PersistenceMode mode)
   {
      // errorMessage - not supported yet.
      return SaveObject(pRuleCriteria);
   }

   bool
   PersistentRuleCriteria::SaveObject(std::shared_ptr<RuleCriteria> pRuleCriteria)
   {
      SQLStatement oStatement;
      oStatement.SetTable("hm_rule_criterias");

      bool bNewObject = pRuleCriteria->GetID() == 0;

      if (bNewObject)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("criteriaid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);
         
         String sWhere;
         sWhere.Format(PLATFORM_STRING("criteriaid = %I64d"), pRuleCriteria->GetID());
         oStatement.SetWhereClause(sWhere);

      }

      oStatement.AddColumnInt64("criteriaruleid", pRuleCriteria->GetRuleID());
      oStatement.AddColumn("criteriausepredefined", pRuleCriteria->GetUsePredefined());
      oStatement.AddColumn("criteriapredefinedfield", pRuleCriteria->GetPredefinedField());
      oStatement.AddColumn("criteriaheadername", pRuleCriteria->GetHeaderField());
      oStatement.AddColumn("criteriamatchtype", pRuleCriteria->GetMatchType());
      oStatement.AddColumn("criteriamatchvalue", pRuleCriteria->GetMatchValue());

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pRuleCriteria->SetID((int) iDBID);

      return bRetVal;

   }

   bool
   PersistentRuleCriteria::DeleteObject(std::shared_ptr<RuleCriteria> pRuleCriteria)
   {
      SQLCommand command("delete from hm_rule_criterias where criteriaid = @CRITERIAID");
      command.AddParameter("@CRITERIAID", pRuleCriteria->GetID());

      bool bRet = Application::Instance()->GetDBManager()->Execute(command);

      return bRet; 
   }

   bool
   PersistentRuleCriteria::DeleteObjects(long long iRuleID)
   {
      SQLCommand command("delete from hm_rule_criterias where criteriaruleid = @RULEID");
      command.AddParameter("@RULEID", iRuleID);

      bool bRet = Application::Instance()->GetDBManager()->Execute(command);

      return bRet; 
   }
}