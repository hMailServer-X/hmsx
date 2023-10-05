#include "pch.h"
#include "IMAPFetchParser.h"

namespace HM
{
   IMAPFetchParser::BodyPart::BodyPart() : name_(""), 
      octet_start_(-1),
      octet_count_(-1),
      show_body_header_fields_(false),
      show_body_header_fields_NOT(false),
      show_body_header_(false),
      show_body_text_(false),
      show_body_full_(false)
   {

   }

   IMAPFetchParser::IMAPFetchParser()
   {
      show_envelope_ = false;
      show_rfcsize_ = false;
      show_uid_ = false;
      show_flags_ = false;
      show_internal_date_ = false;
      show_body_structure_ = false;
      set_seen_ = false;
      show_body_structure_NonExtensible = false;
   }

   IMAPFetchParser::~IMAPFetchParser()
   {

   }

   void
   IMAPFetchParser::CleanFetchString_(String &sString)
   {
      if (sString.Left(1) == PLATFORM_STRING(" "))
         sString = sString.Mid(1);
      
      if (sString.Left(1) == PLATFORM_STRING("("))
         sString = sString.Mid(1);

      if (sString.Right(1) == PLATFORM_STRING(")"))
         sString = sString.Mid(0, sString.GetLength() - 1);
      

   }

   IMAPResult
   IMAPFetchParser::ValidateSyntax_(const String &sString)
   {
      long lNoOfLeftPar = sString.NumberOf(PLATFORM_STRING("("));
      long lNoOfRightPar = sString.NumberOf(PLATFORM_STRING(")"));

      long lNoOfLeftBrack = sString.NumberOf(PLATFORM_STRING("["));
      long lNoOfRightBrack = sString.NumberOf(PLATFORM_STRING("]"));

      if (lNoOfLeftBrack != lNoOfRightBrack)
         return IMAPResult(IMAPResult::ResultBad, "Brackets are mismatching.");
         
      if (lNoOfLeftPar != lNoOfRightPar)
         return IMAPResult(IMAPResult::ResultBad, "Parenthesises are mismatching.");

      return IMAPResult();
    
   }

   std::vector<String>
   IMAPFetchParser::ParseString_(String &sString)
   {

      std::vector<String> vecResult;

      CleanFetchString_(sString);

      while (!sString.IsEmpty())
      {
         long lFirstLeftBracket = sString.Find(PLATFORM_STRING("["));
         long lFirstSpace = sString.Find(PLATFORM_STRING(" "));

         if (lFirstLeftBracket >= 0 && lFirstLeftBracket < lFirstSpace)
         {
            // Find end bracket.
            long lFirstRightBracket = sString.Find(PLATFORM_STRING("]"), lFirstLeftBracket);

            // Check if we got a <> directly after the []
            if (sString.SafeGetAt(lFirstRightBracket + 1) == '<')
               lFirstRightBracket = sString.Find(PLATFORM_STRING(">"), lFirstRightBracket);

            // Parse out string between brackets.
            if (lFirstRightBracket <= 0)
            {
               sString = sString.Mid(lFirstRightBracket + 1);
               continue;
            }

            // String between brackets.
            String sResString = sString.Mid(0, lFirstRightBracket+1 );
            vecResult.push_back(sResString);

            // Cut away this from the start string.
            sString = sString.Mid(lFirstRightBracket + 1);
         }
         else if (lFirstSpace >= 0)
         {
            // Copy string from here to end.
            String sResString = sString.Mid(0, lFirstSpace );

            vecResult.push_back(sResString);

            sString = sString.Mid(lFirstSpace + 1);

         }
         else
         {
            vecResult.push_back(sString);
            sString.Empty();
         }
         

         CleanFetchString_(sString);


      }

      return vecResult;
   }


   IMAPResult
   IMAPFetchParser::ParseCommand(const String &sCommand)
   {
      String sStringToParse = sCommand;
      
      IMAPResult result = ValidateSyntax_(sStringToParse);
      if (result.GetResult() != IMAPResult::ResultOK)
         return result;
      
      std::vector<String> vecResult = ParseString_(sStringToParse);
      auto iter = vecResult.begin();
      while (iter != vecResult.end())
      {
         String sPart = (*iter);

         
         ePartType iType = GetPartType_(sPart);

         switch (iType)
         {
            case BODYPEEK:
            {
               IMAPFetchParser::BodyPart oPart = ParseBODY_PEEK(sPart);
               parts_to_look_at_.push_back(oPart);
               break;
            }
            
            case ENVELOPE:
            {
               show_envelope_ = true;
               break;
            }
            
            case RFC822SIZE:
            {
               show_rfcsize_ = true;
               break;
            }

            case UID:
            {
               show_uid_ = true;
               break;
            }

            case FLAGS:
            {
               show_flags_ = true;
               break;
            }

            case INTERNALDATE:
            {
               show_internal_date_ = true;
               break;
            }

            case BODYSTRUCTURE:
            {
               show_body_structure_ = true;
               break;
            }
            
            case BODYSTRUCTURENONEXTENSIBLE:
            {
               show_body_structure_NonExtensible = true;
               break;
            }

            case BODY:
            {
               IMAPFetchParser::BodyPart oPart = ParseBODY_(sPart);
               parts_to_look_at_.push_back(oPart);
               break;
            }
            case RFC822:
            {
               // Same as:
               IMAPFetchParser::BodyPart oPart = ParseBODY_(sPart);
               oPart.SetDescription("RFC822");
               parts_to_look_at_.push_back(oPart);
               break;

            }
            case ALL:
            {
               // ALL
               // Macro equivalent to: (FLAGS INTERNALDATE RFC822.SIZE ENVELOPE)

               show_flags_ = true;
               show_internal_date_ = true;
               show_rfcsize_ = true;
               show_envelope_ = true;
               break;
            }

            case FAST:
            {
               // FAST
               // Macro equivalent to: (FLAGS INTERNALDATE RFC822.SIZE)

               show_flags_ = true;
               show_internal_date_ = true;
               show_rfcsize_ = true;
               break;
            }

            case FULL:
            {
               // FULL
               // Macro equivalent to: (FLAGS INTERNALDATE RFC822.SIZE ENVELOPE BODY)
               show_flags_ = true;
               show_internal_date_ = true;
               show_rfcsize_ = true;
               show_envelope_ = true;
               show_body_structure_ = true;
               break;
            }
            case RFC822HEADER:
            {
               /* 
                  RFC822.HEADER
                  Functionally equivalent to BODY.PEEK[HEADER], differing in the
                  syntax of the resulting untagged FETCH data (RFC822.HEADER is
                  returned).
                  */
            
               IMAPFetchParser::BodyPart oPart = ParseBODY_PEEK("BODY[HEADER]");
               oPart.SetDescription("RFC822.HEADER");
               parts_to_look_at_.push_back(oPart);
               break;
            }
            case RFC822TEXT:
               {
                  /* 
                  Functionally equivalent to BODY[TEXT], differing in the syntax
                  of the resulting untagged FETCH data (RFC822.TEXT is returned).
                  */

                  IMAPFetchParser::BodyPart oPart = ParseBODY_("BODY[TEXT]");
                  oPart.SetDescription("RFC822.TEXT");
                  parts_to_look_at_.push_back(oPart);

                  break;
               }
         }

         iter++;
      }

      return IMAPResult();
   }

   IMAPFetchParser::BodyPart
   IMAPFetchParser::ParseBODY_(const String &sString)
   {
      BodyPart oPart;
      
      // Set the description.

      String sNewName = sString;
      sNewName.ReplaceNoCase(PLATFORM_STRING("BODY.PEEK["), PLATFORM_STRING("BODY["));

      oPart.SetDescription(sNewName);

      // Locate the start of the peek-part.
      long lBodyStart = sNewName.Find(PLATFORM_STRING("[")) + 1;
      
      // Locate the end of the part.
      long lBodyEnd = sNewName.Find(PLATFORM_STRING("]"), lBodyStart) - 1;

      if (sNewName.Find(PLATFORM_STRING("<"), lBodyEnd) == lBodyEnd +2)
      {
         int iStart = lBodyEnd+3;
         int iEnd = sNewName.Find(PLATFORM_STRING(">"), iStart);

         String sPartial = sNewName.Mid(iStart, iEnd - iStart);
         int iDotPos = sPartial.Find(PLATFORM_STRING("."));
         
         oPart.octet_start_ = _ttoi(sPartial.Mid(0, iDotPos));
         oPart.octet_count_ = _ttoi(sPartial.Mid(iDotPos+1));

         // Remove the octets part from the description.
         String sBefore = sNewName.Mid(0, iStart - 1);
         String sAfter = sNewName.Mid(iEnd + 1);

         String sDescWithoutOctets = sBefore + sAfter;

         oPart.SetDescription(sDescWithoutOctets);
      }

      // Extract the body  part.
      long lBodyLen = lBodyEnd - lBodyStart +1 ;
      String sBody = sNewName.Mid(lBodyStart, lBodyLen);

      if (sBody.IsEmpty())
      {
         oPart.SetShowBodyFull(true);
         set_seen_ = true;
      }
      else
      {
         // Determine what to look at.
         long lTemp  = 0;

         // Should we show all header fields except for...
         lTemp = sBody.FindNoCase(PLATFORM_STRING("HEADER.FIELDS.NOT"));
         if (lTemp >= 0)
         {
            int lStart = sBody.Find(PLATFORM_STRING("("), lTemp) + 1;
            int lEnd = sBody.Find(PLATFORM_STRING(")"), lStart) ;
            int lLength = lEnd - lStart;
            
            String sFields = sBody.Mid(lStart, lLength);
            oPart.GetHeaderFieldsNOT() = StringParser::SplitString(sFields, " ");
            oPart.SetShowBodyHeaderFieldsNOT(true);

            // Strip away the header fields part from the Body.
            // If we don't do this, we will parse the same string
            // as header.fields below.
            String sBefore = sBody.Mid(0, lTemp);
            String sAfter = sBody.Mid(lEnd + 2);
            sBody = sBefore + sAfter;

         }

         // Should we show header fields?
         lTemp = sBody.FindNoCase(PLATFORM_STRING("HEADER.FIELDS"));
         if (lTemp >= 0)
         {
            int lStart = sBody.Find(PLATFORM_STRING("("), lTemp) + 1;
            int lEnd = sBody.Find(PLATFORM_STRING(")"), lStart) ;
            int lLength = lEnd - lStart;
            
            String sFields = sBody.Mid(lStart, lLength);
            oPart.GetHeaderFields() = StringParser::SplitString(sFields, " ");
            oPart.SetShowBodyHeaderFields(true);

            // Strip away the header fields part from the Body.
            String sBefore = sBody.Mid(0, lTemp);
            String sAfter = sBody.Mid(lEnd + 2);
            sBody = sBefore + sAfter;
         }

         lTemp = sBody.FindNoCase(PLATFORM_STRING("HEADER"));
         if (lTemp >= 0)
         {
            oPart.SetShowBodyHeader(true);
            
            String sBefore = sBody.Mid(0, lTemp);
            String sAfter = sBody.Mid(lTemp + 7);
            sBody = sBefore + sAfter;
         }

         lTemp = sBody.FindNoCase(PLATFORM_STRING("MIME"));
         if (lTemp >= 0)
         {
            oPart.SetShowBodyHeader(true);

            String sBefore = sBody.Mid(0, lTemp);
            String sAfter = sBody.Mid(lTemp + 7);
            sBody = sBefore + sAfter;
         }

         lTemp = sBody.FindNoCase(PLATFORM_STRING("TEXT"));
         if (lTemp >= 0)
         {
            oPart.SetShowBodyText(true);
            
            String sBefore = sBody.Mid(0, lTemp);
            String sAfter = sBody.Mid(lTemp + 5);
            sBody = sBefore + sAfter;

            set_seen_ = true;
         }

         if (!oPart.GetShowBodyText() &&
             !oPart.GetShowBodyHeader() &&
             !oPart.GetShowBodyHeaderFields() &&
             !oPart.GetShowBodyHeaderFieldsNOT())
         {
             oPart.SetShowBodyText(true);
             set_seen_ = true;
         }
         
         sBody = sBody.TrimLeft(PLATFORM_STRING("."));
         sBody = sBody.TrimRight(PLATFORM_STRING("."));

         oPart.SetName(sBody);
      }

      return oPart;

   }



   
   IMAPFetchParser::ePartType
   IMAPFetchParser::GetPartType_(const String &sPart)
   {
      if (sPart.FindNoCase(PLATFORM_STRING("BODY.PEEK")) >= 0)
         return BODYPEEK;

      if (sPart.CompareNoCase(PLATFORM_STRING("BODYSTRUCTURE")) == 0)
         return BODYSTRUCTURE;      

      if (sPart.CompareNoCase(PLATFORM_STRING("BODY")) == 0)
         return BODYSTRUCTURENONEXTENSIBLE;

      if (sPart.FindNoCase(PLATFORM_STRING("BODY")) >= 0)
         return BODY;

      if (sPart.CompareNoCase(PLATFORM_STRING("ENVELOPE")) == 0)
         return ENVELOPE;      

      if (sPart.CompareNoCase(PLATFORM_STRING("RFC822.SIZE")) == 0)
         return RFC822SIZE;         

      if (sPart.CompareNoCase(PLATFORM_STRING("UID")) == 0)
         return UID;  

      if (sPart.CompareNoCase(PLATFORM_STRING("FLAGS")) == 0)
         return FLAGS;  

      if (sPart.CompareNoCase(PLATFORM_STRING("INTERNALDATE")) == 0)
         return INTERNALDATE;  

      if (sPart.CompareNoCase(PLATFORM_STRING("RFC822")) == 0)
         return RFC822;  

      if (sPart.CompareNoCase(PLATFORM_STRING("ALL")) == 0)
         return ALL;  

      if (sPart.CompareNoCase(PLATFORM_STRING("FAST")) == 0)
         return FAST;  

      if (sPart.CompareNoCase(PLATFORM_STRING("FULL")) == 0)
         return FULL;  

      if (sPart.CompareNoCase(PLATFORM_STRING("RFC822.HEADER")) == 0)
         return RFC822HEADER;  

      if (sPart.CompareNoCase(PLATFORM_STRING("RFC822.TEXT")) == 0)
         return RFC822TEXT;  

      return PARTUNKNOWN;
   }


   IMAPFetchParser::BodyPart
   IMAPFetchParser::ParseBODY_PEEK(const String &sString)
   {
      BodyPart oPart = ParseBODY_(sString);
      set_seen_ = false;

      return oPart;
   }

   bool 
   IMAPFetchParser::IsPartSpecifier_(const String &sString)
   {
      String sTemp = sString;
      sTemp.ToUpper();
      sTemp.Replace(PLATFORM_STRING("."), PLATFORM_STRING(""));
      sTemp.Replace(PLATFORM_STRING("MIME"), PLATFORM_STRING(""));
      sTemp.Replace(PLATFORM_STRING("HEADER"), PLATFORM_STRING(""));
      sTemp.Replace(PLATFORM_STRING("TEXT"), PLATFORM_STRING(""));

      if (sTemp.GetLength() == 0)
         return false;

      if (StringParser::IsNumeric(sTemp))      
         return true;

      return false;

      
      
   }
}

