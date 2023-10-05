#pragma once

namespace HM
{
   class DALRecordsetFactory  
   {
   public:
	   DALRecordsetFactory();
	   virtual ~DALRecordsetFactory();

      //static std::shared_ptr<DALRecordset> CreateRecordset();
   };
}
