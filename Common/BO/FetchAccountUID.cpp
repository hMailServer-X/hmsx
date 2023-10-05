#include "pch.h"
#include "./FetchAccountUID.h"
#include "../Util/Time.h"

namespace HM
{
   FetchAccountUID::FetchAccountUID (long long iID, long long iAccountID, const String &sUID, const String &sDate) :
      account_id_(iAccountID),
      uid_(sUID),
      date_(sDate)
   {
      SetID(iID);
   }

   FetchAccountUID::FetchAccountUID() :
      account_id_(0)
   {
      SetID(0);
   }

   FetchAccountUID::~FetchAccountUID()
   {

   }

   DateTime
   FetchAccountUID::GetCreationDate() const
   {
      return Time::GetDateFromSystemDate(date_);
   }

   bool 
   FetchAccountUID::XMLStore(XNode *pUIDsNode, int iOptions)
   {  
      XNode *pUIDNode = pUIDsNode->AppendChild(PLATFORM_STRING("UID"));
      
      pUIDNode->AppendAttr(PLATFORM_STRING("UID"), uid_);
      pUIDNode->AppendAttr(PLATFORM_STRING("Date"), date_);

      return true;
   }

   bool
   FetchAccountUID::XMLLoad(XNode *pUIDNode, int iRestoreOptions)
   {
      uid_ = pUIDNode->GetAttrValue(PLATFORM_STRING("UID"));
      date_ = pUIDNode->GetAttrValue(PLATFORM_STRING("Date"));

      return true;
   }

   void 
   FetchAccountUID::SetAccountID(long long accountID)
   {
      account_id_ = accountID;
   }
}