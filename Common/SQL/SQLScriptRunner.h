#pragma once

namespace HM
{
   class SQLScriptRunner
   {
   public:
      SQLScriptRunner();

      bool ExecuteScript(std::shared_ptr<DALConnection> connectionObject, const String &sFile, String &sErrorMessage);

   private:


   };
}
