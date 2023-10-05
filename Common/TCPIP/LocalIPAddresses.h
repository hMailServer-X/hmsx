#pragma once

namespace HM
{
   class LocalIPAddresses : public Singleton<LocalIPAddresses>
   {
   public:
	   LocalIPAddresses();
	   virtual ~LocalIPAddresses();

      void LoadIPAddresses();

      bool IsLocalIPAddress(const IPAddress &address);
      bool IsLocalPort(const IPAddress &address, int port);
      bool IsWithinLoopbackRange(const IPAddress &address);

   private:
      
      std::vector<std::pair<IPAddress, int> > local_ports_;
   };


   class LocalIPAddressesTester
   {
   public :
      LocalIPAddressesTester () {};
      ~LocalIPAddressesTester () {};      

      void Test();
   };



}
