#pragma once

namespace HM
{
   class MimeTester
   {
   public:
      MimeTester(void);
      ~MimeTester(void);

      bool TestFolder(const String &sFolderName);
      void TestFile(const String &sFilename);
	  void TestLoadFile(const String &sFilename);
   };
}