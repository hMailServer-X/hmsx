
#include "pch.h"
#include "DALConnectionFactory.h"
#include "PGConnection.h"
#include "DatabaseSettings.h"

namespace HM
{

   DALConnectionFactory::DALConnectionFactory()
   {

   }

   DALConnectionFactory::~DALConnectionFactory()
   {

   }

   std::shared_ptr<DALConnection>
   DALConnectionFactory::CreateConnection(std::shared_ptr<DatabaseSettings> pSettings)
   {
      std::shared_ptr<DALConnection> pConn;
      
      HM::DatabaseSettings::SQLDBType t = pSettings->GetType();

     switch (t)
      {
      case HM::DatabaseSettings::TypeMSSQLServer:

         break;
      case HM::DatabaseSettings::TypeMYSQLServer:
         break;

      case HM::DatabaseSettings::TypePGServer:
         pConn = std::shared_ptr<PGConnection>(new PGConnection(pSettings));
         break;

      case HM::DatabaseSettings::TypeMSSQLCompactEdition:
         break;
      }
   
      return pConn;
   }
}