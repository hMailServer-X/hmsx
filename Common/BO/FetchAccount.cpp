#include "pch.h"
#include "Fetchaccount.h"
#include "FetchAccountUIDs.h"
#include "FetchAccountUID.h"
#include "../Util/Crypt.h"

namespace HM
{


   FetchAccount::FetchAccount(void) :
      account_id_(0),
      port_(0),
      minutes_(30),
      days_to_keep_(0),
      is_active_(1),
      process_mimerecipients_(false),
      process_mimedate_(false),
      server_type_(POP3),
      use_anti_spam_(false),
      use_anti_virus_(false),
      enable_route_recipients_(false),
      connection_security_(CSNone)      
   {
 
   }

   FetchAccount::~FetchAccount(void)
   {

   }

   std::shared_ptr<FetchAccountUIDs>
   FetchAccount::GetUIDs()
   {
      if (!uids_)
      {
         uids_ = std::shared_ptr<FetchAccountUIDs> (new FetchAccountUIDs);
         uids_->Refresh(id_);
      }

      return uids_;
   }

   bool 
   FetchAccount::XMLStore(XNode *pRuleNode, int iOptions)
   {
      XNode *pNode = pRuleNode->AppendChild(PLATFORM_STRING("FetchAccount"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("ServerAddress"), server_address_);
      pNode->AppendAttr(PLATFORM_STRING("ServerType"), StringParser::IntToString(server_type_));
      pNode->AppendAttr(PLATFORM_STRING("Port"), StringParser::IntToString(port_));
      pNode->AppendAttr(PLATFORM_STRING("Username"), username_);
      pNode->AppendAttr(PLATFORM_STRING("Password"), Crypt::Instance()->EnCrypt(password_, Crypt::ETBlowFish));
      pNode->AppendAttr(PLATFORM_STRING("Minutes"), StringParser::IntToString(minutes_));
      pNode->AppendAttr(PLATFORM_STRING("DaysToKeep"), StringParser::IntToString(days_to_keep_));
      pNode->AppendAttr(PLATFORM_STRING("Active"), is_active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("MIMERecipientHeaders"), mime_recipient_headers_);
      pNode->AppendAttr(PLATFORM_STRING("ProcessMIMERecipients"), process_mimerecipients_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("ProcessMIMEDate"), process_mimedate_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("UseAntiSpam"), use_anti_spam_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("UseAntiVirus"), use_anti_virus_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("EnableRouteRecipients"), enable_route_recipients_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("ConnectionSecurity"), StringParser::IntToString(connection_security_));

      if (!GetUIDs()->XMLStore(pNode, iOptions))
         return false;

      return true;
   }

   bool
   FetchAccount::XMLLoad(XNode *pNode, int iOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      server_address_ = pNode->GetAttrValue(PLATFORM_STRING("ServerAddress"));
      server_type_ = (ServerType)_ttoi(pNode->GetAttrValue(PLATFORM_STRING("ServerType")));
      port_ =  _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Port")));
      username_ = pNode->GetAttrValue(PLATFORM_STRING("Username"));
      password_ = Crypt::Instance()->DeCrypt(pNode->GetAttrValue(PLATFORM_STRING("Password")), Crypt::ETBlowFish);
      minutes_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Minutes")));
      days_to_keep_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("DaysToKeep")));
      is_active_ = (pNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1"));
      mime_recipient_headers_ = pNode->GetAttrValue(PLATFORM_STRING("MIMERecipientHeaders"));
      process_mimerecipients_ = (pNode->GetAttrValue(PLATFORM_STRING("ProcessMIMERecipients")) == PLATFORM_STRING("1"));
      process_mimedate_ = (pNode->GetAttrValue(PLATFORM_STRING("ProcessMIMEDate")) == PLATFORM_STRING("1"));
      use_anti_spam_ = (pNode->GetAttrValue(PLATFORM_STRING("UseAntiSpam")) == PLATFORM_STRING("1"));
      use_anti_virus_ = (pNode->GetAttrValue(PLATFORM_STRING("UseAntiVirus")) == PLATFORM_STRING("1"));
      enable_route_recipients_ = (pNode->GetAttrValue(PLATFORM_STRING("EnableRouteRecipients")) == PLATFORM_STRING("1"));

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

   bool 
   FetchAccount::XMLLoadSubItems(XNode *pNode, int iRestoreOptions)
   {
      if (!GetUIDs()->XMLLoad(pNode, iRestoreOptions))
         return false;

      return true;
   }
}