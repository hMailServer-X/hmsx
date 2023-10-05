#pragma once

namespace HM
{
   class MessageRecipient
   {
   public:
      MessageRecipient();
      ~MessageRecipient(void);

      enum DeliveryResult
      {
         ResultUndefined = 0,
         ResultOK = 1,
         ResultNonFatalError = 2,
         ResultFatalError =3,
         ResultOptionalHandshakeFailed = 4
      };

      void CopyFrom(std::shared_ptr<MessageRecipient> pRecip);

      void SetAddress(const String & sNewVal) {address_ = sNewVal; }
      String GetAddress() const {return address_;}

      void SetOriginalAddress(const String & sNewVal) {original_address_ = sNewVal; }
      String GetOriginalAddress() const {return original_address_;}

      void SetLocalAccountID(long long lNewVal) {local_account_id_ = lNewVal;}
      long long GetLocalAccountID() const{return local_account_id_;}

      void SetMessageID(long long lNewVal) {message_id_ = lNewVal;}
      long long GetMessageID() const {return message_id_;}

      bool GetRequireAuth() const {return requires_authentication_;}
      void SetRequiresAuth(bool bNewVal) {requires_authentication_ = bNewVal; }

      String GetRequiredSender() const {return required_sender_; }
      void SetRequiredSender(const String &sNewVal) {required_sender_ = sNewVal; }

      bool GetIsLocalName() const {return is_local_name_; }
      void SetIsLocalName(bool isLocalName) {is_local_name_ = isLocalName; }

      bool IsEmpty() {return address_.IsEmpty(); }

      // -- BEGIN REMOTE DELIVERY
      DeliveryResult GetDeliveryResult() const {return  result_; }
      void SetDeliveryResult(DeliveryResult newVal) {result_ = newVal; }

      String GetErrorMessage() const {return error_message_;}
      void SetErrorMessage(const String &sNewVal) {error_message_ = sNewVal; }
      // -- END REMOTE DELIVERY

   protected:

      String address_;
      long long local_account_id_;
      long long message_id_;

      bool is_local_name_;

      bool requires_authentication_;
      String required_sender_;
      String original_address_;
      
      // -- BEGIN REMOTE DELIVERY
      DeliveryResult result_;
      String error_message_;
      // -- END REMOTE DELIVERY
   };
}
