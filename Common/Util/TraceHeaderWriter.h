#pragma once

namespace HM
{
   class Message;

   class TraceHeaderWriter
   {
   public:
      TraceHeaderWriter();
      ~TraceHeaderWriter();

      bool Write(const String &messageFileName, std::shared_ptr<Message> message, const std::vector<std::pair<AnsiString, AnsiString> > &headerFields);
   };
}
