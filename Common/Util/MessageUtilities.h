#pragma once

namespace HM
{
   class Message;
   class MimeHeader;
   class IMAPFolder;

   class MessageUtilities
   {
   public:

	   MessageUtilities();
	   virtual ~MessageUtilities();

		static bool MoveToIMAPFolder(std::shared_ptr<Message> pMessage, long long iAccountID, const String &sFolderName, bool bAutoSubscribe, bool bSetByGlobalRule,  long long &iResultAccount, long long &iResultFolder);
      // Moves a message to an IMAP folder. The message should not be saved when this
      // function is called.
      // Returns the ID of the folder the message was moved to.

      static bool RetrieveOriginatingAddress(std::shared_ptr<Message> pMessage, String &hostName, IPAddress &address);
      // Tries to determine the IP address this email originally comes from. This function uses
      // the forwarding relay server list to determine this.

      static bool RetrieveOriginatingAddress(const std::list<String> &receivedHeaders, String &hostName, IPAddress &address);

      static String GetSendersIP(std::shared_ptr<Message> pMessage);

      static bool CopyToIMAPFolder(std::shared_ptr<Message> pMessage, int iDestinationFolderID);
         
   private:

      static void CleanIMAPFolderRuleString(String &sIMAPFolder);
      
      static void RetrieveReceivedIPList_(const std::list<String> &headers, std::list<std::pair<String, IPAddress> > &vecAddresses);

      static std::shared_ptr<MimeHeader> GetMessageHeader_(std::shared_ptr<Message> pMessage);
      // Reads the header for the message and returns it.
   };

   class MessageUtilitiesTester
   {
   public:
      void Test();
   };
}

