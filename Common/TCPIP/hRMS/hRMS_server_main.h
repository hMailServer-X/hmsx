#pragma once

namespace HM
{
   void InithRMSAdminServer();

   const std::string PASSWORD_CORRECT = "Password is correct";
   const std::string PASSWORD_INCORRECT = "Password is incorrect";
   const std::string QUIT_COMMAND_RECEIVED = "Quit command received. Closing connection...";
   const std::string UNKNOWN_COMMAND = "Unknown command\n";

   // Move stored password out of the function for a more secure design
   const std::string storedPassword = "test123";


}