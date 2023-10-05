#include "pch.h"
#include "./task.h"
#include <boost/thread/thread.hpp>

namespace HM
{
   Task::Task(const String &name) :
      name_ (name)
   {

   }

   Task::~Task(void)
   {

   }

   void
   Task::Run()
   {
      try
      {
         DoWork();
      }
      catch (boost::thread_interrupted const&)
      {
         boost::this_thread::disable_interruption disabled;
         return;
      }
   }
}