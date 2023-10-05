#include "pch.h"
#include "./reinitializator.h"
#include <boost/thread/thread.hpp>

namespace HM
{

   Reinitializator::Reinitializator(void) :
      is_running_(false)
   {
   }

   Reinitializator::~Reinitializator(void)
   {

   }

   void 
   Reinitializator::ReInitialize()
   {
      if (is_running_)
      {
         return;
      }

      std::function<void ()> func = std::bind( &Reinitializator::WorkerFunc, this );

      worker_thread_ = boost::thread(func);
   }

   void
   Reinitializator::WorkerFunc()
   {
      is_running_ = true;

      Application::Instance()->Reinitialize();

      is_running_ = false;

   }
}