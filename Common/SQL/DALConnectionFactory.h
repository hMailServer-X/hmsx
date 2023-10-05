#pragma once

namespace HM
{
   class DatabaseSettings;

   class DALConnectionFactory  
   {
   public:
	   DALConnectionFactory();
	   virtual ~DALConnectionFactory();


      static std::shared_ptr<DALConnection> CreateConnection(std::shared_ptr<DatabaseSettings> pSettings);

   };
}
