#pragma once

namespace HM
{

   class RuleResult
   {
   public:
      RuleResult(void);
      ~RuleResult(void);

      String GetMoveToFolder() const {return move_to_folder_;}
      void SetMoveToFolder(const String &sIMAPFolderName) {move_to_folder_ = sIMAPFolderName;}
      
      String GetDeleteRuleName() const {return delete_rule_name_;}
      void SetDeleteRuleName(const String &sDeleteRuleName) {delete_rule_name_ = sDeleteRuleName;}

      long long GetSendUsingRoute() const {return send_using_route_;}
      void SetSendUsingRoute(long long iRuleID) {send_using_route_ = iRuleID; }

      bool GetDeleteEmail() const {return delete_email_;}
      void SetDeleteEmail(bool bNewVal) {delete_email_ = bNewVal; }

      String GetBindToAddress() const {return bind_to_address_;}
      void SetBindToAddress(const String &sAddress) {bind_to_address_ = sAddress;}

   private:

      String move_to_folder_;
      long long send_using_route_;
      
      bool delete_email_;
      String delete_rule_name_;

      String bind_to_address_;

   };
}