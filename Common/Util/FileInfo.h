#pragma once

#include "VariantDateTime.h"

namespace HM
{
   

   class FileInfo
   {
   public:
	   FileInfo(const String &name, const DateTime &created);
      FileInfo();

      String GetName() {return name_;}
      DateTime GetCreateTime() {return created_;}

   private:
      
      String name_;
      DateTime created_;
   };

}
