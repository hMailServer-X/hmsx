#include "pch.h"
#include "SSLCertificate.h"

namespace HM
{
   SSLCertificate::SSLCertificate(void)
   {
      
   }

   SSLCertificate::~SSLCertificate(void)
   {
   }

   bool 
   SSLCertificate::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("SSLCertificate"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("CertificateFile"), certificate_file_);
      pNode->AppendAttr(PLATFORM_STRING("PrivateKeyFile"), private_key_file_);

      return true;
   }

   bool 
   SSLCertificate::XMLLoad(XNode *pNode, int iOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      certificate_file_ = pNode->GetAttrValue(PLATFORM_STRING("CertificateFile"));
      private_key_file_ = pNode->GetAttrValue(PLATFORM_STRING("PrivateKeyFile"));

      return true;
   }
}