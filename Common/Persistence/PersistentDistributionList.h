#pragma once

namespace HM
{
   class DistributionList; 
   enum PersistenceMode;

   class PersistentDistributionList
   {
   public:
      PersistentDistributionList(void);
      ~PersistentDistributionList(void);

      static bool DeleteObject(std::shared_ptr<DistributionList> pDistList);
      
      static bool SaveObject(std::shared_ptr<DistributionList> pDistList);
      static bool SaveObject(std::shared_ptr<DistributionList> pDistList, String &sErrorMessage, PersistenceMode mode);

      static bool ReadObject(std::shared_ptr<DistributionList> pDistList, const String &sAddress);
      static bool ReadObject(std::shared_ptr<DistributionList> pDistList, long long ObjectID);
      static bool ReadObject(std::shared_ptr<DistributionList> pDistList, const SQLCommand &command);
      static bool ReadObject(std::shared_ptr<DistributionList> pDistList, std::shared_ptr<DALRecordset> pRS);

      static bool DeleteMembers(std::shared_ptr<DistributionList> pDistList);


   private:

      
   };
}
