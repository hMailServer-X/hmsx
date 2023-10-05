#include "pch.h"

#include "SSLCertificates.h"
#include "../Persistence/PersistentSSLCertificate.h"


namespace HM
{
   SSLCertificates::SSLCertificates()
   {
   }

   SSLCertificates::~SSLCertificates(void)
   {
   }


   void
   SSLCertificates::Refresh()
   //---------------------------------------------------------------------------()
   // DESCRIPTION:
   // Reads all SURBL servers from the database.
   //---------------------------------------------------------------------------()
   {
      String sSQL = "select * from hm_sslcertificates order by sslcertificatename asc";
      DBLoad_(sSQL);
   }

}