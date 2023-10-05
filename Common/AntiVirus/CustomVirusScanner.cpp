#include "pch.h"

#include "CustomVirusScanner.h"
#include "../../SMTP/SMTPConfiguration.h"


namespace HM
{
   CustomVirusScanner::CustomVirusScanner(void)
   {
   }

   CustomVirusScanner::~CustomVirusScanner(void)
   {

   }
   
   VirusScanningResult 
   CustomVirusScanner::Scan(const String &sFilename)
   {
      AntiVirusConfiguration &pConfig = Configuration::Instance()->GetAntiVirusConfiguration();
      String executablePath = pConfig.GetCustomScannerExecutable();
      int virusReturnCode = pConfig.GetCustomScannerReturnValue();
      return Scan(executablePath, virusReturnCode, sFilename);
   }

   VirusScanningResult 
   CustomVirusScanner::Scan(const String &executablePath, int virusReturnCode, const String &sFilename)
   {
      LOG_DEBUG("Running custom virus scanner...");


      String sPath = FileUtilities::GetFilePath(sFilename);

      String sCommandLine;

      if (executablePath.Find(PLATFORM_STRING("%FILE%")) >= 0)
      {
         sCommandLine = executablePath;
         sCommandLine.Replace(PLATFORM_STRING("%FILE%"), sFilename);
      }
      else
         sCommandLine.Format(PLATFORM_STRING("%s %s"), executablePath.c_str(), sFilename.c_str());

      unsigned int exitCode = 0;
      
      

      String sDebugMessage = Formatter::Format("Scanner: {0}. Return code: {1}", sCommandLine, exitCode);
      LOG_DEBUG(sDebugMessage);

      if (exitCode == virusReturnCode)
         return VirusScanningResult(VirusScanningResult::VirusFound, "Unknown");
      else
         return VirusScanningResult(VirusScanningResult::NoVirusFound, Formatter::Format("Return code: {0}", exitCode));

   }
}