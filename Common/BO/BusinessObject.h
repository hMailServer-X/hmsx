#pragma once

namespace HM
{
   template <class T>
   class BusinessObject
   {
   public:
      BusinessObject<T>::BusinessObject();
      virtual ~BusinessObject<T>() {};

		long long GetID() const;
		void SetID(long long iNewVal);

   protected:

     long long id_;
   };

   template <class T>
   BusinessObject<T>::BusinessObject()
   {
      id_ = 0;
   }

   template <class T>
   long long BusinessObject<T>::GetID() const
   {
      return id_;
   }

   template <class T> 
   void BusinessObject<T>::SetID(long long iNewID)
   {
      id_ = iNewID;
   }  

}  