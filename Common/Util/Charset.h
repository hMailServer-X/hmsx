#pragma once

namespace HM
{
   class MimeField;

   class Charset  
   {
   public:
	   Charset();
	   virtual ~Charset();


      static bool IsProperlyEncoded(const String &sInput);

      static String Encode(const String &sUnencoded);
   
      static String GetIMAPEncoded(const String &sUnencoded);

      static AnsiString ToMultiByte(const String &sWideChar, const AnsiString &sCharacterSet);
      static String ToWideChar(const AnsiString &sMultiByte, const AnsiString &sCharacterSet);

   private:

      static String B64Encode(const String &sInput);
   };

   class CharsetTester
   {
   public:

      CharsetTester () {};
      ~CharsetTester () {};      

      void Test();
   };

}
