#include "pch.h"
#include "./imapsortparser.h"

namespace HM
{
   IMAPSortParser::IMAPSortParser(void)
   {
   }

   IMAPSortParser::~IMAPSortParser(void)
   {
   }

   void 
   IMAPSortParser::Parse(const String &sExpression)
   {
      std::vector<String> vecSortCriterias = StringParser::SplitString(sExpression, " ");
      auto iter = vecSortCriterias.begin();
      while (iter != vecSortCriterias.end())
      {
         String sPart = (*iter);

         sPart.ToUpper();
         
         if (sPart == PLATFORM_STRING("REVERSE"))
         {
            iter++;
            if (iter != vecSortCriterias.end())
            {
               sPart = (*iter);
               sort_types_.push_back(std::make_pair(false, sPart));
            }
         }
         else
         {
            sort_types_.push_back(std::make_pair(true, sPart));
         }

         if (iter != vecSortCriterias.end())
            iter++;
      }
   }
}