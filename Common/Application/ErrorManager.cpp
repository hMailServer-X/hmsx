#include "pch.h"
#include "ErrorManager.h"

namespace HM
{
   ErrorManager::ErrorManager()
   {

   }

   ErrorManager::~ErrorManager()
   {

   }

   String
   GetSeverity(ErrorManager::eSeverity iSev)
   {
      switch (iSev)
      {
      case ErrorManager::Critical:
         return "Critical";
      case ErrorManager::High:
         return "High";
      case ErrorManager::Medium:
         return "Medium";
      case ErrorManager::Low:
         return "Low";
      default:
         return "Unknown";
      }
   }

   int 
   ErrorManager::GetNativeErrorCode(IErrorInfo *pIErrorInfo)
   {
      int iRetValue = 0;
      HRESULT hr                          = S_OK;
      IErrorInfo       *pIErrorInfoRecord = NULL;

      
      return iRetValue;
   }

   void 
   ErrorManager::ReportError(eSeverity iSeverity, int iErrorID, const String &sSource, const String &sDescription, const boost::system::system_error &error)
   {
      String formatted_message 
         = Formatter::Format(PLATFORM_STRING("{0}, Error code: {1}, Message: {2}"), sDescription, error.code().value(), error.what());

      ReportError(iSeverity, iErrorID, sSource, formatted_message);
   }

   void
   ErrorManager::ReportError(eSeverity iSeverity, int iErrorID, const String &sSource, const String &sDescription, const boost::system::error_code &error)
   {
      String formatted_message
         = Formatter::Format(PLATFORM_STRING("{0}, Error code: {1}, Message: {2}"), sDescription, error.value(), error.message().c_str());

      ReportError(iSeverity, iErrorID, sSource, formatted_message);
   }

   void 
   ErrorManager::ReportError(eSeverity iSeverity, int iErrorID, const String &sSource, const String &sDescription, const std::exception &error)
   {
      String formatted_message
         = Formatter::Format(PLATFORM_STRING("{0}, Message: {1}"), sDescription, error.what());

      ReportError(iSeverity, iErrorID, sSource, formatted_message);
   }


   String 
   ErrorManager::GetWindowsErrorText(int windows_error_code)
   {
      LPTSTR message_buf = 0;

      FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | 
         FORMAT_MESSAGE_FROM_SYSTEM |
         FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         windows_error_code,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
         (LPTSTR) &message_buf,
         0, NULL );

      String windows_error_message = message_buf;
      windows_error_message.TrimRight(PLATFORM_STRING("\r\n "));

      /*
          http://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx
          The caller should use the LocalFree function to free the buffer when it is no longer needed.
      */

      LocalFree(message_buf);

      return windows_error_message;
   }

   void 
   ErrorManager::ReportError(eSeverity iSeverity, int iErrorID, const String &sSource, const String &sDescription)
   {
      String sSeverityStr = GetSeverity(iSeverity);

      String sTempDesc = sDescription;
      sTempDesc.Replace(PLATFORM_STRING("\r\n"), PLATFORM_STRING("[nl]"));

      String sErrorToLog;
      sErrorToLog.Format(PLATFORM_STRING("Severity: %d (%s), Code: HM%d, Source: %s, Description: %s"), 
                            iSeverity, sSeverityStr.c_str(), iErrorID, sSource.c_str(), sTempDesc);

      Logger::Instance()->LogError(sErrorToLog); 

      // Send an event if we've been able to load our settings. During database
      // creation, we don't have any PropertySet in the cache but we should still
      // be able to report errors. During server start up, we have a property set (?)
      // but it's not initialized. So we need to be a bit careful here.
      if (Configuration::Instance()&& 
          Configuration::Instance()->GetPropertySet() && 
          Configuration::Instance()->GetUseScriptServer())
      {
         String sEventCaller;
         
         String sScriptLanguage = Configuration::Instance()->GetScriptLanguage();

         if (sScriptLanguage == PLATFORM_STRING("VBScript"))
         {
            String tempSource = sSource;
            String tempDescription = sDescription;
            
            tempSource.Replace(PLATFORM_STRING("\""), PLATFORM_STRING("\"\""));
            tempDescription.Replace(PLATFORM_STRING("\""), PLATFORM_STRING("\"\""));

            sEventCaller.Format(PLATFORM_STRING("OnError(%d, %d, \"%s\", \"%s\")"), 
               iSeverity, iErrorID, tempSource.c_str(), tempDescription.c_str());
         }
         else if (sScriptLanguage == PLATFORM_STRING("JScript"))
         {
            String tempSource = sSource;
            String tempDescription = sDescription;

            tempSource.Replace(PLATFORM_STRING("'"), PLATFORM_STRING("\\'"));
            tempDescription.Replace(PLATFORM_STRING("'"), PLATFORM_STRING("\\'"));

            sEventCaller.Format(PLATFORM_STRING("OnError(%d, %d, '%s', '%s')"), 
               iSeverity, iErrorID, tempSource.c_str(), tempDescription.c_str());
         }

         

      }
   }


}
