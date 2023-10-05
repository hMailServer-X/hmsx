#include "pch.h"
#include "IMAPCommand.h"

namespace HM
{
   IMAPCommand::IMAPCommand()
   {

   }

   IMAPCommand::~IMAPCommand()
   {

   }

   String
   IMAPCommandArgument::Literal(unsigned int Index)
   {
      if (Index >= literals_.size())
         return "";
      else 
         return literals_[Index];
   }

}
