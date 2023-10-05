#include "pch.h"
#include "PasswordGenerator.h"
#include "../Util/GUIDCreator.h"

namespace HM
{
   int PasswordGenerator::Seed = 0;

   PasswordGenerator::PasswordGenerator()
   {
      
   }

   PasswordGenerator::~PasswordGenerator()
   {

   }

   String
   PasswordGenerator::Generate()
   {
      String sGUID = GUIDCreator::GetGUID();

      String sOutString;

      for (int i = 0; i < sGUID.GetLength(); i++)
      {
         wchar_t c = sGUID[i];

         switch (c)
         {
         case '{':
         case '}':
         case '-':
            break;
         default:
            sOutString += c;
         }

      }

      String sRetVal = sOutString.Mid(0,12);
      return sRetVal;
   }

   bool 
   PasswordGenerator::IsStrongPassword(const String &sUsername, const String &sPassword)
   {

      // The password should not be a part of a user name.
      if (sUsername.FindNoCase(sPassword) >= 0)
         return false;

      // The password should be more than 4 characters long.
      if (sPassword.GetLength() <= 4)
         return false;
     
      // If the password is 6 characters or less, it should contain a number or special char
      if (sPassword.GetLength() <= 6)
      {
         if (sPassword.FindOneOf(PLATFORM_STRING("01234567890!\"#�%&/()=?^*_:;><,.-'��+")) < 0)
            return false;
      }

      if (sPassword.CompareNoCase(PLATFORM_STRING("secret")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("password")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("info")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("webmaster")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("admin")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("12345")) == 0) return false;
      if (sPassword.CompareNoCase(PLATFORM_STRING("qwerty")) == 0) return false;

      return true;
   }

}
