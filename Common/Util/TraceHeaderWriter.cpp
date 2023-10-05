#include "pch.h"
#include "TraceHeaderWriter.h"
#include "../BO/Message.h"
#include "../Persistence/PersistentMessage.h"

namespace HM
{
   TraceHeaderWriter::TraceHeaderWriter()
   {

   }

   TraceHeaderWriter::~TraceHeaderWriter(void)
   {

   }

   bool 
   TraceHeaderWriter::Write(const String &messageFileName, std::shared_ptr<Message> message, const std::vector<std::pair<AnsiString, AnsiString> > &headerFields)
   {
      if (headerFields.size() == 0)
         return true;

      // Add a return-path header. 
      String tempFile = messageFileName + ".tmp";

      File temporaryFile;
      if (!temporaryFile.Open(tempFile, File::OTCreate))
         return false;

      typedef std::pair<AnsiString, AnsiString> headerField;

      AnsiString prependString;
      for(headerField field : headerFields)
      {
         prependString += field.first + ": " + field.second + "\r\n";
      }
      
      if (!temporaryFile.Write(prependString))
         return false;

      File messageFile;
      if (!messageFile.Open(messageFileName, File::OTReadOnly))
         return false;

      if (!temporaryFile.Write(messageFile))
         return false;

      temporaryFile.Close();
      messageFile.Close();

      return FileUtilities::Move(tempFile, messageFileName, true);

      return true;
   }

}