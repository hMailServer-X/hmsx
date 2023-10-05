#pragma once

namespace HM
{
   class SQLCommand;

   class DALRecordset  
   {
   public:
      DALRecordset();
      virtual ~DALRecordset();

      bool Open(std::shared_ptr<DALConnection> pConn, const SQLCommand &command);

      virtual DALConnection::ExecutionResult TryOpen(std::shared_ptr<DALConnection> pConn, const SQLCommand &command, String &sErrorMessage) = 0;

      virtual long RecordCount() const = 0;
      virtual bool MoveNext() = 0;
      virtual bool IsEOF() const = 0;          

      virtual String GetStringValue(const AnsiString &FieldName) const= 0;
      virtual long GetLongValue(const AnsiString &FieldName) const = 0;
      virtual long long GetInt64Value(const AnsiString &FieldName) const =0 ;
      virtual double GetDoubleValue(const AnsiString &FieldName) const = 0;

      virtual bool GetIsNull(const AnsiString &FieldName) const = 0;
      virtual std::vector<AnsiString> GetColumnNames() const = 0;



   protected:
      void ReportEOFError_(const AnsiString &FieldName) const;

   private:

   };
}
