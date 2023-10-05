#include "pch.h"
#include "PersistentRouteAddress.h"
#include "../BO/RouteAddress.h"


namespace HM
{
   PersistentRouteAddress::PersistentRouteAddress()
   {

   }

   PersistentRouteAddress::~PersistentRouteAddress()
   {

   }

   bool
   PersistentRouteAddress::SaveObject(std::shared_ptr<RouteAddress> pRA, String &errorMessage, PersistenceMode mode)
   {
      // errorMessage not supported yet.

      return SaveObject(pRA);
   }

   bool
   PersistentRouteAddress::SaveObject(std::shared_ptr<RouteAddress> pRA)
   {

      SQLStatement oStatement;
      oStatement.AddColumnInt64("routeaddressrouteid", pRA->GetRouteID());
      oStatement.AddColumn("routeaddressaddress", pRA->GetAddress());

      oStatement.SetTable("hm_routeaddresses");

      if (pRA->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("routeaddressid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);

         String sWhere;
         sWhere.Format(PLATFORM_STRING("routeaddressid = %I64d"), pRA->GetID());
         oStatement.SetWhereClause(sWhere);
      }

      bool bNewObject = pRA->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pRA->SetID((int) iDBID);

      return bRetVal;
   }

   bool
   PersistentRouteAddress::DeleteObject(std::shared_ptr<RouteAddress> pRA)
   {
      SQLCommand command("delete from hm_routeaddresses where routeaddressid = @ROUTEADDRESSID");
      command.AddParameter("@ROUTEADDRESSID", pRA->GetID());

      return Application::Instance()->GetDBManager()->Execute(command);
   }

   bool
   PersistentRouteAddress::DeleteByRoute(long long RouteID)
   {
      SQLCommand command("delete from hm_routeaddresses where routeaddressrouteid = @ROUTEID");
      command.AddParameter("@ROUTEID", RouteID);

      return Application::Instance()->GetDBManager()->Execute(command);
   }

   bool
   PersistentRouteAddress::ReadObject(std::shared_ptr<RouteAddress> pRA, long lID)
   {
      SQLCommand command("select * from hm_routeaddresses where routeaddressid = @ROUTEADDRESSID");
      command.AddParameter("@ROUTEADDRESSID", lID);

      std::shared_ptr<DALRecordset> pRS = Application::Instance()->GetDBManager()->OpenRecordset(command);
      if (!pRS)
         return false;

      bool bRetVal = false;
      if (!pRS->IsEOF())
      {
         bRetVal = ReadObject(pRA, pRS);
      }

      return true;
   }

   bool 
   PersistentRouteAddress::ReadObject(std::shared_ptr<RouteAddress> pRA, std::shared_ptr<DALRecordset> pRS)
   {
      pRA->SetID(pRS->GetLongValue("routeaddressid"));
      pRA->SetRouteID(pRS->GetLongValue("routeaddressrouteid"));
      pRA->SetAddress(pRS->GetStringValue("routeaddressaddress"));

      return true;
   }   
}

