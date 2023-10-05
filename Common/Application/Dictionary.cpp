#include "pch.h"
#include "Dictionary.h"


namespace HM
{
   Dictionary::Dictionary()
   {

   }


   Dictionary::~Dictionary()
   {

   }

   String 
   Dictionary::GetWindowsErrorDescription(int iErrorCode)
   {
      switch (iErrorCode)
      {
      case ERROR_INVALID_FUNCTION:
         return "Invalid function";
      case ERROR_FILE_NOT_FOUND:
         return "File not found";
      case ERROR_PATH_NOT_FOUND:
         return "Path not found";
      case ERROR_TOO_MANY_OPEN_FILES:
         return "Too many open files";
      case ERROR_ACCESS_DENIED:
         return "Access denied";
      case ERROR_INVALID_HANDLE:
         return "Invalid handle";
      case ERROR_ARENA_TRASHED:
         return "The storage control blocks were destroyed.";
      case ERROR_NOT_ENOUGH_MEMORY:
         return "Not enough storage is available to process this command.";
      case ERROR_INVALID_ACCESS:
         return "The access code is invalid.";
      case ERROR_OUTOFMEMORY:
         return "Not enough storage is available to complete this operation.";
      case ERROR_SHARING_VIOLATION:
         return "The process cannot access the file because it is being used by another process.";
      default:
         return "Unknown";
      }
   }

}