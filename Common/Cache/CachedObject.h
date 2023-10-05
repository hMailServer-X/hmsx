#pragma once

namespace HM
{

   template <typename T>
   struct CachedObject
   {
      CachedObject() {}

      CachedObject(std::shared_ptr<T> object) :
         object_(object),
         id_(object->GetID()),
         name_(object->GetName()),
         creation_time_(GetTickCount())
      {
         SetEstimatedSize();
      }

      int
      CachedObject::SecondsOld()
      {
         int iCurrentTime = GetTickCount();

         // Convert from milliseconds to seconds.
         int iAge = (iCurrentTime - creation_time_) / 1000;

         if (iAge < 0)
            iAge = 60 * 60 * 24;

         return iAge;
      }

      void
      CachedObject::SetEstimatedSize()
      {
         estimated_size_ = object_->GetEstimatedCachingSize();
      }

      size_t
      CachedObject::GetEstimatedSize()
      {
         return estimated_size_;
      }

      long long id_;
      std::wstring name_;
      int creation_time_;
      size_t estimated_size_;

      std::shared_ptr<T> object_;
   };

}
