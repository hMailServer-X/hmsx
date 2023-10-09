#include "pch.h"

#include "Account.h"
#include "Rules.h"
#include "Messages.h"
#include "IMAPFolders.h"
#include "../Util/Crypt.h"
#include "../Util/Time.h"
#include "FetchAccounts.h"

#include "../../SMTP/SMTPVacationMessageCreator.h"
#include "../Persistence/PersistentAccount.h"
#include "../Cache/AccountSizeCache.h"

namespace HM
{
   Account::Account() :
      domain_id_(0),
      forward_enabled_(false),
      forward_keep_original_(false),
      active_(false),
      is_ad_(false),
      account_max_size_(0),
      vacation_message_is_on_(false),
      password_encryption_(0),
      admin_level_(NormalUser),
      enable_signature_(false),
      vacation_expires_(false)
   {
      Initialize();
   }

   Account::Account(const String &address, AdminLevel adminLevel) :
      address_(address),
      domain_id_(0),
      forward_enabled_(false),
      forward_keep_original_(false),
      active_(false),
      is_ad_(false),
      account_max_size_(0),
      vacation_message_is_on_(false),
      password_encryption_(0),
      admin_level_(adminLevel),
      enable_signature_(false),
      vacation_expires_(false)
   {
      Initialize();
   }

   void
   Account::Initialize()
   {
      last_logon_time_ = Time::GetCurrentDateTime();
      vacation_expires_date_ = Time::GetCurrentDate();
   }


   Account::~Account()
   {
   
   }

   Account::Account(const Account &oldAccount)
   {
      id_ = oldAccount.id_;
      domain_id_ = oldAccount.domain_id_;
      account_max_size_ = oldAccount.account_max_size_;
      password_encryption_ = oldAccount.password_encryption_;
      address_ = oldAccount.address_;
      password_ = oldAccount.password_;
      addomain_ = oldAccount.addomain_;
      adusername_ = oldAccount.adusername_;
      person_first_name_ = oldAccount.person_first_name_;
      person_last_name_ = oldAccount.person_last_name_;
      vacation_message_ = oldAccount.vacation_message_;
      vacation_subject_ = oldAccount.vacation_subject_;
      vacation_expires_ = oldAccount.vacation_expires_;
      vacation_expires_date_ = oldAccount.vacation_expires_date_;
      signature_plain_text_ = oldAccount.signature_plain_text_;
      signature_html_ = oldAccount.signature_html_;
      forward_address_ = oldAccount.forward_address_;
      forward_enabled_ = oldAccount.forward_enabled_;
      forward_keep_original_ = oldAccount.forward_keep_original_;
      active_ = oldAccount.active_;
      is_ad_ = oldAccount.is_ad_;
      vacation_message_is_on_ = oldAccount.vacation_message_is_on_;
      enable_signature_ = oldAccount.enable_signature_;
      admin_level_ = oldAccount.admin_level_;
      last_logon_time_ = oldAccount.last_logon_time_;
   }

   std::shared_ptr<Messages>
   Account::GetMessages()
   {
      if (messages_.get() == NULL)
      {
         messages_ = std::shared_ptr<Messages>(new Messages(id_, -1));
         messages_->Refresh(false);
      }

      return messages_;
   }

   std::shared_ptr<Rules>
   Account::GetRules()
   {
      if (rules_.get() == NULL)
      {
         rules_ = std::shared_ptr<Rules>(new Rules(id_));
         rules_->Refresh();
      }
   
      return rules_;
   }

   std::shared_ptr<IMAPFolders>
   Account::GetFolders()
   {
      if (folders_.get() == NULL)
      {
         folders_ = std::shared_ptr<IMAPFolders>(new HM::IMAPFolders(id_, -1));
         folders_->Refresh();

      }

      return folders_;
   }


   void 
   Account::SetPassword(const String & newVal)
   {
      password_ = newVal; 
   }

   void
   Account::SetVacationMessageIsOn(bool bNewVal)
   {
      if (!bNewVal && vacation_message_is_on_)
      {
         // The user has just turned of the vacation
         // message. Notify the SMTP deliverer of this.

         if (!address_.IsEmpty())
            SMTPVacationMessageCreator::Instance()->VacationMessageTurnedOff(address_);
      }

      vacation_message_is_on_ = bNewVal;
   }

   bool
   Account::SpaceAvailable(long long iBytes) const
   {
      if (account_max_size_ == 0)
         return true;

      long long currentSize = AccountSizeCache::Instance()->GetSize(id_);

      // Calculate new size
      long long iNewSize = currentSize + iBytes;
      long long iMaxSize = ((long long) account_max_size_) * 1024 * 1024;

      if (iNewSize <= iMaxSize)
         return true;
      else
         return false;
   }

   bool 
   Account::GetForwardEnabled() const
   {
      return forward_enabled_;
   }

   void 
   Account::SetForwardEnabled(bool bEnabled)
   {
      forward_enabled_ = bEnabled;
   }

   bool 
   Account::GetForwardKeepOriginal() const
   {
      return forward_keep_original_;
   }

   void 
   Account::SetForwardKeepOriginal(bool bEnabled)
   {
      forward_keep_original_ = bEnabled;
   }

   bool 
   Account::GetEnableSignature() const
   {
      return enable_signature_;
   }

   void 
   Account::SetEnableSignature(bool bEnabled)
   {
      enable_signature_ = bEnabled;
   }

   String 
   Account::GetSignaturePlainText() const
   {
      return signature_plain_text_;
   }

   void 
   Account::SetSignaturePlainText(const String &sSignature)
   {
      signature_plain_text_ = sSignature;
   }

   String 
   Account::GetSignatureHTML() const
   {
      return signature_html_;
   }

   void 
   Account::SetSignatureHTML(const String &sSignature)
   {
      signature_html_ = sSignature;
   }

   String 
   Account::GetLastLogonTime() const
   {
      return last_logon_time_;
   }

   void 
   Account::SetLastLogonTime(const String &sNewVal)
   {
      last_logon_time_ = sNewVal;
   }

   String 
   Account::GetPersonFirstName() const
   {
      return person_first_name_;
   }

   void 
   Account::SetPersonFirstName(const String &sNewVal)
   {
      person_first_name_ = sNewVal;
   }

   String 
   Account::GetPersonLastName() const
   {
      return person_last_name_;
   }

   void 
   Account::SetPersonLastName(const String &sNewVal)
   {
      person_last_name_ = sNewVal;
   }

   bool 
   Account::XMLStore(XNode *pParentNode, int iBackupOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Account"));

      Logger::Instance()->LogBackup("Backing up account " + address_ + "...");

      pNode->AppendAttr(PLATFORM_STRING("Name"), String(address_));
      pNode->AppendAttr(PLATFORM_STRING("PersonFirstName"), person_first_name_);
      pNode->AppendAttr(PLATFORM_STRING("PersonLastName"), person_last_name_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), active_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("Password"), String(password_));
      pNode->AppendAttr(PLATFORM_STRING("PasswordEncryption"), StringParser::IntToString(password_encryption_));
      pNode->AppendAttr(PLATFORM_STRING("MaxAccountSize"), StringParser::IntToString(account_max_size_));
      pNode->AppendAttr(PLATFORM_STRING("ADUsername"), adusername_);
      pNode->AppendAttr(PLATFORM_STRING("ADDomain"), addomain_);
      pNode->AppendAttr(PLATFORM_STRING("ADActive"), is_ad_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("VacationMessageOn"), vacation_message_is_on_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("VacationMessage"), vacation_message_);
      pNode->AppendAttr(PLATFORM_STRING("VacationSubject"), vacation_subject_);
      pNode->AppendAttr(PLATFORM_STRING("VacationExpires"), vacation_expires_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("VacationExpireDate"), vacation_expires_date_);
      pNode->AppendAttr(PLATFORM_STRING("AdminLevel"), StringParser::IntToString(admin_level_));
      
      pNode->AppendAttr(PLATFORM_STRING("ForwardEnabled"), forward_enabled_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("ForwardAddress"), String(forward_address_));
      pNode->AppendAttr(PLATFORM_STRING("ForwardKeepOriginal"), forward_keep_original_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));

      pNode->AppendAttr(PLATFORM_STRING("EnableSignature"), enable_signature_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("SignaturePlainText"), signature_plain_text_);
      pNode->AppendAttr(PLATFORM_STRING("SignatureHTML"), signature_html_);

      pNode->AppendAttr(PLATFORM_STRING("LastLogonTime"), String(last_logon_time_));

      // Store fetch accounts
      std::shared_ptr<HM::FetchAccounts> pFetchAccounts = std::shared_ptr<HM::FetchAccounts>(new HM::FetchAccounts(id_));
      pFetchAccounts->Refresh();
      if (!pFetchAccounts->XMLStore(pNode, iBackupOptions))
         return false;

      // Store rules
      if (!GetRules()->XMLStore(pNode,iBackupOptions))
         return false;


      return true;
   }

   bool
   Account::XMLLoad(XNode *pAccountNode, int iRestoreOptions)
   {
      address_ = pAccountNode->GetAttrValue(PLATFORM_STRING("Name"));

      Logger::Instance()->LogBackup("Restoring account " + address_ + "...");

      person_first_name_ = pAccountNode->GetAttrValue(PLATFORM_STRING("PersonFirstName"));;
      person_last_name_ = pAccountNode->GetAttrValue(PLATFORM_STRING("PersonLastName"));;
      active_ = (pAccountNode->GetAttrValue(PLATFORM_STRING("Active")) == PLATFORM_STRING("1"));
      password_ = pAccountNode->GetAttrValue(PLATFORM_STRING("Password"));
      password_encryption_ = _ttoi(pAccountNode->GetAttrValue(PLATFORM_STRING("PasswordEncryption")));
      account_max_size_ = _ttoi(pAccountNode->GetAttrValue(PLATFORM_STRING("MaxAccountSize")));
      adusername_ = pAccountNode->GetAttrValue(PLATFORM_STRING("ADUsername"));
      addomain_ = pAccountNode->GetAttrValue(PLATFORM_STRING("ADDomain"));
      is_ad_ = pAccountNode->GetAttrValue(PLATFORM_STRING("ADActive")) == PLATFORM_STRING("1");
      vacation_message_is_on_ = pAccountNode->GetAttrValue(PLATFORM_STRING("VacationMessageOn")) == PLATFORM_STRING("1");
      vacation_message_ = pAccountNode->GetAttrValue(PLATFORM_STRING("VacationMessage"));
      vacation_subject_ = pAccountNode->GetAttrValue(PLATFORM_STRING("VacationSubject"));
      vacation_expires_ = (pAccountNode->GetAttrValue(PLATFORM_STRING("VacationExpires")) == PLATFORM_STRING("1"));
      vacation_expires_date_ = pAccountNode->GetAttrValue(PLATFORM_STRING("VacationExpireDate"));

      admin_level_ = (AdminLevel) _ttoi(pAccountNode->GetAttrValue(PLATFORM_STRING("AdminLevel")));
     
      forward_address_ = pAccountNode->GetAttrValue(PLATFORM_STRING("ForwardAddress"));

      forward_enabled_ = (pAccountNode->GetAttrValue(PLATFORM_STRING("ForwardEnabled")) == PLATFORM_STRING("1"));
      forward_address_ = pAccountNode->GetAttrValue(PLATFORM_STRING("ForwardAddress"));
      forward_keep_original_ = (pAccountNode->GetAttrValue(PLATFORM_STRING("ForwardKeepOriginal")) == PLATFORM_STRING("1"));

      signature_plain_text_ = pAccountNode->GetAttrValue(PLATFORM_STRING("SignaturePlainText"));
      signature_html_ = pAccountNode->GetAttrValue(PLATFORM_STRING("SignatureHTML"));
      enable_signature_ = (pAccountNode->GetAttrValue(PLATFORM_STRING("EnableSignature")) == PLATFORM_STRING("1"));

      enable_signature_ = pAccountNode->GetAttrValue(PLATFORM_STRING("EnableSignature")) == PLATFORM_STRING("1");
      signature_plain_text_ = pAccountNode->GetAttrValue(PLATFORM_STRING("SignaturePlainText"));
      signature_html_ = pAccountNode->GetAttrValue(PLATFORM_STRING("SignatureHTML"));

      last_logon_time_ = pAccountNode->GetAttrValue(PLATFORM_STRING("LastLogonTime"));

      return true;
   }

   bool
   Account::XMLLoadSubItems(XNode *pAccountNode, int iRestoreOptions)
   {
      // Load 
      std::shared_ptr<HM::FetchAccounts> pFetchAccounts = std::shared_ptr<HM::FetchAccounts>(new HM::FetchAccounts(id_));
      pFetchAccounts->Refresh();
      if (!pFetchAccounts->XMLLoad(pAccountNode, iRestoreOptions))
         return false;

      if (!GetRules()->XMLLoad(pAccountNode, iRestoreOptions))
         return false;

     
      return true;
   }

   bool 
   Account::GetVacationMessageIsOn() const
   {
      return vacation_message_is_on_;

      
   }

   size_t 
   Account::GetEstimatedCachingSize()
   {
      return 1024;
   }

}
