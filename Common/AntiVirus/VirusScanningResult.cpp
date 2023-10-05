#include "pch.h"
#include "VirusScanningResult.h"


namespace HM
{
   

   VirusScanningResult::VirusScanningResult(ScanningResult result, const String &details) :
      result_(result),
      details_(details)
   {
      
   }

   VirusScanningResult::VirusScanningResult(const String &errorMessageSource, const String &errorMessage) :
      result_(ErrorOccurred),
      details_(errorMessage),
      message_source_(errorMessageSource)
   {

   }
}
