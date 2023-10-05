#define MAXKEYBYTES 	56		// 448 bits max
#define NPASS           16		// SBox passes

#define DWORD  		unsigned long
#define WORD  		unsigned short
#define BYTE  		unsigned char

namespace HM
{
   class BlowFishEncryptor
   {
   private:
	   DWORD 		* PArray ;
	   DWORD		(* SBoxes)[256];
	   void 		Blowfish_encipher (DWORD *xl, DWORD *xr) ;
	   void 		Blowfish_decipher (DWORD *xl, DWORD *xr) ;

      String ToHex_(BYTE *Buf, int iBufLen);
      int ToByteArray_(const String &sHex, BYTE *OutArray);

   public:
		BlowFishEncryptor () ;
		~BlowFishEncryptor () ;

      String EncryptToString(const String &sUnEncrypted);
      String DecryptFromString(const String &sEncrypted);

	   void 		Initialize (BYTE key[], int keybytes) ;
	   DWORD		GetOutputLength (DWORD lInputLong) ;
	   DWORD		Encode (BYTE * pInput, BYTE * pOutput, DWORD lSize) ;
	   void		Decode (BYTE * pInput, BYTE * pOutput, DWORD lSize) ;

   } ;

   class BlowFishEncryptorTester
   {
   public :
      BlowFishEncryptorTester () {};
      ~BlowFishEncryptorTester () {};      
      
      void Test();
   };

   // choose a byte order for your hardware
   #define ORDER_DCBA	// chosing Intel in this case

   #ifdef ORDER_DCBA  	// DCBA - little endian - intel
	   union aword {
	     DWORD dword;
	     BYTE byte [4];
	     struct {
	       unsigned int byte3:8;
	       unsigned int byte2:8;
	       unsigned int byte1:8;
	       unsigned int byte0:8;
	     } w;
	   };
   #endif

   #ifdef ORDER_ABCD  	// ABCD - big endian - motorola
	   union aword {
	     DWORD dword;
	     BYTE byte [4];
	     struct {
	       unsigned int byte0:8;
	       unsigned int byte1:8;
	       unsigned int byte2:8;
	       unsigned int byte3:8;
	     } w;
	   };
   #endif

   #ifdef ORDER_BADC  	// BADC - vax
	   union aword {
	     DWORD dword;
	     BYTE byte [4];
	     struct {
	       unsigned int byte1:8;
	       unsigned int byte0:8;
	       unsigned int byte3:8;
	       unsigned int byte2:8;
	     } w;
   };
   #endif

}
