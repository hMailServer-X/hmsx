#include "pch.h"
#include "ModifiedUTF7.h"
#include "../Charset.h"


namespace HM
{
   
   /*
   Converts an UTF-8 string to modified UTF-7.

   Example: 
      Input: TE&AOUA5AD2-ST
      Output: TEåäöST

   Implementation:
      We go through the input string one character at a time.
      If the character is not a special character, we'll add it
      directly to the output string. If the character IS a special 
      character, it needs to be encoded. When we detect a special
      character, we continue going through the string until we find
      a normal char or end of string. We then encode that subset of 
      the string using the Windows API.
   */
   AnsiString
   ModifiedUTF7::Encode(const String &sUnicodeString)
   {
      AnsiString sRetVal;
      int iCurrentPos = 0;

      while (iCurrentPos <  sUnicodeString.GetLength())
      {
         wchar_t sCurrentChar = sUnicodeString[iCurrentPos];

         if (IsSpecialCharacter_(sCurrentChar) == false)
         {
            // This isn't a special character, so we can append it without
            // doing any encoding.
            sRetVal += (char) sCurrentChar;

            if (sCurrentChar == '&')
               sRetVal += "-";

            iCurrentPos++;
            sCurrentChar = sUnicodeString[iCurrentPos];

            continue;
         }

         // Locate the position of the next special character.
         int subsetStartPos = iCurrentPos;

         for (; iCurrentPos < sUnicodeString.GetLength(); iCurrentPos++)
         {
            sCurrentChar = sUnicodeString[iCurrentPos];
            if (!IsSpecialCharacter_(sCurrentChar))
               break;
         } 
         
         int subsetLength = iCurrentPos - subsetStartPos;
         String subSet = sUnicodeString.Mid(subsetStartPos, subsetLength);
         if (!subSet.IsEmpty())
         {
            AnsiString utf7String = Charset::ToMultiByte(subSet, PLATFORM_STRING("utf-7"));
            utf7String = utf7String.TrimLeft("+");
            utf7String = utf7String.TrimRight("-");

            sRetVal += "&"; 
            sRetVal += utf7String;
            sRetVal += "-";
         }
        
      }

      return sRetVal;
   }

   /*
   Converts a modified UTF-7 string to UTF-8.

   Example: 
      Input: TE&AOUA5AD2-ST
      Output: TEåäöST

   Implementation:
      We go through the input string one character at a time.
      We add the input character to the output buffer. If we find
      a &, that means we're entering an encoded subset. We locate
      the end of this subset (-) and the decode the subset.
   */

   String 
   ModifiedUTF7::Decode(const AnsiString &s)
   {
      String sRetVal;

      for (int iPos=0 ; iPos < s.GetLength(); iPos++)
      {
         char sCurrentChar = s[iPos];

         if ( IsSpecialCharacter_(sCurrentChar) )
         {
            // We should not have a special character here.
            return "";
         }

         if ( sCurrentChar != '&' )
         {
            sRetVal += sCurrentChar;
            continue;
         }

         // Move to next character
         iPos++;

         sCurrentChar = s[iPos];

         if ( sCurrentChar == '-' )
         {
            sRetVal += '&';
            continue;
         }

         // Locate the position of the next special character.
         int subsetStartPos = iPos;

         for (; iPos < s.GetLength(); iPos++)
         {
            sCurrentChar = s[iPos];
            if (sCurrentChar == '-')
               break;
         } 

         int subsetLength = iPos - subsetStartPos;
         String subSet = s.Mid(subsetStartPos, subsetLength);
         if (!subSet.IsEmpty())
         {
            String unicodeString = Charset::ToWideChar("+" + subSet + "-", PLATFORM_STRING("utf-7"));
            sRetVal += unicodeString;
         }
      }

      return sRetVal;
   }


   bool
   ModifiedUTF7::IsSpecialCharacter_(wchar_t c)
   {
      return c < 32 || c >= 127;
   }


   void
   ModifiedUTF7Tester::Test()
   {
      String s = ModifiedUTF7::Encode(PLATFORM_STRING("test"));
      if (s.Compare(PLATFORM_STRING("test")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("&"));
      if (s.Compare(PLATFORM_STRING("&-")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("TEST"));
      if (s.Compare(PLATFORM_STRING("TEST")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING(""));
      if (s.Compare(PLATFORM_STRING("")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("TE\\ST"));
      if (s.Compare(PLATFORM_STRING("TE\\ST")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("TEåäöST"));
      if (s.Compare(PLATFORM_STRING("TE&AOUA5AD2-ST")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("T"));
      if (s.Compare(PLATFORM_STRING("T")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("Å"));
      if (s.Compare(PLATFORM_STRING("&AMU-")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("Ä"));
      if (s.Compare(PLATFORM_STRING("&AMQ-")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("ÄÄÄÄÄÄÄÄÄÄÄÄÄ"));
      if (s.Compare(PLATFORM_STRING("&AMQAxADEAMQAxADEAMQAxADEAMQAxADEAMQ-")) != 0)
         throw;

      s = ModifiedUTF7::Encode(PLATFORM_STRING("ABCDEFGHIJKLMNOPQRSTUVXYZÅÄÖ,.<>-1234567890!¤%&/()=?"));
      if (s.Compare(PLATFORM_STRING("ABCDEFGHIJKLMNOPQRSTUVXYZ&AMUAxADW-,.<>-1234567890!&AKQ-%&-/()=?")) != 0)
         throw;

      s = ModifiedUTF7::Decode(ModifiedUTF7::Encode(PLATFORM_STRING("TEST")));
      if (s.Compare(PLATFORM_STRING("TEST")))
         throw;

      s = ModifiedUTF7::Decode(ModifiedUTF7::Encode(PLATFORM_STRING("ÅÄÖ")));
      if (s.Compare(PLATFORM_STRING("ÅÄÖ")))
         throw;

      s = ModifiedUTF7::Decode(ModifiedUTF7::Encode(PLATFORM_STRING("1234567890ABCDEFGHIJKLMNOPQRSTUVXYZÅÄÖ!#¤&%&()=?,<>")));
      if (s.Compare(PLATFORM_STRING("1234567890ABCDEFGHIJKLMNOPQRSTUVXYZÅÄÖ!#¤&%&()=?,<>")))
         throw;

      s = ModifiedUTF7::Decode("&AMQAxADEAMQAxADEAMQAxADEAMQAxADEAMQ-");
      if (s.Compare(PLATFORM_STRING("ÄÄÄÄÄÄÄÄÄÄÄÄÄ")) != 0)
         throw;

      s = ModifiedUTF7::Decode("&AMU-");
      if (s.Compare(PLATFORM_STRING("Å")) != 0)
         throw;

      s = ModifiedUTF7::Decode("&AMQ-");
      if (s.Compare(PLATFORM_STRING("Ä")) != 0)
         throw;
 
      s = ModifiedUTF7::Decode(ModifiedUTF7::Encode(PLATFORM_STRING("Ελληνικά")));
      if (s.Compare(PLATFORM_STRING("Ελληνικά")))
         throw;

      s = ModifiedUTF7::Decode(ModifiedUTF7::Encode(PLATFORM_STRING("&&&&----&")));
      if (s.Compare(PLATFORM_STRING("&&&&----&")))
         throw;
   }


}