#pragma once

namespace HM
{
   class IMAPListLookup
   {
   public:

      IMAPListLookup();
      virtual ~IMAPListLookup();

      static bool IsItemInList(std::vector<String> vecItems, int item);

   private:

   };


}