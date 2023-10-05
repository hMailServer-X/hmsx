#include "pch.h"
#include "Domain.h"
#include "Accounts.h"
#include "Aliases.h"
#include "DistributionLists.h"
#include "DomainAliases.h"

namespace HM
{
   Domain::Domain() :
      use_plus_addressing_(false),
      active_(0),
      max_message_size_(0),
      plus_addressing_char_("+"),
      anti_spam_options_(1),
      max_size_mb_(0),
      enable_signature_(false),
      signature_method_(SMSetIfNotSpecifiedInAccount),
      add_signatures_to_local_mail_(true),
      add_signatures_to_replies_(false),
      max_no_of_accounts_(0),
      max_no_of_aliases_(0),
      max_no_of_distribution_lists_(0),
      max_account_size_(0),
      limitations_enabled_(0)
   {
      
   }

   Domain::~Domain()
   {

   }

   std::shared_ptr<Accounts>
   Domain::GetAccounts()
   {
      if (!accounts_)
         accounts_ = std::shared_ptr<Accounts>(new Accounts(id_));

      accounts_->Refresh();
      return accounts_;
   }


   std::shared_ptr<DomainAliases>
   Domain::GetDomainAliases()
   {
      if (!domain_aliases_)
         domain_aliases_ = std::shared_ptr<DomainAliases>(new DomainAliases(id_));

      domain_aliases_->Refresh();
      return domain_aliases_;
   }

   std::shared_ptr<Accounts>
   Domain::GetAccounts(long long iAccountID)
   {
      if (!accounts_)
      {
         // Only fetch a specific account and put it in the list. This happens
         // when an API client only has limited access.
         accounts_ = std::shared_ptr<Accounts>(new Accounts(id_, iAccountID));
      }

      accounts_->Refresh();
      return accounts_;
   }

   std::shared_ptr<Aliases>
   Domain::GetAliases()
   {
      if (!aliases_)
         aliases_ = std::shared_ptr<Aliases>(new Aliases(id_));
      
      aliases_->Refresh();

      return aliases_;
   }

   std::shared_ptr<DistributionLists>
   Domain::GetDistributionLists()
   {
      if (!distribution_lists_)
         distribution_lists_ = std::shared_ptr<DistributionLists>(new DistributionLists(id_));

      distribution_lists_->Refresh();

      return distribution_lists_;
   }

   bool 
   Domain::XMLStore(XNode *pParentNode, int iBackupOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Domain"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);
      pNode->AppendAttr(PLATFORM_STRING("Postmaster"), postmaster_);
      pNode->AppendAttr(PLATFORM_STRING("ADDomainName"), addomain_name_);
      pNode->AppendAttr(PLATFORM_STRING("Active"), StringParser::IntToString(active_));
      pNode->AppendAttr(PLATFORM_STRING("MaxMessageSize"), StringParser::IntToString(max_message_size_));
      pNode->AppendAttr(PLATFORM_STRING("MaxSize"), StringParser::IntToString(max_size_mb_));
      pNode->AppendAttr(PLATFORM_STRING("MaxAccountSize"), StringParser::IntToString(max_account_size_));

      pNode->AppendAttr(PLATFORM_STRING("UsePlusAddressing"), use_plus_addressing_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("PlusAddressingChar"), plus_addressing_char_);
      pNode->AppendAttr(PLATFORM_STRING("AntiSpamOptions"), StringParser::IntToString(anti_spam_options_));

      pNode->AppendAttr(PLATFORM_STRING("EnableSignature"), enable_signature_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("SignatureMethod"), StringParser::IntToString(signature_method_));
      pNode->AppendAttr(PLATFORM_STRING("SignaturePlainText"), signature_plain_text_);
      pNode->AppendAttr(PLATFORM_STRING("SignatureHTML"), signature_html_);
      pNode->AppendAttr(PLATFORM_STRING("AddSignaturesToLocalMail"), add_signatures_to_local_mail_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("AddSignaturesToReplies"), add_signatures_to_replies_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));

      pNode->AppendAttr(PLATFORM_STRING("MaxNoOfAccounts"), StringParser::IntToString(max_no_of_accounts_));
      pNode->AppendAttr(PLATFORM_STRING("MaxNoOfAliases"), StringParser::IntToString(max_no_of_aliases_));
      pNode->AppendAttr(PLATFORM_STRING("MaxNoOfLists"), StringParser::IntToString(max_no_of_distribution_lists_));
      pNode->AppendAttr(PLATFORM_STRING("LimitationsEnabled"), StringParser::IntToString(limitations_enabled_));

      pNode->AppendAttr(PLATFORM_STRING("DKIMSelector"), dkim_selector_);
      pNode->AppendAttr(PLATFORM_STRING("DKIMPrivateKeyFile"), dkim_private_key_file_);

      if (!GetDomainAliases()->XMLStore(pNode, iBackupOptions))
         return false;

      // Accounts
      if (!GetAccounts()->XMLStore(pNode, iBackupOptions))
         return false;

      if (!GetAliases()->XMLStore(pNode, iBackupOptions))
         return false;

      if (!GetDistributionLists()->XMLStore(pNode, iBackupOptions))
         return false;

      return true;
   }

   bool 
   Domain::XMLLoad(XNode *pNode, int iRestoreOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      postmaster_ = pNode->GetAttrValue(PLATFORM_STRING("Postmaster"));
      addomain_name_ = pNode->GetAttrValue(PLATFORM_STRING("ADDomainName"));
      active_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("Active")));
      max_message_size_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxMessageSize")));
      max_size_mb_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxSize")));
      max_account_size_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxAccountSize")));

      use_plus_addressing_ = pNode->GetAttrValue(PLATFORM_STRING("UsePlusAddressing")) == PLATFORM_STRING("1");
      plus_addressing_char_ = pNode->GetAttrValue(PLATFORM_STRING("PlusAddressingChar"));
      anti_spam_options_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("AntiSpamOptions")));

      enable_signature_ = pNode->GetAttrValue(PLATFORM_STRING("EnableSignature")) == PLATFORM_STRING("1");
      signature_method_ = (DomainSignatureMethod) _ttoi(pNode->GetAttrValue(PLATFORM_STRING("SignatureMethod")));
      signature_plain_text_ = pNode->GetAttrValue(PLATFORM_STRING("SignaturePlainText"));
      signature_html_ = pNode->GetAttrValue(PLATFORM_STRING("SignatureHTML"));

      add_signatures_to_local_mail_ = pNode->GetAttrValue(PLATFORM_STRING("AddSignaturesToLocalMail")) == PLATFORM_STRING("1");
      add_signatures_to_replies_ = pNode->GetAttrValue(PLATFORM_STRING("AddSignaturesToReplies")) == PLATFORM_STRING("1");

      max_no_of_accounts_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxNoOfAccounts")));
      max_no_of_aliases_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxNoOfAliases")));
      max_no_of_distribution_lists_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MaxNoOfLists")));
      
      limitations_enabled_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("LimitationsEnabled")));

      dkim_selector_ = pNode->GetAttrValue(PLATFORM_STRING("DKIMSelector"));
      dkim_private_key_file_ = pNode->GetAttrValue(PLATFORM_STRING("DKIMPrivateKeyFile"));

      return true;
   }

   bool 
   Domain::XMLLoadSubItems(XNode *pNode, int iRestoreOptions)
   {
      if (!GetDomainAliases()->XMLLoad(pNode, iRestoreOptions))
         return false;

      if (!GetAccounts()->XMLLoad(pNode, iRestoreOptions))
         return false;

      if (!GetAliases()->XMLLoad(pNode, iRestoreOptions))
         return false;

      if (!GetDistributionLists()->XMLLoad(pNode, iRestoreOptions))
         return false;

      return true;
   }

   bool 
   Domain::GetASUseGreyListing() const
   {
      return (anti_spam_options_ & ASUseGreylisting) ? true : false;
   }

   void 
   Domain::SetASUseGreyListing(bool bNewVal)
   {
      if (bNewVal)
         anti_spam_options_ = anti_spam_options_ | ASUseGreylisting;
      else
         anti_spam_options_ = anti_spam_options_ & ~ASUseGreylisting;      

   }

   int
   Domain::GetMaxSizeMB() const
   {
      return max_size_mb_;
   }

   void 
   Domain::SetMaxSizeMB(int iNewVal)
   {
      max_size_mb_ = iNewVal;
   }

   bool  
   Domain::GetEnableSignature() const
   {
      return enable_signature_;
   }

   void 
   Domain::SetEnableSignature(bool bNewVal)
   {
      enable_signature_ = bNewVal;
   }

   Domain::DomainSignatureMethod 
   Domain::GetSignatureMethod() const
   {
      return signature_method_;
   }

   void 
   Domain::SetSignatureMethod(Domain::DomainSignatureMethod eSM)
   {
      signature_method_ = eSM;
   }

   String 
   Domain::GetSignaturePlainText() const
   {
      return signature_plain_text_;
   }

   void 
   Domain::SetSignaturePlainText(const String &sSignature)
   {
      signature_plain_text_ = sSignature;
   }

   String 
   Domain::GetSignatureHTML() const
   {
      return signature_html_;
   }

   void 
   Domain::SetSignatureHTML(const String &sSignature)
   {
      signature_html_ = sSignature;
   }


   bool
   Domain::GetAddSignaturesToReplies() const
   {
      return add_signatures_to_replies_;
   }

   void 
   Domain::SetAddSignaturesToReplies(bool bNewVal)
   {
      add_signatures_to_replies_ = bNewVal;
   }

   bool
   Domain::GetAddSignaturesToLocalMail() const
   {
      return add_signatures_to_local_mail_;
   }

   void 
   Domain::SetAddSignaturesToLocalMail(bool bNewVal)
   {
      add_signatures_to_local_mail_ = bNewVal;
   }

   int
   Domain::GetMaxNoOfAccounts() const
   {
      return max_no_of_accounts_;
   }

   void 
   Domain::SetMaxNoOfAccounts(int iNewVal)
   {
      max_no_of_accounts_ = iNewVal;
   }

   int
   Domain::GetMaxNoOfAliases() const
   {
      return max_no_of_aliases_;
   }

   void 
   Domain::SetMaxNoOfAliases(int iNewVal)
   {
      max_no_of_aliases_ = iNewVal;
   }

   int
   Domain::GetMaxNoOfDistributionLists() const
   {
      return max_no_of_distribution_lists_;
   }

   void 
   Domain::SetMaxNoOfDistributionLists(int iNewVal)
   {
      max_no_of_distribution_lists_ = iNewVal;
   }

   int
   Domain::GetLimitationsEnabled() const
   {
      return limitations_enabled_;
   }

   void
   Domain::SetLimitationsEnabled(int iNewVal)
   {
      limitations_enabled_ = iNewVal;
   }

   bool
   Domain::GetMaxNoOfAccountsEnabled() const
   {
      return (limitations_enabled_ & MaxNoOfAccounts) ? true : false;
   }

   void
   Domain::SetMaxNoOfAccountsEnabled(bool bNewVal)
   {
      if (bNewVal)
         limitations_enabled_ = limitations_enabled_ | MaxNoOfAccounts;
      else
         limitations_enabled_ = limitations_enabled_ & ~MaxNoOfAccounts;
   }

   bool
   Domain::GetMaxNoOfAliasesEnabled() const
   {
      return (limitations_enabled_ & MaxNoOfAliases) ? true : false;
   }

   void 
   Domain::SetMaxNoOfAliasesEnabled(bool bNewVal)
   {
      if (bNewVal)
         limitations_enabled_ = limitations_enabled_ | MaxNoOfAliases;
      else
         limitations_enabled_ = limitations_enabled_ & ~MaxNoOfAliases;

   }

   bool
   Domain::GetMaxNoOfDistributionListsEnabled() const
   {
      return (limitations_enabled_ & MaxNoOfDistributionLists) ? true : false;
   }

   void 
   Domain::SetMaxNoOfDistributionListsEnabled(bool bNewVal)
   {
      if (bNewVal)
         limitations_enabled_ = limitations_enabled_ | MaxNoOfDistributionLists;
      else
         limitations_enabled_ = limitations_enabled_ & ~MaxNoOfDistributionLists;
   }

   int
   Domain::GetMaxAccountSize() const
   {
      return max_account_size_;
   }

   void 
   Domain::SetMaxAccountSize(int iNewVal)
   {
      max_account_size_ = iNewVal;
   }

   bool
   Domain::GetDKIMEnabled() const
   {
      return (anti_spam_options_ & ASDKIMSign) ? true : false;
   }

   void
   Domain::SetDKIMEnabled(bool newValue)
   {
      anti_spam_options_ = newValue ? anti_spam_options_ | ASDKIMSign : anti_spam_options_ & ~ASDKIMSign;
   }

   AnsiString 
   Domain::GetDKIMSelector() const
   {
      return dkim_selector_;
   }

   void 
   Domain::SetDKIMSelector(const String &newValue)
   {
      dkim_selector_ = newValue;
   }

   String 
   Domain::GetDKIMPrivateKeyFile() const
   {
      return dkim_private_key_file_;
   }

   void 
   Domain::SetDKIMPrivateKeyFile(const String &newValue)
   {
      dkim_private_key_file_ = newValue;
   }

   int 
   Domain::GetDKIMHeaderCanonicalizationMethod() const
   {
      if (anti_spam_options_ & ASDKIMSimpleHeader)
         return 1;
      else
         return 2;
   }

   void 
   Domain::SetDKIMHeaderCanonicalizationMethod(int newValue)
   {
      if (newValue == 1)
         anti_spam_options_ |= ASDKIMSimpleHeader;
      else
         anti_spam_options_ &= ~ASDKIMSimpleHeader;
   }


   int 
   Domain::GetDKIMBodyCanonicalizationMethod() const
   {
      if (anti_spam_options_ & ASDKIMSimpleBody)
         return 1;
      else
         return 2;
   }

   void 
   Domain::SetDKIMBodyCanonicalizationMethod(int newValue)
   {
      if (newValue == 1)
         anti_spam_options_ |= ASDKIMSimpleBody;
      else
         anti_spam_options_ &=  ~ASDKIMSimpleBody;
   }

   int 
   Domain::GetDKIMSigningAlgorithm() const
   {
      if (anti_spam_options_ & ASDKIMSHA1)
         return 1;
      else
         return 2;
   }

   void 
   Domain::SetDKIMSigningAlgorithm(int newValue)
   {
      if (newValue == 1)
         anti_spam_options_ |=  ASDKIMSHA1;
      else
         anti_spam_options_ &= ~ASDKIMSHA1;
   }

   size_t 
   Domain::GetEstimatedCachingSize()
   {
      return 1024;
   }
}