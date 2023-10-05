namespace HM
{
   class ModifiedUTF7
   {
   public:
      static AnsiString Encode(const String &sUnicodeString);
      static String Decode(const AnsiString &s);

   private:
      static bool IsSpecialCharacter_(const wchar_t);
   };

   class ModifiedUTF7Tester
   {
   public:
      void Test();
   };

}