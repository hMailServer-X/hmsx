#include "pch.h"
#include "MacroParser.h"

namespace HM
{
   MacroParser::MacroParser(const String &macroString) :
      macro_string_(macroString)
   {
      
   }


   MacroParser::~MacroParser()
   {
   
   }

   Macro 
   MacroParser::Parse()
   {
      if (macro_string_.StartsWith(PLATFORM_STRING("HM_DROP_COLUMN_OBJECTS")))
      {
         int pos = macro_string_.Find(PLATFORM_STRING(" "));

         String columnSpecifier = macro_string_.Mid(pos);

         int separator = columnSpecifier.Find(PLATFORM_STRING("."));

         String tableName = columnSpecifier.Mid(0, separator);
         String columnName = columnSpecifier.Mid(separator+1);

         tableName.Trim();
         columnName.Trim();

         Macro macro;
         macro.SetType(Macro::DropColumnKeys);
         macro.SetTableName(tableName);
         macro.SetColumnName(columnName);

         return macro;
      }
      else if (macro_string_ == PLATFORM_STRING("UPDATE_MESSAGES_SET_FOLDER_INBOX"))
      {
         Macro macro;
         macro.SetType(Macro::SQLCEUPDATE_MESSAGES_SET_FOLDER_INBOX);
         return macro;
      }
      else if (macro_string_ == PLATFORM_STRING("UPDATE_FOLDERS_SET_CURRENT_UID"))
      {
         Macro macro;
         macro.SetType(Macro::SQLCEUPDATE_FOLDERS_SET_CURRENT_UID);
         return macro;
      }
      else if (macro_string_ == PLATFORM_STRING("UPDATE_FOLDERS_SET_NEW_PARENTFOLDERID_WHERE_ZERO"))
      {
         Macro macro;
         macro.SetType(Macro::SQLCEUPDATE_FOLDERS_SET_NEW_PARENTFOLDERID_WHERE_ZERO);
         
         return macro;
      }
      else if (macro_string_ == PLATFORM_STRING("SQLCE_UPDATE_IMAP_HIERARCHY_DELIMITER"))
      {
         Macro macro;
         macro.SetType(Macro::SQLCE_UPDATE_IMAP_HIERARCHY_DELIMITER);

         return macro;
      }
      
      Macro unknownMacro;
      return unknownMacro;
   }
}
