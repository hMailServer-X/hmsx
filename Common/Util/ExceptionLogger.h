#pragma once

namespace HM
{
   class ExceptionLogger
   {
   private:
      ExceptionLogger();

   public:
      static void Log(int exception_code, EXCEPTION_POINTERS* pExp);

   private:


      static bool TryToMakeRoom();

      static boost::mutex logging_mutex_;
   };
}