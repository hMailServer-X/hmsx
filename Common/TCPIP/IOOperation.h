#pragma once

namespace HM
{
   class ByteBuffer;

   class IOOperation
   {
   public:

      enum OperationType
      {
         BCTWrite,
         BCTRead,
         BCTShutdownSend,
         BCTDisconnect,
         BCTHandshake
      };

      IOOperation(OperationType type, std::shared_ptr<ByteBuffer> buffer);
      IOOperation(OperationType type, const AnsiString &string);
      ~IOOperation(void);

      OperationType GetType() {return type_; }
      std::shared_ptr<ByteBuffer> GetBuffer() {return buffer_; }
      AnsiString GetString() {return string_; }

   private:

      OperationType type_;
      AnsiString string_;
      std::shared_ptr<ByteBuffer> buffer_;

   };
}