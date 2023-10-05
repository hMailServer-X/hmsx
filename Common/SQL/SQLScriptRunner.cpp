#include "pch.h"

#include "SQLScriptRunner.h"
#include "SQLScriptParser.h"
#include "Macros/MacroParser.h"
#include "Macros/IMacroExpander.h"

namespace HM
{
   SQLScriptRunner::SQLScriptRunner() 
   {
      
   }

   bool
   SQLScriptRunner::ExecuteScript(std::shared_ptr<DALConnection> connectionObject, const String &sFile, String &sErrorMessage)
   {
      SQLScriptParser oParser(connectionObject->GetSettings(), sFile);
      if (!oParser.Parse(sErrorMessage))
      {
         sErrorMessage = "Parsing of SQL script failed: " + sFile + "\r\nError:" + sErrorMessage;
         return false;
      }

      if (oParser.GetNoOfCommands() == 0)
      {
         sErrorMessage = "Found no SQL commands in file : " + sFile;
         return false;
      }

      // 30 minute timeout per statement. Should hopefully never be needed.
      connectionObject->SetTimeout(60 * 30);

      for (int i = 0; i < oParser.GetNoOfCommands(); i++)
      {
         String sCommand = oParser.GetCommand(i);

         if (sCommand.StartsWith(PLATFORM_STRING("@@@")))
         {
            // Remove leading @@@.
            sCommand = sCommand.Mid(3);

            // Remove trailing @@@
            sCommand = sCommand.Mid(0, sCommand.Find(PLATFORM_STRING("@@@")));

            MacroParser parser(sCommand);
            Macro macro = parser.Parse();

            if (macro.GetType() == Macro::Unknown)
            {
               sErrorMessage = "Parsing of SQL script failed. Unknown macro. " + sFile + "\r\nMacro:" + sCommand;
               return false;
            }

            std::shared_ptr<IMacroExpander> macroExpander = connectionObject->CreateMacroExpander();
            if (!macroExpander->ProcessMacro(connectionObject, macro, sErrorMessage))
               return false;
         }
         else
         {
            if (connectionObject->TryExecute(SQLCommand(sCommand), sErrorMessage, 0, 0) != DALConnection::DALSuccess)
            {
               return false;
            }
         }
      }

      connectionObject->SetTimeout(30);

      return true;
   }


}
