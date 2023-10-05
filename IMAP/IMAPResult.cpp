#include "pch.h"
#include "IMAPResult.h"

namespace HM
{

   IMAPResult::IMAPResult(Result result, const String &message) :
      result_(result),
      message_(message)
   {
      
   }

   IMAPResult::IMAPResult() :
      result_(ResultOK),
      message_("")
   {

   }

   IMAPResult::IMAPResult(const IMAPResult &otherCopy)
   {
      result_ = otherCopy.GetResult();
      message_ = otherCopy.GetMessage();
   }

   IMAPResult& 
   IMAPResult::operator= (const IMAPResult&otherCopy)
   {
      result_ = otherCopy.GetResult();
      message_ = otherCopy.GetMessage();

      return *this;
   }


   IMAPResult::~IMAPResult()
   {
      
   }
}
