#pragma once

#include "../BO/ScheduledTask.h"

namespace HM
{
   class RemoveExpiredRecords : public ScheduledTask
   {
   public:
      RemoveExpiredRecords(void);
      ~RemoveExpiredRecords(void);

      virtual void DoWork();

   private:
   };
}