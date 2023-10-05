#include "pch.h"

#include "SQLScriptParser.h"
#include "DatabaseSettings.h"

namespace HM
{
   SQLScriptParser::SQLScriptParser(std::shared_ptr<DatabaseSettings> pSettings, const String &sFile) :
      settings_(pSettings),
      file_(sFile)
   {

   }

   SQLScriptParser::~SQLScriptParser()
   {

   }

   bool 
   SQLScriptParser::Parse(String &sErrorMessage)
   {
      String sContents = FileUtilities::ReadCompleteTextFile(file_);
      

      if (sContents.GetLength() == 0)
      {
         sErrorMessage = "Unable to read from file " + file_;
         return false;
      }
   
      String sCommandSeparator;
      switch (settings_->GetType())
      {
      case HM::DatabaseSettings::TypeMSSQLCompactEdition:
      case HM::DatabaseSettings::TypeMSSQLServer:
         sCommandSeparator = "\r\n\r\n";
         break;
      case HM::DatabaseSettings::TypeMYSQLServer:
         sCommandSeparator = "\r\n\r\n";
         break;
      case HM::DatabaseSettings::TypePGServer:
         sCommandSeparator = ";\r\n\r\n";
         break;
      }

      std::vector<String> vecCommands = StringParser::SplitString(sContents, sCommandSeparator);
      auto iter = vecCommands.begin();
      auto iterEnd = vecCommands.end();

      for (; iter != iterEnd; iter++)
      {
         String sCommand = (*iter);

         if (PreprocessLine_(sCommand))
         {
            commands_.push_back(sCommand);
         }
      }
      

      return true;
   }

   bool 
   SQLScriptParser::PreprocessLine_(String &sLine)
   {
      // Do some basic preprocessing...
      while (sLine.Left(2).Compare(PLATFORM_STRING("\r\n")) == 0)
         sLine = sLine.Mid(2);
      
      while (sLine.Left(1).Compare(PLATFORM_STRING(" ")) == 0)
         sLine = sLine.Mid(1);
     
      while (sLine.Left(1).Compare(PLATFORM_STRING("\t")) == 0)
         sLine = sLine.Mid(1);


      String sTempLine = sLine;

      if (settings_->GetType() == HM::DatabaseSettings::TypeMSSQLCompactEdition)
      {
         if (sTempLine.ToLower().Left(3).Compare(PLATFORM_STRING("if ")) == 0)
         {
            return false;
         }
         else if (sLine.FindNoCase(PLATFORM_STRING(" CLUSTERED ")) >= 0)
         {
            sLine.ReplaceNoCase(PLATFORM_STRING(" CLUSTERED "), PLATFORM_STRING(" "));
         }
         else if (sLine.FindNoCase(PLATFORM_STRING("CREATE PROC")) >= 0)
         {
            // Procedures not supported by SQL CE
            return false;
         }

         sLine.Replace(PLATFORM_STRING("\t"), PLATFORM_STRING(" "));
         sLine.Replace(PLATFORM_STRING(" varchar"), PLATFORM_STRING(" nvarchar"));

      }

      if (sLine.IsEmpty())
         return false;


      return true;
   }

}