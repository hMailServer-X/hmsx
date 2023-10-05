#include "pch.h"
#include "TCPIPPort.h"
#include "SSLCertificates.h"

namespace HM
{
   TCPIPPort::TCPIPPort(void) :
      port_number_(0),
      port_protocol_(STUnknown),
      sslcertificate_id_(0),
      connection_security_(CSNone)
   {

   }

   TCPIPPort::~TCPIPPort(void)
   {
   }

   String 
   TCPIPPort::GetName() const
   {
      String sName;
      sName.Format(PLATFORM_STRING("%d-%d"), port_protocol_, port_number_);

      return sName;
   }

   bool 
   TCPIPPort::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("TCPIPPort"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), GetName());
      pNode->AppendAttr(PLATFORM_STRING("PortProtocol"), StringParser::IntToString(port_protocol_));
      pNode->AppendAttr(PLATFORM_STRING("PortNumber"), StringParser::IntToString(port_number_));
      pNode->AppendAttr(PLATFORM_STRING("ConnectionSecurity"), StringParser::IntToString(connection_security_));
      pNode->AppendAttr(PLATFORM_STRING("Address"), String(address_.ToString()));
      
      if (sslcertificate_id_ > 0)
      {
         pNode->AppendAttr(PLATFORM_STRING("SSLCertificateName"), GetSSLCertificateName_(sslcertificate_id_));
      }

      return true;
   }

   bool 
   TCPIPPort::XMLLoad(XNode *pNode, int iOptions)
   {
      port_protocol_ = (SessionType) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("PortProtocol")));
      port_number_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("PortNumber")));

      address_.TryParse(pNode->GetAttrValue(PLATFORM_STRING("Address")));
      sslcertificate_id_  = GetSSLCertificateID_(pNode->GetAttrValue(PLATFORM_STRING("SSLCertificateName")));

      // Backwards compatibiltiy
      if (pNode->GetAttrValue(PLATFORM_STRING("UseSSL")) == PLATFORM_STRING("1"))
      {
         connection_security_ = CSSSL;
      }
      else
      {
         connection_security_ = (ConnectionSecurity) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("ConnectionSecurity")));
      }

      return true;
   }

   int
   TCPIPPort::GetSSLCertificateID_(const String &sSSLCertificateName)
   {
      if (sSSLCertificateName.IsEmpty())
         return 0;

      std::shared_ptr<SSLCertificates> pSSLCertificates = std::shared_ptr<SSLCertificates>(new SSLCertificates);
      pSSLCertificates->Refresh();

      std::shared_ptr<SSLCertificate> pCertificate = pSSLCertificates->GetItemByName(sSSLCertificateName);
      if (pCertificate)
         return (int) pCertificate->GetID();
      else
         return 0;

   }

   String 
   TCPIPPort::GetSSLCertificateName_(long long iCertificateID)
   {
      std::shared_ptr<SSLCertificates> pSSLCertificates = std::shared_ptr<SSLCertificates>(new SSLCertificates);
      pSSLCertificates->Refresh();

      std::shared_ptr<SSLCertificate> pCertificate = pSSLCertificates->GetItemByDBID(iCertificateID);
      if (pCertificate)
         return pCertificate->GetName();
      else
         return "";

   }

   bool
   TCPIPPort::SetAddress(const String &address)
   {
      IPAddress listeningAddress;
      if (!listeningAddress.TryParse(address))
         return false;
      
      SetAddress(listeningAddress);
      return true;
   }

   void 
   TCPIPPort::SetAddress(const IPAddress &address)
   {
      address_ = address;
   }

   String
   TCPIPPort::GetAddressString() const
   {
      return address_.ToString();
   }

   IPAddress
   TCPIPPort::GetAddress() const
   {
      return address_;
   }
}