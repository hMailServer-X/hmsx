#pragma once

using boost::asio::ip::tcp;

#include "VirusScanningResult.h"

namespace HM
{
   class ClamAVVirusScanner
   {
   public:
      ClamAVVirusScanner(void);
      ~ClamAVVirusScanner(void);

      static VirusScanningResult Scan(const String &sFilename);
      static VirusScanningResult Scan(const String &hostName, int primaryPort, const String &sFilename);
   };

}