#pragma once


namespace HM
{
   class Message;
   
   class SMTPVirusNotifier  
   {
   public:
	   SMTPVirusNotifier();
	   virtual ~SMTPVirusNotifier();

      static void CreateMessageDeletedNotification(const std::shared_ptr<Message> pOriginalMessage, const String &sRecipient);
      
   };

}
