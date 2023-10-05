#include "pch.h"
#include "IOOperation.h"
#include "../Util/ByteBuffer.h"

namespace HM
{
   IOOperation::IOOperation(OperationType type, std::shared_ptr<ByteBuffer> buffer) :
      type_(type),
      buffer_(buffer)
   {
      
   }

   IOOperation::IOOperation(OperationType type, const AnsiString &string) :
      type_(type),
      string_(string)
   {
      
   }

   IOOperation::~IOOperation(void)
   {

   }

   
}