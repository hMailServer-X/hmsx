#pragma once

namespace HM
{
   class PasswordGenerator
   {
   public:
	   PasswordGenerator();
	   virtual ~PasswordGenerator();

      static String Generate();
      static bool IsStrongPassword(const String &sUsername, const String &sPassword);

   private:
      
      static int Seed;

   };

}

