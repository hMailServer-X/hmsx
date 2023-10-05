#pragma once

namespace HM
{
   class GUIDCreator  
   {
   public:
	   GUIDCreator();
	   virtual ~GUIDCreator();

      static String GetGUID();
   };

}
