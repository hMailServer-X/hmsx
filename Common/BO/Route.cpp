#include "pch.h"
#include "Route.h"

#include "RouteAddresses.h"
#include "../Util/Crypt.h"
#include "../Persistence/PersistentRouteAddress.h"

namespace HM
{
   Route::Route() : 
      connection_security_(CSNone),
      to_all_addresses_(true),
      relayer_requires_authentication_(false),
      treat_recipient_as_local_domain_(false),
      treat_sender_as_local_domain_(false),
      target_smtpport_(0),
      number_of_tries_(0),
      minutes_between_try_(0)
   {
      
   }

   Route::~Route()
   {

   }

   std::shared_ptr<RouteAddresses>
   Route::GetAddresses()
   {
       if (!addresses_)
       {
          assert(id_);
          addresses_ = std::shared_ptr<RouteAddresses>(new RouteAddresses(id_));

          addresses_->Refresh();
       }

       return addresses_;
   }

   bool 
   Route::XMLStore(XNode *pRoutesNode, int iOptions)
   {
      XNode *pNode = pRoutesNode->AppendChild(PLATFORM_STRING("Route"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), domain_name_);
      pNode->AppendAttr(PLATFORM_STRING("Description"), description_);
      pNode->AppendAttr(PLATFORM_STRING("TargetHost"), target_smtphost_);
      pNode->AppendAttr(PLATFORM_STRING("TargetPort"), StringParser::IntToString(target_smtpport_));
      pNode->AppendAttr(PLATFORM_STRING("NumberOfTries"), StringParser::IntToString(number_of_tries_));
      pNode->AppendAttr(PLATFORM_STRING("MinutesBetweenTry"), StringParser::IntToString(minutes_between_try_));
      pNode->AppendAttr(PLATFORM_STRING("ToAllAddresses"), to_all_addresses_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("RequiresAuthentication"), relayer_requires_authentication_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("Username"), relayer_auth_username_);
      pNode->AppendAttr(PLATFORM_STRING("Password"), Crypt::Instance()->EnCrypt(relayer_auth_password_, Crypt::ETBlowFish));
      pNode->AppendAttr(PLATFORM_STRING("TreatRecipientAsLocalDomain"), treat_recipient_as_local_domain_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("TreatSenderAsLocalDomain"), treat_sender_as_local_domain_ ? PLATFORM_STRING("1") : PLATFORM_STRING("0"));
      pNode->AppendAttr(PLATFORM_STRING("ConnectionSecurity"), StringParser::IntToString(connection_security_));

      return GetAddresses()->XMLStore(pNode, iOptions);

   }
   
   bool 
   Route::XMLLoad(XNode *pNode, int iOptions)
   {
      domain_name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));
      description_ = pNode->GetAttrValue(PLATFORM_STRING("Description"));
      target_smtphost_ = pNode->GetAttrValue(PLATFORM_STRING("TargetHost"));
      target_smtpport_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("TargetPort")));
      number_of_tries_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("NumberOfTries")));
      minutes_between_try_ = _ttoi(pNode->GetAttrValue(PLATFORM_STRING("MinutesBetweenTry")));
      to_all_addresses_ = pNode->GetAttrValue(PLATFORM_STRING("ToAllAddresses")) == PLATFORM_STRING("1");
      relayer_requires_authentication_ = pNode->GetAttrValue(PLATFORM_STRING("RequiresAuthentication")) == PLATFORM_STRING("1");
      relayer_auth_username_ = pNode->GetAttrValue(PLATFORM_STRING("Username"));
      relayer_auth_password_ = Crypt::Instance()->DeCrypt(pNode->GetAttrValue(PLATFORM_STRING("Password")), Crypt::ETBlowFish);
      treat_recipient_as_local_domain_ = pNode->GetAttrValue(PLATFORM_STRING("TreatRecipientAsLocalDomain")) == PLATFORM_STRING("1");
      treat_sender_as_local_domain_ = pNode->GetAttrValue(PLATFORM_STRING("TreatSenderAsLocalDomain")) == PLATFORM_STRING("1");

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
   Route::XMLLoadSubItems(XNode *pNode, int iOptions)
   {
      return GetAddresses()->XMLLoad(pNode, iOptions);
   }
}

