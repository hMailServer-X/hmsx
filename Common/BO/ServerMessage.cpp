#include "pch.h"
#include "ServerMessage.h"

namespace HM
{
   ServerMessage::ServerMessage(void)
   {

   }

   ServerMessage::~ServerMessage(void)
   {
   }

   bool 
   ServerMessage::XMLStore(XNode *pParentNode)
   {

      return true;
   }

   bool 
   ServerMessage::XMLLoad(XNode *pNode)
   {

      return true;
   }
}