#include "pch.h"
#include "ScheduledTask.h"

namespace HM
{
   ScheduledTask::ScheduledTask(void) :
      Task("ScheduledTask"),
      minutes_between_run_(0),
      reoccurance_(RunOnce)
   {

   }

   ScheduledTask::~ScheduledTask(void)
   {
   }

   int
   ScheduledTask::GetMinutesBetweenRun() const
   {
      return minutes_between_run_;
   }

   void 
   ScheduledTask::SetMinutesBetweenRun(int iNewVal)
   {
      minutes_between_run_ = iNewVal;

      SetNextRunTime();
   }

   ScheduledTask::Reoccurance 
   ScheduledTask::GetReoccurance() const
   {
      return reoccurance_;
   }

   void 
   ScheduledTask::SetReoccurance(Reoccurance ro)
   {
      reoccurance_ = ro;
   }

   DateTime 
   ScheduledTask::GetNextRunTime() const
   {
      return next_run_time_;

   }

   void 
   ScheduledTask::SetNextRunTime()
   {
      DateTime dtNow = DateTime::GetCurrentTime();
      
      DateTimeSpan dts;
      dts.SetDateTimeSpan(0,0, minutes_between_run_, 0);

      next_run_time_ = dtNow + dts;
   }

}