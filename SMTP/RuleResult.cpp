#include "pch.h"
#include "./RuleResult.h"

namespace HM
{ 
   RuleResult::RuleResult(void) :
      send_using_route_(0),
      delete_email_(false)
   {
   }

   RuleResult::~RuleResult(void)
   {
   }

}