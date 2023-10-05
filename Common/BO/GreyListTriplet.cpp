#include "pch.h"
#include "GreyListTriplet.h"

namespace HM
{
   GreyListTriplet::GreyListTriplet(void) :
      id_(0),
      passed_count_(0),
      blocked_count_(0)
   {

   }

   GreyListTriplet::~GreyListTriplet(void)
   {
   }

   void 
   GreyListTriplet::SetID(long long iNewID)
   {
      id_ = iNewID;
   }

   long long 
   GreyListTriplet::GetID() const
   {
      return id_;
   }

   void 
   GreyListTriplet::SetCreateTime(const String &sNewVal)
   {
      create_time_ = sNewVal; 
   }

   String
   GreyListTriplet::GetCreateTime() const
   {
      return create_time_;
   }

   void 
   GreyListTriplet::SetBlockEndTime(const String &sNewVal)
   {
      block_end_time_ = sNewVal; 
   }

   String
   GreyListTriplet::GetBlockEndTime() const
   {
      return block_end_time_;
   }

   void 
   GreyListTriplet::SetDeleteTime(const String &sNewVal)
   {
      delete_time_ = sNewVal; 
   }

   String
   GreyListTriplet::GetDeleteTime() const
   {
      return delete_time_;
   }

   void 
   GreyListTriplet::SetIPAddress(IPAddress iNewVal)
   {
      ipaddress_ = iNewVal;
   }
   
   IPAddress 
   GreyListTriplet::GetIPAddress() const
   {
      return ipaddress_;
   }

   void 
   GreyListTriplet::SetRecipientAddress(const String &sNewVal)
   {
      recipient_address_ = sNewVal; 
   }

   String
   GreyListTriplet::GetRecipientAddress() const
   {
      return recipient_address_;
   }

   void 
   GreyListTriplet::SetSenderAddress(const String &sNewVal)
   {
      sender_address_ = sNewVal; 
   }

   String
   GreyListTriplet::GetSenderAddress() const
   {
      return sender_address_;
   }


   void 
   GreyListTriplet::SetPassedCount(int iNewVal)
   {
      passed_count_ = iNewVal;
   }

   int 
   GreyListTriplet::GetPassedCount() const
   {
      return passed_count_;
   }

   void 
   GreyListTriplet::SetBlockedCount(int iNewVal)
   {
      passed_count_ = iNewVal;
   }

   int 
   GreyListTriplet::GetBlockedCount() const
   {
      return passed_count_;
   }

}