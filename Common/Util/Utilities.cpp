#include "pch.h"

#include "Utilities.h"
#include "File.h"
#include "Time.h"
#include "../Mime/Mime.h"
#include "GUIDCreator.h"

#include "../TCPIP/LocalIPAddresses.h"
#include "../TCPIP/IPAddress.h"
#include "../TCPIP/TCPServer.h"
#include "../TCPIP/DNSResolver.h"
#include "../../SMTP/SMTPConnection.h"
#include "../Util/runtime_variables.h"

namespace HM
{
   String Utilities::cached_win_32computer_name_ = "";
   String Utilities::cached_win_32temp_dir_ = "";

   Utilities::Utilities()
   {
      
   }

   Utilities::~Utilities()
   {

   }

   std::string Utilities::WideStringToAnsi(const std::wstring& wideStr)
   {
       int bufferSize = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
       std::string ansiStr(bufferSize, '\0');
       WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &ansiStr[0], bufferSize, nullptr, nullptr);
       return ansiStr;
   }

   std::string Utilities::GetIPAddress2(const SOCKADDR_IN& addr)
   {
       char ipBuffer[INET_ADDRSTRLEN];
       inet_ntop(AF_INET, &(addr.sin_addr), ipBuffer, INET_ADDRSTRLEN);
       return std::string(ipBuffer);
   }

   String 
   Utilities::GetUniqueTempDirectory()
   {
      return FileUtilities::Combine(IniFileSettings::Instance()->GetTempDirectory(), GUIDCreator::GetGUID());
   }


   String 
   Utilities::ComputerName()
   {

      String sComputerName = Configuration::Instance()->GetHostName();

      if (!sComputerName.IsEmpty())
      {
         // Use the computer name specified by the user.
         return sComputerName;
      }
         

      // No username specified. Fetch local computer name.
      if (!cached_win_32computer_name_.IsEmpty())
         return cached_win_32computer_name_;


      cached_win_32computer_name_ = "LOCALHOST";
      TCHAR pCharBuf[255];
      unsigned long iSize = 255;
      if (::GetComputerName(pCharBuf, &iSize) == TRUE)
         cached_win_32computer_name_ = pCharBuf;
      
      return cached_win_32computer_name_ ;

   }

   std::shared_ptr<MimeHeader>
   Utilities::GetMimeHeader(const BYTE *pByteBuf, size_t iBufSize)
   {
      // First locate end of header in the buffer.
      const char *pBuffer = (const char*) pByteBuf;
      const char *pBufferEndPos = StringParser::Search(pBuffer, iBufSize, "\r\n\r\n");

      std::shared_ptr<MimeHeader> pMimeHeader = std::shared_ptr<MimeHeader>(new MimeHeader);

      if (!pBufferEndPos)
      {
         // The end of header could not be found. Message format error.
         return pMimeHeader;
      }

      // Calculate the length of the header.
      size_t iHeaderSize = pBufferEndPos - pBuffer + 2; // +2 for the last newline.

      // Load the header
      pMimeHeader->Load(pBuffer, iHeaderSize, true);

      return pMimeHeader;

   }

   HM::String SetIniFileDirectory()
   {
       //boost::filesystem::path path = boost::dll::program_location();
       //return(path.string());

       return "";
   }


   // hMailServer bin folder is now passed as hmailserver.exe argument
   String Utilities::GetBinDirectory()
   {
       HM::String IniPath;       
       std::string ppath = readIniPath();              
       IniPath = ppath;
       return IniPath;       
   }

   String Utilities::GetIPAddress(SOCKADDR_IN addr)
   {
      String sRetVal;
      try
      {
         BYTE bt1 = addr.sin_addr.S_un.S_un_b.s_b1;
         BYTE bt2 = addr.sin_addr.S_un.S_un_b.s_b2;
         BYTE bt3 = addr.sin_addr.S_un.S_un_b.s_b3;
         BYTE bt4 = addr.sin_addr.S_un.S_un_b.s_b4 ;
         sRetVal.Format(PLATFORM_STRING("%d.%d.%d.%d"), bt1, bt2, bt3, bt4);
      }
      catch (...)
      {
         sRetVal = "<Unknown>";
         throw;
      }

      return sRetVal;
   }



   String 
   Utilities::GenerateMessageID()
   {
      String sGUID = GUIDCreator::GetGUID();
      sGUID.Replace(PLATFORM_STRING("{"), PLATFORM_STRING(""));
      sGUID.Replace(PLATFORM_STRING("}"), PLATFORM_STRING(""));

      String sRetVal;
      sRetVal.Format(PLATFORM_STRING("<%s@%s>"), sGUID.c_str(), Utilities::ComputerName().c_str());
      
      return sRetVal;
   }

   bool Utilities::IsLocalHost(const String &sHostname)
   {
       SOCKADDR_IN addr;
       addr.sin_family = AF_INET;

       std::wstring wHostname = sHostname; // Konvertiere String zu std::wstring
       addr.sin_addr.s_addr = inet_addr(Utilities::WideStringToAnsi(wHostname).c_str());

       struct hostent* host;

       if (addr.sin_addr.s_addr == INADDR_NONE)
       {
           host = NULL;
           host = gethostbyname(Utilities::WideStringToAnsi(wHostname).c_str());
           if (!host)
               return false;

           memcpy(&addr.sin_addr, host->h_addr_list[0], host->h_length);
       }

       std::string sIPAddress = Utilities::GetIPAddress2(addr);

       IPAddress address;
       address.TryParse(sIPAddress);

       if (LocalIPAddresses::Instance()->IsLocalIPAddress(address))
           return true;
       else
           return false;

   }

   String 
   Utilities::GetRecipientFromReceivedHeader(const String &sReceivedHeader)
   {
      int iLastSemicolon = sReceivedHeader.ReverseFind(PLATFORM_STRING(";"));
      if (iLastSemicolon == -1)
         return "";

      String sFirstPart = sReceivedHeader.Mid(0, iLastSemicolon);

      /*
      sFirstPart now contains the following
      received =  "Received"    ":"            ; one per relay
            ["from" domain]           ; sending host
            ["by"   domain]           ; receiving host
            ["via"  atom]             ; physical path
            *("with" atom)             ; link/mail protocol
            ["id"   msg-id]           ; receiver msg id
            ["for"  addr-spec]        ; initial form
            ";"    date-time         ; time received

      http://cr.yp.to/immhf/envelope.html
      In theory, the value of a Received field is tokenizable.
      In practice, SMTP servers put all sorts of badly formatted information into Received lines. 
      Hence: We only do a quick search
      */

      int iForPos = sFirstPart.ReverseFind(PLATFORM_STRING("for "));
      
      if (iForPos == -1)
         return "";
      
      String sAddressPart = sFirstPart.Mid(iForPos + 4);

      sAddressPart.TrimLeft(PLATFORM_STRING(" \r\n\t"));
      sAddressPart.TrimRight(PLATFORM_STRING(" \r\n\t"));

      sAddressPart.Replace(PLATFORM_STRING("<"), PLATFORM_STRING(""));
      sAddressPart.Replace(PLATFORM_STRING(">"), PLATFORM_STRING(""));
      sAddressPart.Replace(PLATFORM_STRING(" "), PLATFORM_STRING(""));

      if (!StringParser::IsValidEmailAddress(sAddressPart))
         return "";

      return sAddressPart;
   }

   DateTime
   Utilities::GetDateTimeFromReceivedHeader(const String &sReceivedHeader)
   {
      DateTime dtRetValue;

      int iLastSemicolon = sReceivedHeader.ReverseFind(PLATFORM_STRING(";"));
      if (iLastSemicolon == -1)
         return dtRetValue;

      String sDatePart = sReceivedHeader.Mid(iLastSemicolon + 1);

      /*
      sFirstPart now contains the following
      received =  "Received"    ":"            ; one per relay
      ["from" domain]           ; sending host
      ["by"   domain]           ; receiving host
      ["via"  atom]             ; physical path
      *("with" atom)             ; link/mail protocol
      ["id"   msg-id]           ; receiver msg id
      ["for"  addr-spec]        ; initial form
      ";"    date-time         ; time received

      http://cr.yp.to/immhf/envelope.html
      In theory, the value of a Received field is tokenizable.
      In practice, SMTP servers put all sorts of badly formatted information into Received lines. 
      Hence: We only do a quick search
      */

      sDatePart.Trim();

      dtRetValue = Time::GetDateTimeFromMimeHeader(sDatePart);
      
      return dtRetValue;
   }

   bool
   Utilities::IsValidIPAddress(const AnsiString string)
   {
      return IPAddress::IsValid(string);
   }

   HM::String Utilities::SetIniFileDirectory(HM::String path)
   {
       return HM::String();
   }



   String
   Utilities::GetHostNameFromReceivedHeader(const String &sReceivedHeader)
   {
      /*
         sFirstPart now contains the following
         received =  "Received"    ":"            ; one per relay
         ["from" domain]           ; sending host
         ["by"   domain]           ; receiving host
         ["via"  atom]             ; physical path
         *("with" atom)             ; link/mail protocol
         ["id"   msg-id]           ; receiver msg id
         ["for"  addr-spec]        ; initial form
         ";"    date-time         ; time received

         http://cr.yp.to/immhf/envelope.html
         In theory, the value of a Received field is tokenizable.
         In practice, SMTP servers put all sorts of badly formatted information into Received lines. 
         Hence: We only do a quick search
      */

      int iFromPos = sReceivedHeader.Find(PLATFORM_STRING("from "));
      if (iFromPos == -1)
      {
         return "";
      }

      int startPos = iFromPos + 5;
      int endPos = sReceivedHeader.Find(PLATFORM_STRING(" "), startPos );
      if (endPos == -1)
      {
         assert(0);
         return "";
      }

      int length = endPos - startPos;

      if (length == -1)
      {
         assert(0);
         return "";
      }

      String hostName = sReceivedHeader.Mid(startPos, length);

      if (!StringParser::IsValidDomainName(hostName))
      {
         return "";
      }

      return hostName;

   }

   IPAddress
   Utilities::GetIPAddressFromReceivedHeader(const String &sReceivedHeader)
   {
      /*
      sFirstPart now contains the following
      received =  "Received"    ":"            ; one per relay
      ["from" domain]           ; sending host
      ["by"   domain]           ; receiving host
      ["via"  atom]             ; physical path
      *("with" atom)             ; link/mail protocol
      ["id"   msg-id]           ; receiver msg id
      ["for"  addr-spec]        ; initial form
      ";"    date-time         ; time received

      http://cr.yp.to/immhf/envelope.html
      In theory, the value of a Received field is tokenizable.
      In practice, SMTP servers put all sorts of badly formatted information into Received lines. 
      Hence: We only do a quick search
      */

      int iFromPos = sReceivedHeader.Find(PLATFORM_STRING("from "));
      if (iFromPos == -1)
      {
         // Could not locate IP address.
         return IPAddress();
      }

      int iBracketPos = sReceivedHeader.Find(PLATFORM_STRING("["), iFromPos );
      if (iBracketPos == -1)
      {
         // Could not locate IP address.
         return IPAddress();
      }

      int iByPos = sReceivedHeader.Find(PLATFORM_STRING("by "));
      if (iByPos >= 0 && iByPos < iBracketPos)
      {
         // Found from but no bracket.
         return IPAddress();
      }

      int iBracketEndPos = sReceivedHeader.Find(PLATFORM_STRING("]"), iBracketPos);

      int iIPLength = iBracketEndPos - iBracketPos - 1;

      String sIPAddress = sReceivedHeader.Mid(iBracketPos + 1, iIPLength);

      if (!StringParser::IsValidIPAddress(sIPAddress))
      {
         // Could not locate IP address
         assert(0);
         return IPAddress();
      }

      IPAddress address;
      address.TryParse(sIPAddress);

      return address;

   }


   void
   UtilitiesTester::Test()
   {
      TestReceivedHeaderParse_();
      TestComputerName_();

      Utilities utilities;
      if (utilities.IsValidIPAddress("127.0.0.A"))
         throw;

      if (!utilities.IsValidIPAddress("127.0.0"))
         throw;

      if (Configuration::Instance()->IsIPv6Available())
      {
         if (!utilities.IsValidIPAddress("2001:0db8:0000:0000:0000:0000:1428:07ab"))
            throw;

         if (!utilities.IsValidIPAddress("001:0db8:0000:0000:0000::1428:07ab"))
            throw;

         if (!utilities.IsValidIPAddress("2001:db8::1428:7ab"))
            throw;

      }
   }

   void 
   UtilitiesTester::TestReceivedHeaderParse_()
   {
      String sHeader = "from host.edu (host.edu [1.2.3.4]) by mail.host.edu (8.8.5) id 004A21; Tue, Mar 18 1997 14:36:17 -0800 (PST)";
      String sRecipient = Utilities::GetRecipientFromReceivedHeader(sHeader);
      if (sRecipient != PLATFORM_STRING(""))
         throw;

      String hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("host.edu"))
            throw;

      sHeader = "from host.edu (host.edu [1.2.3.4]) by mailhost.host.edu (8.8.5/8.7.2) with ESMTP id LAA20869 for <tmh@host.edu>; Tue, 18 Mar 1997 14:39:24 -0800 (PST)";
      sRecipient = Utilities::GetRecipientFromReceivedHeader(sHeader);
      if (sRecipient != PLATFORM_STRING("tmh@host.edu"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("host.edu"))
         throw;

      sHeader = "Received: from unknown (HELO mail-***.icp-***-irony4.*****.***.au) ([123.123.123.123])\r\n "
                "(envelope-sender <sender@sender.com>)\r\n"
                "by mail.*****.***.au (qmail-ldap-1.03) with SMTP\r\n"
                "for <sender@sender.com>; 20 Oct 2006 04:42:47 -0000\r\n";

      sRecipient = Utilities::GetRecipientFromReceivedHeader(sHeader);
      if (sRecipient != PLATFORM_STRING("sender@sender.com"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("unknown"))
         throw;

      sHeader = "Received: from mail.lysator.liu.se (mail.lysator.liu.se [130.236.254.3]) "
                "by j218.ryd.student.liu.se (Postfix) with ESMTP id D84F433035 "
                "for <email@student.liu.se>; Thu, 14 Mar 2002 21:39:17 +0100 (CET) ";

      sRecipient = Utilities::GetRecipientFromReceivedHeader(sHeader);
      if (sRecipient != PLATFORM_STRING("email@student.liu.se"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("mail.lysator.liu.se"))
         throw;

      sHeader = "Received: from mail.lysator.liu.se (mail.lysator.liu.se [130.236.254.3]) "
         "by j218.ryd.student.liu.se (Postfix) with ESMTP id D84F433035 "
         "for <email@student.liu.se>; Thu, 14 Mar 2002 21:39:17 +0100 (CET) ";

      DateTime dtTime = Utilities::GetDateTimeFromReceivedHeader(sHeader);
      if (dtTime.GetYear() != 2002 || 
          dtTime.GetMonth() != 3 ||
          dtTime.GetDay() != 14 ||
          dtTime.GetHour() != 20 ||
          dtTime.GetMinute() != 39 ||
          dtTime.GetSecond() != 17)
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("mail.lysator.liu.se"))
         throw;

      // Test IP Address parsing
      sHeader = "Received: from mail.lysator.liu.se (mail.lysator.liu.se [130.236.254.3]) "
         "by j218.ryd.student.liu.se (Postfix) with ESMTP id D84F433035 "
         "for <email@student.liu.se>; Thu, 14 Mar 2002 21:39:17 +0100 (CET) ";

      String sIPAddress = Utilities::GetIPAddressFromReceivedHeader(sHeader).ToString();
      if (sIPAddress != PLATFORM_STRING("130.236.254.3"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
         if (hostName != PLATFORM_STRING("mail.lysator.liu.se"))
            throw;
      
      sHeader = "from host.edu (host.edu [1.2.3.4]) by mail.host.edu (8.8.5) id 004A21; Tue, Mar 18 1997 14:36:17 -0800 (PST)";
      sIPAddress = Utilities::GetIPAddressFromReceivedHeader(sHeader).ToString();
      if (sIPAddress != PLATFORM_STRING("1.2.3.4"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("host.edu"))
         throw;

      sHeader = "Received: from unknown (HELO mail-***.icp-***-irony4.*****.***.au) ([123.123.123.125])\r\n "
         "(envelope-sender <sender@sender.com>)\r\n"
         "by mail.*****.***.au (qmail-ldap-1.03) with SMTP\r\n"
         "for <sender@sender.com>; 20 Oct 2006 04:42:47 -0000\r\n";
      sIPAddress = Utilities::GetIPAddressFromReceivedHeader(sHeader).ToString();
      if (sIPAddress != PLATFORM_STRING("123.123.123.125"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("unknown"))
        throw;

      sHeader = "Received: from outbound1.den.paypal.com ([216.113.188.96])\r\n"
                "  by mail.hmailserver.com\r\n"
                "  ; Sun, 13 Dec 2009 09:22:54 +0100\r\n";
      
      sIPAddress = Utilities::GetIPAddressFromReceivedHeader(sHeader).ToString();
      if (sIPAddress != PLATFORM_STRING("216.113.188.96"))
         throw;

      hostName = Utilities::GetHostNameFromReceivedHeader(sHeader);
      if (hostName != PLATFORM_STRING("outbound1.den.paypal.com"))
         throw;
   }



   void 
   UtilitiesTester::TestComputerName_()
   {
      String sComputerName = Utilities::ComputerName();
      Utilities::IsLocalHost(sComputerName); // We can't check the result of this since 
                                             // it's not always possible to say this safely.
   }


}
