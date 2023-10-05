#include "pch.h"
#include "PrerequisiteList.h"

#include "PreReqNoDuplicateFolders.h"
#include "IPrerequisite.h"

namespace HM
{
   PrerequisiteList::PrerequisiteList(void)
   {
      Initialize_();
   }

   PrerequisiteList::~PrerequisiteList(void)
   {
   }

   void 
   PrerequisiteList::Initialize_()
   {
      std::shared_ptr<PreReqNoDuplicateFolders> duplicateFolderCheck = std::shared_ptr<PreReqNoDuplicateFolders>(new PreReqNoDuplicateFolders);
      prerequisites_.push_back(std::make_pair(duplicateFolderCheck->GetDatabaseVersion(), duplicateFolderCheck));
   }

   bool
   PrerequisiteList::Ensure(std::shared_ptr<DALConnection> connection, int scriptDatabaseVersion, String &sErrorMessage)
   {
      auto iter = prerequisites_.begin();
      auto iterEnd = prerequisites_.end();

      for (; iter != iterEnd; iter++)
      {
         int databaseVersion = (*iter).first;

         if (databaseVersion == scriptDatabaseVersion)
         {
            std::shared_ptr<IPrerequisite > prereq = (*iter).second;

            if (!prereq->Ensure(connection, sErrorMessage))
               return false;
         }
      }

      return true;
   }

   
}