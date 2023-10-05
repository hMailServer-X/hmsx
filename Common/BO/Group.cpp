#include "pch.h"

#include "Group.h"
#include "GroupMembers.h"
#include "Groups.h"

namespace HM
{
   Group::Group(void)
   {
      
   }

   Group::~Group(void)
   {
   }

   String 
   Group::GetName() const
   {
      return name_;
   }

   void 
   Group::SetName(const String &sName)
   {
      name_ = sName;
   }

   std::shared_ptr<GroupMembers> 
   Group::GetMembers()
   {
      std::shared_ptr<GroupMembers> pGroupMembers = std::shared_ptr<GroupMembers>(new GroupMembers(id_));
      pGroupMembers->Refresh();

      return pGroupMembers;
   }

   bool 
   Group::UserIsMember(long long iAccountID)
   {
      return GetMembers()->UserIsMember(iAccountID);
   }

   bool 
   Group::XMLStore(XNode *pParentNode, int iOptions)
   {
      XNode *pNode = pParentNode->AppendChild(PLATFORM_STRING("Group"));

      pNode->AppendAttr(PLATFORM_STRING("Name"), name_);

      GetMembers()->XMLStore(pNode, iOptions);

      return true;
   }

   bool
   Group::XMLLoad(XNode *pNode, int iRestoreOptions)
   {
      name_ = pNode->GetAttrValue(PLATFORM_STRING("Name"));

      return true;
   }


   bool
   Group::XMLLoadSubItems(XNode *pNode, int iRestoreOptions)
   {
      std::shared_ptr<GroupMembers> pGroupMembers = GetMembers();
      return pGroupMembers->XMLLoad(pNode, iRestoreOptions);
   }
}