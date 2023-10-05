#include "pch.h"
#include "SQLParameter.h"

namespace HM
{
   SQLParameter::SQLParameter(const String& name, const int &value) :
      column_name_(name),
      type_(ParamTypeInt32)
   {
      ResetValues_();
      int_32value_ = value;
   }

   SQLParameter::SQLParameter(const String& name, const long long &value) :
      column_name_(name),
      type_(ParamTypeInt64)
   {
      ResetValues_();
      int_64value_ = value;
   }

   SQLParameter::SQLParameter(const String& name, const String &value) :
      column_name_(name),
      type_(ParamTypeString)
   {
      ResetValues_();
      string_value_ = value;
   }


   SQLParameter::SQLParameter(const String& name, unsigned int value) :
      column_name_(name),
      type_(ParamTypeUnsignedInt32)
   {
      ResetValues_();
      unsigned_int_32value_ = value;
   }

   void 
   SQLParameter::ResetValues_()
   {
      int_32value_ = 0;
      int_64value_ = 0;
      string_value_ = "";
      unsigned_int_32value_ = 0;
   }

   int 
   SQLParameter::GetType() const
   {
      return type_;
   }

   String
   SQLParameter::GetName() const
   {
      return column_name_;
   }

   int 
   SQLParameter::GetInt32Value() const
   {
      return int_32value_;
   }

   unsigned int 
   SQLParameter::GetUnsignedInt32Value() const
   {
      return unsigned_int_32value_;
   }

   long long 
   SQLParameter::GetInt64Value() const
   {
      return int_64value_;
   }

   String 
   SQLParameter::GetStringValue() const
   {
      return string_value_;
   }
}
