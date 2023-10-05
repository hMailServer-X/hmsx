#pragma once

#include "../Common/BO/ScheduledTask.h"

namespace HM
{
   class GreyListCleanerTask : public ScheduledTask
   {
   public:
      GreyListCleanerTask(void);
      ~GreyListCleanerTask(void);

      virtual void DoWork();
   private:
   };
}