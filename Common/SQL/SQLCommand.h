#pragma once

#include "SQLParameter.h"

namespace HM
{

   class SQLCommand
   {
   public:
      SQLCommand();
      explicit SQLCommand(const String &queryString);

      void SetQueryString(const String &queryString);
      String GetQueryString() const;
      const std::list<SQLParameter> &GetParameters() const;
      void ClearParameters();

      void AddParameter(const AnsiString &name, const int &value);
      void AddParameter(const AnsiString &name, const long long &value);
      void AddParameter(const AnsiString &name, const String& value);
      void AddParameter(const AnsiString &name, unsigned int value);
      

   private:

      std::list<SQLParameter> parameters_;

      String query_string_;
   };
}
