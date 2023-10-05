#pragma once

#include "VirusScanningResult.h"

namespace HM
{
   class CustomVirusScanner
   {
   public:
      CustomVirusScanner(void);
      ~CustomVirusScanner(void);

      static VirusScanningResult Scan(const String &executablePath, int virusReturnCode, const String &sFilename);
      static VirusScanningResult Scan(const String &sFilename);
   };

}