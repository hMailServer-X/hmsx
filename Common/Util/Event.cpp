#include "pch.h"
#include "Event.h"

namespace HM
{
   Event::Event(void) :
      is_set_(false)
   {

   }

   Event::~Event(void)
   {
      
   }

   void 
   Event::Wait()
   {
      boost::mutex::scoped_lock lock(mutex_);

      if (!is_set_)
         set_condition_.wait(lock);

      is_set_ = false;
   }

   void 
   Event::WaitFor(boost::chrono::milliseconds milliseconds)
   {
      boost::mutex::scoped_lock lock(mutex_);

      if (!is_set_)
      {
         // result will be false if there's a timeout.
         set_condition_.wait_for(lock, milliseconds);
      }
     
      is_set_ = false;
   }

   void 
   Event::Set()
   {  
      boost::mutex::scoped_lock lock(mutex_);
      is_set_ = true;
      set_condition_.notify_one();
   }


}