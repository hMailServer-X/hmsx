#include "pch.h"
#include "GroupMember.h"

namespace HM
{
   GroupMember::GroupMember(void) :
      group_id_(0),
      account_id_(0)
   {
      
   }

   GroupMember::~GroupMember(void)
   {
   }

   String
   GroupMember::GetName()
   {
      return "N/A";
   }

   long long 
   GroupMember::GetGroupID()
   {
      return group_id_;
   }

   void 
   GroupMember::SetGroupID(long long iNewVal)
   {
      group_id_ = iNewVal;
   }

   long long 
   GroupMember::GetAccountID()
   {
      return account_id_;
   }

   void 
   GroupMember::SetAccountID(long long iNewVal)
   {
      account_id_ = iNewVal; 
   }


   bool 
   GroupMember::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Member"));

      // Taken care of by parent.
      return true;
   }

   bool 
   GroupMember::XMLLoad(XNode *pNode, int iOptions)
   {
      //

      return true;
   }

}