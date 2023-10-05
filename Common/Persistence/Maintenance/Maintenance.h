#pragma once

namespace HM
{
   class Maintenance
   {
   public:
	   Maintenance();
	   virtual ~Maintenance();

      enum MaintenanceOperation
      {
         RecalculateFolderUID = 1001 
      };

      bool Perform(MaintenanceOperation operation);

   private:

      bool RecalculateFolderUID_();
   };


}