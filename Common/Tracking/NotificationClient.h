#pragma once

namespace HM
{
   class ChangeNotification;

   class NotificationClient
   {
   public:
      NotificationClient();

      virtual void OnNotification(std::shared_ptr<ChangeNotification> notification) = 0;
   };
}
