#include "pch.h"

#include "ExceptionLogger.h"
#include "FileInfo.h"
#include "Time.h"
#include "GUIDCreator.h"
#include "FileUtilities.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

namespace HM
{
   boost::mutex ExceptionLogger::logging_mutex_;

   void
   ExceptionLogger::Log(int exception_code, EXCEPTION_POINTERS* pExp)
   {
      boost::mutex::scoped_lock lock(logging_mutex_);

      // limit the number of logs crated to prevent disk from becoming full.
      if (!TryToMakeRoom())
      {
         return;
      }

      String log_directory = IniFileSettings::Instance()->GetLogDirectory();
      String current_date_time = Time::GetCurrentDateTime();
      current_date_time.Replace(PLATFORM_STRING(":"), PLATFORM_STRING(""));

      String log_identifier = GUIDCreator::GetGUID();


   }

   bool 
   ExceptionLogger::TryToMakeRoom()
   {
      // error logs are saved for 4 hours, rolling.

      String log_directory = IniFileSettings::Instance()->GetLogDirectory();

      


      FileInfo oldest;




      String full_path = FileUtilities::Combine(log_directory, oldest.GetName());

      FileUtilities::DeleteFile(full_path);
      return true;
   }
      
   

} 