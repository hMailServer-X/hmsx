#pragma once

namespace HM
{
   class DKIMParameters
   {
   public:
      
      void Load(const AnsiString &parameters);
      bool GetIsSet(const AnsiString &paramName) const;
      AnsiString GetValue(const AnsiString &paramName) const;

      

      size_t GetParamCount() const;

   private:

      std::map<AnsiString, AnsiString> parameters_;

      AnsiString  DKIMQPDecode_(AnsiString input) const;
   };

}