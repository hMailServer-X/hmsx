#include "pch.h"
#include "SQLCommand.h"

namespace HM
{

   SQLCommand::SQLCommand()
   {

   }

   SQLCommand::SQLCommand(const String &queryString) :
      query_string_(queryString)
   {
      
   }

   void
   SQLCommand::AddParameter(const AnsiString &name, const int &value)
   {
      SQLParameter parameter(name, value);

      parameters_.push_back(parameter);
   }

   void
   SQLCommand::AddParameter(const AnsiString &name, const long long &value)
   {
      SQLParameter parameter(name, value);

      parameters_.push_back(parameter);
   }


   void
   SQLCommand::AddParameter(const AnsiString &name, const String& value)
   {
      SQLParameter parameter(name, value);

      parameters_.push_back(parameter);
   }

   void
   SQLCommand::AddParameter(const AnsiString &name, unsigned int value)
   {
      SQLParameter parameter(name, value);

      parameters_.push_back(parameter);
   }


   String 
   SQLCommand::GetQueryString() const
   {
      return query_string_;
   }

   void
   SQLCommand::SetQueryString(const String &value)
   {
      query_string_ = value;
   }


   const std::list<SQLParameter> &
   SQLCommand::GetParameters() const
   {
      return parameters_;
   }

   void 
   SQLCommand::ClearParameters()
   {
      parameters_.clear();
   }
}
