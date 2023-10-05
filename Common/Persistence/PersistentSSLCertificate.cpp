#include "pch.h"

#include "./PersistentSSLCertificate.h"
#include "../BO/SSLCertificate.h"
#include "../SQL/SQLStatement.h"

namespace HM
{
   PersistentSSLCertificate::PersistentSSLCertificate(void)
   {
   }

   PersistentSSLCertificate::~PersistentSSLCertificate(void)
   {
   }

   bool
   PersistentSSLCertificate::DeleteObject(std::shared_ptr<SSLCertificate> pObject)
   {
      SQLCommand command(PLATFORM_STRING("delete from hm_sslcertificates where sslcertificateid = @CERTIFICATEID"));
      command.AddParameter("@CERTIFICATEID", pObject->GetID());
      
      return Application::Instance()->GetDBManager()->Execute(command);
   }

   bool 
   PersistentSSLCertificate::ReadObject(std::shared_ptr<SSLCertificate> pObject, std::shared_ptr<DALRecordset> pRS)
   {
      pObject->SetID (pRS->GetLongValue("sslcertificateid"));
      pObject->SetName(pRS->GetStringValue("sslcertificatename"));
      pObject->SetCertificateFile(pRS->GetStringValue("sslcertificatefile"));
      pObject->SetPrivateKeyFile(pRS->GetStringValue("sslprivatekeyfile"));

      return true;
   }

   bool 
   PersistentSSLCertificate::SaveObject(std::shared_ptr<SSLCertificate> pObject, String &errorMessage,  PersistenceMode mode)
   {
      // errorMessage - not supported yet.
      return SaveObject(pObject);
   }

   bool 
   PersistentSSLCertificate::SaveObject(std::shared_ptr<SSLCertificate> pObject)
   {
      SQLStatement oStatement;
      oStatement.SetTable("hm_sslcertificates");
      
      if (pObject->GetID() == 0)
      {
         oStatement.SetStatementType(SQLStatement::STInsert);
         oStatement.SetIdentityColumn("sslcertificateid");
      }
      else
      {
         oStatement.SetStatementType(SQLStatement::STUpdate);
         String sWhere;
         sWhere.Format(PLATFORM_STRING("sslcertificateid = %I64d"), pObject->GetID());
         oStatement.SetWhereClause(sWhere);
         
      }

      oStatement.AddColumn(PLATFORM_STRING("sslcertificatename"), pObject->GetName());
      oStatement.AddColumn(PLATFORM_STRING("sslcertificatefile"), pObject->GetCertificateFile());
      oStatement.AddColumn(PLATFORM_STRING("sslprivatekeyfile"), pObject->GetPrivateKeyFile());

      bool bNewObject = pObject->GetID() == 0;

      // Save and fetch ID
      long long iDBID = 0;
      bool bRetVal = Application::Instance()->GetDBManager()->Execute(oStatement, bNewObject ? &iDBID : 0);
      if (bRetVal && bNewObject)
         pObject->SetID((int) iDBID);


      return true;
   }
}