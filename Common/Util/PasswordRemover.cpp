#include "pch.h"
#include "PasswordRemover.h"

namespace HM
{

   PasswordRemover::PasswordRemover()
   {
      
   }

   PasswordRemover::~PasswordRemover()
   {

   }

	void
	PasswordRemover::Remove(PRType prt, String &sClientCommand)
	{
      if (prt == PRIMAP)
      {
		   // Starts the second word.
         int iCommandStart = sClientCommand.Find(PLATFORM_STRING(" "));
         if (iCommandStart == -1)
            return;
      
         iCommandStart++;

         if (sClientCommand.Mid(iCommandStart, 5).CompareNoCase(PLATFORM_STRING("LOGIN")) != 0)
            return;
         
         // Find end of login name.
         int iUsernameEnd = sClientCommand.Find(PLATFORM_STRING(" "), iCommandStart + 6);
         if (iUsernameEnd <= 0)
            return;

         sClientCommand = sClientCommand.Mid(0, iUsernameEnd);
         sClientCommand += " ***";
      }
      else if (PRIMAP)
      {
         // Remove from POP3 ...
         if (sClientCommand.Mid(0, 4).CompareNoCase(PLATFORM_STRING("PASS")) != 0)
            return;

         // Remove the password.
         sClientCommand = sClientCommand.Mid(0, 4) + " ***";
      }

	}
}
