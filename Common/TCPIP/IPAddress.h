#pragma once

#include <boost/asio.hpp> 

namespace HM
{

   class IPAddress
   {
   public:
      IPAddress(void);
      ~IPAddress(void);
      
      IPAddress(boost::asio::ip::address address);
      
      IPAddress(long long address1, long long address2);
      IPAddress(long long address1);

      bool operator==(const IPAddress &other);
      bool operator!=(const IPAddress &other);
      bool operator>(const IPAddress &other);
      bool operator<(const IPAddress &other);

      bool TryParse(const AnsiString &string);
      bool TryParse(const AnsiString &string, bool reportOnFail);

      bool IsAny() const;

      enum Type
      {
         Unknown = 0,
         IPV4 = 1,
         IPV6 = 2
      };

      AnsiString ToString() const;
      AnsiString ToLongString() const;

      
      Type GetType() const;

      unsigned long long GetAddress1() const;
      unsigned long long GetAddress2() const;

      boost::asio::ip::address GetAddress() const {return address_; }     


      bool WithinRange(const IPAddress &lower, const IPAddress &upper) const;

      static bool IsValid(const AnsiString &address);

   private:

      void SetIPV4Address_(long long address1);
      void SetIPV6Address_(long long address1, long long address2);

      boost::asio::ip::address address_;     

   };
}