#pragma once

#include "IMacroExpander.h"

namespace HM
{
   class Macro;

   class PGSQLMacroExpander : public IMacroExpander
   {
   public:

      bool ProcessMacro(std::shared_ptr<DALConnection> connection, const Macro &macro, String &sErrorMessage);

   private:
   };
}
