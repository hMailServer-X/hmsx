#include "pch.h"
#include "POP3Configuration.h"

namespace HM
{
   POP3Configuration::POP3Configuration()
   {

   }

   POP3Configuration::~POP3Configuration()
   {

   }

   std::shared_ptr<PropertySet> 
   POP3Configuration::GetSettings_() const
   {
      return Configuration::Instance()->GetSettings();
   }

   void
   POP3Configuration::SetMaxPOP3Connections(int newVal)
   {
      GetSettings_()->SetLong(PROPERTY_MAXPOP3CONNECTIONS, newVal);
   }

   long
   POP3Configuration::GetMaxPOP3Connections() const
   {
      return GetSettings_()->GetLong(PROPERTY_MAXPOP3CONNECTIONS);
   }


   String 
   POP3Configuration::GetWelcomeMessage() const
   {
      return GetSettings_()->GetString(PROPERTY_WELCOMEPOP3);
   }

   void 
   POP3Configuration::SetWelcomeMessage(const String &sMessage)
   {
      GetSettings_()->SetString(PROPERTY_WELCOMEPOP3, sMessage);
   }
}