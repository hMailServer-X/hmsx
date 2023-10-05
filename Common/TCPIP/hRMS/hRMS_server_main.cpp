#include <pch.h>

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <iomanip>
#include <chrono>
#include <locale>
#include "hRMS_server_main.h"
#include "../../BO/Domains.h"
#include "../../Persistence/PersistentDomain.h"
#include "../../Util/StdString.h"

#pragma comment(lib, "ws2_32.lib")

/* Combine two const char* strings  */
const char* CombineStrings(const char* str1, const char* str2) {
   size_t len1 = strlen(str1);
   size_t len2 = strlen(str2);

   char* combinedStr = new char[len1 + len2 + 1]; // +1 für Null-Terminator

   strcpy(combinedStr, str1);
   strcat(combinedStr, str2);

   return combinedStr;
}

std::string WideStringToUTF8(const wchar_t* wideString) {
   int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr);
   std::vector<char> utf8Buffer(utf8Length);
   WideCharToMultiByte(CP_UTF8, 0, wideString, -1, utf8Buffer.data(), utf8Length, nullptr, nullptr);
   return std::string(utf8Buffer.data());
}

/* Determine the path of the hMailServer.exe process */
const char* GetCallingExePath() {
   static char callingExePath[MAX_PATH] = { 0 };

   if (callingExePath[0] == '\0') {
      wchar_t widePath[MAX_PATH];
      DWORD pathLength = GetModuleFileName(NULL, widePath, MAX_PATH);
      if (pathLength == 0) {
         std::cerr << "Fehler beim Abrufen des Pfads der ausführbaren Datei." << std::endl;
         return nullptr;
      }

      // Path to EXE file in Unicode (wide) to buffer
      std::wstring wideCallingExePath(widePath);

      // Dateinamen aus dem Pfad entfernen, um nur das Verzeichnis zu erhalten
      size_t pos = wideCallingExePath.find_last_of(L"\\/");
      wideCallingExePath = wideCallingExePath.substr(0, pos);

      // Unicode (wide) in UTF-8 konvertieren
      int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideCallingExePath.c_str(), -1, NULL, 0, NULL, NULL);
      std::vector<char> utf8Buffer(utf8Length);
      WideCharToMultiByte(CP_UTF8, 0, wideCallingExePath.c_str(), -1, utf8Buffer.data(), utf8Length, NULL, NULL);

      // UTF-8-kodierten Pfad der aufrufenden EXE-Datei im statischen Puffer speichern
      strncpy(callingExePath, utf8Buffer.data(), MAX_PATH);
   }

   return callingExePath;
}

namespace HM
{

#define PORT "9999"

   void initOpenSSL() {
      SSL_load_error_strings();
      OpenSSL_add_ssl_algorithms();
   }

   void cleanupOpenSSL() {
      EVP_cleanup();
   }

   SSL_CTX* createSSLContext() {
      const SSL_METHOD* method;
      SSL_CTX* ctx;

      method = TLS_server_method();

      ctx = SSL_CTX_new(method);
      if (!ctx) {
         std::cerr << "Unable to create SSL context";
         ERR_print_errors_fp(stderr);
         exit(EXIT_FAILURE);
      }

      SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
      SSL_CTX_set_max_proto_version(ctx, TLS1_3_VERSION);

      const char* callingExePath = GetCallingExePath();

      const char* certFile = "/cert.pem";
      const char* certKeyFile = "/key.pem";          
  
      const char* combinedStr1 = CombineStrings(callingExePath, certFile);
      const char* combinedStr2 = CombineStrings(callingExePath, certKeyFile);

      // Include the server certificate and private key
      if (SSL_CTX_use_certificate_file(ctx, combinedStr1, SSL_FILETYPE_PEM) <= 0) {
         ERR_print_errors_fp(stderr);
         exit(EXIT_FAILURE);
      }

      if (SSL_CTX_use_PrivateKey_file(ctx, combinedStr2, SSL_FILETYPE_PEM) <= 0) {
         ERR_print_errors_fp(stderr);
         exit(EXIT_FAILURE);
      }

      return ctx;
   }

   bool handleClientCommand(SSL* ssl, const std::string& cmd) {

      // handle quit command 
      if (cmd.compare(0, 4, "quit") == 0) {
         SSL_write(ssl, QUIT_COMMAND_RECEIVED.c_str(), static_cast<int>(QUIT_COMMAND_RECEIVED.size()));
         return false;  // Return false to signal that the connection should be closed
      }

      /* Get the Date and time from the server  */
      else if (cmd.compare(0, 4, "date") == 0) {

         // Aktuelles Datum und Zeitpunkt holen
         auto now = std::chrono::system_clock::now();
         std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

         // Struktur tm für das lokale Datum erstellen
         std::tm local_time;
         localtime_s(&local_time, &now_time_t);

         // Datum in einem lesbaren Format ausgeben
         char buffer[100];
         strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
         std::cout << "Das aktuelle Datum ist: " << buffer << std::endl;

         std::string serverdate = buffer;
         SSL_write(ssl, serverdate.c_str(), static_cast<int>(serverdate.size()));
      }

      /* Get hMailServer version string */
      else if (cmd.compare(0, 7, "version") == 0) {

         std::string cmd_version = cmd.substr(8);

         // Remove trailing newline character if it exists
         if (!cmd_version.empty() && cmd_version[cmd_version.size() - 1] == '\n') {
            cmd_version.erase(static_cast<std::string::size_type>(cmd_version.size() - 1));
         }
             
         std::wstring hms_version = HM::Application::Instance()->GetVersionNumber();
      
         std::wstring ws(hms_version);
         std::string str(ws.begin(), ws.end());
         cmd_version = str;

         SSL_write(ssl, cmd_version.c_str(), static_cast<int>(cmd_version.size()));
      }

      /* Get hMailServer startup time */      
      else if (cmd.compare(0, 16, "get_startup_time") == 0) {

         std::string cmd_startup = cmd.substr(17);

         // Remove trailing newline character if it exists
         if (!cmd_startup.empty() && cmd_startup[cmd_startup.size() - 1] == '\n') {
            cmd_startup.erase(static_cast<std::string::size_type>(cmd_startup.size() - 1));
         }

         // Get hMailServer start time
         std::wstring hms_startup_time = Application::Instance()->GetStartTime();

         // Convert startup time to std::string 
         std::wstring ws(hms_startup_time);
         std::string str(ws.begin(), ws.end());
         cmd_startup = str;

         // Put std::string into sent buffer
         SSL_write(ssl, cmd_startup.c_str(), static_cast<int>(cmd_startup.size()));
      }

      /* Get hMailServer version architecture */
      else if (cmd.compare(0, 16, "get_version_arch") == 0) {

         std::string cmd_get_version_arch = cmd.substr(17);

         // Remove trailing newline character if it exists
         if (!cmd_get_version_arch.empty() && cmd_get_version_arch[cmd_get_version_arch.size() - 1] == '\n') {
            cmd_get_version_arch.erase(static_cast<std::string::size_type>(cmd_get_version_arch.size() - 1));
         }

         // Get Arch info
         std::wstring hms_startup_time = Application::Instance()->GetVersionArchitecture();

         // Convert startup time to std::string 
         std::wstring ws(hms_startup_time);
         std::string str(ws.begin(), ws.end());
         cmd_get_version_arch = str;

         // Put std::string into sent buffer
         SSL_write(ssl, cmd_get_version_arch.c_str(), static_cast<int>(cmd_get_version_arch.size()));
      }

      /* Get hMailServer Hostname v*/
      else if (cmd.compare(0, 13, "get_host_name") == 0) {

         std::string cmd_get_host_name = cmd.substr(14);

         // Remove trailing newline character if it exists
         if (!cmd_get_host_name.empty() && cmd_get_host_name[cmd_get_host_name.size() - 1] == '\n') {
            cmd_get_host_name.erase(static_cast<std::string::size_type>(cmd_get_host_name.size() - 1));
         }                 

         std::wstring hms_startup_time = Configuration::Instance()->GetHostName();

         // Convert startup time to std::string 
         std::wstring ws(hms_startup_time);
         std::string str(ws.begin(), ws.end());
         cmd_get_host_name = str;

         // Put std::string into sent buffer
         SSL_write(ssl, cmd_get_host_name.c_str(), static_cast<int>(cmd_get_host_name.size()));
      }

      /* Get hMailServer Default Domain */
      else if (cmd.compare(0, 18, "get_default_domain") == 0) {

         std::string cmd_get_default_domain = cmd.substr(19);

         // Remove trailing newline character if it exists
         if (!cmd_get_default_domain.empty() && cmd_get_default_domain[cmd_get_default_domain.size() - 1] == '\n') {
            cmd_get_default_domain.erase(static_cast<std::string::size_type>(cmd_get_default_domain.size() - 1));
         }

         std::wstring hms_startup_time = Configuration::Instance()->GetHostName();

         // Convert startup time to std::string 
         std::wstring ws(hms_startup_time);
         std::string str(ws.begin(), ws.end());
         cmd_get_default_domain = str;

         // Put std::string into sent buffer
         SSL_write(ssl, cmd_get_default_domain.c_str(), static_cast<int>(cmd_get_default_domain.size()));
      }

      // Login to hMailServer
      else if (cmd.compare(0, 12, "authenticate") == 0) {

         std::string cmd_authenticate = cmd.substr(13);
                 
         // Remove trailing newline character if it exists
         if (!cmd_authenticate.empty() && cmd_authenticate[cmd_authenticate.size() - 1] == '\n') {
            cmd_authenticate.erase(static_cast<std::string::size_type>(cmd_authenticate.size() - 1));
         }

           /* Check password */
         if (cmd_authenticate == storedPassword) {
            SSL_write(ssl, PASSWORD_CORRECT.c_str(), static_cast<int>(PASSWORD_CORRECT.size()));
         }
         else {
            SSL_write(ssl, PASSWORD_INCORRECT.c_str(), static_cast<int>(PASSWORD_INCORRECT.size()));
         }
      }


      // Sent Email
      else if (cmd.compare(0, 10, "sent_email") == 0) {

         std::string cmd_email = cmd.substr(11);

         // Remove trailing newline character if it exists
         if (!cmd_email.empty() && cmd_email[cmd_email.size() - 1] == '\n') {
            cmd_email.erase(static_cast<std::string::size_type>(cmd_email.size() - 1));
         }

         std::shared_ptr<Account> foo_;       

         std::string cmd_email_sent = "Email was sent";
            SSL_write(ssl, cmd_email_sent.c_str(), static_cast<int>(cmd_email_sent.size()));
         }


      // Get Domains
      else if (cmd.compare(0, 11, "get_domains") == 0) {

         std::string cmd_domains = cmd.substr(12);

         std::shared_ptr<HM::Domains> objects_;
         objects_ = std::shared_ptr<HM::Domains>(new HM::Domains);
         objects_->Refresh();      
                
         HM::String result;

         for (size_t i = 0; i < objects_->GetCount(); i++) {
            std::shared_ptr<HM::Domain> pPersDomain = objects_->GetItem(i);
            HM::String new_string = pPersDomain->GetName();
            result += new_string +"\n";
         }
         
         // Comversion from wchar_t-Strings in UTF-8
         int utf8_size = WideCharToMultiByte(CP_UTF8, 0, result, -1, nullptr, 0, nullptr, nullptr);
         std::string utf8_str(utf8_size, 0);
         WideCharToMultiByte(CP_UTF8, 0, result, -1, &utf8_str[0], utf8_size, nullptr, nullptr);

         // SSL_write expected const char* as input so use c_str() to cast C++-String into C chars.
         SSL_write(ssl, utf8_str.c_str(), static_cast<int>(utf8_str.size() - 1));


         
      }         

      /* If no command was found, write out this to the client */
      else {
         SSL_write(ssl, UNKNOWN_COMMAND.c_str(), static_cast<int>(UNKNOWN_COMMAND.size()));
      }

      return true;  // Return true to keep the connection open
   }

   void serverLoop(SSL_CTX* ctx) {
      WSADATA wsaData;
      int state = WSAStartup(MAKEWORD(2, 2), &wsaData);
      if (state != 0) {
         std::cerr << "WSAStartup failed with error: " << state;
      }

      addrinfo hints;
      addrinfo* result, * rp;
      ZeroMemory(&hints, sizeof(hints));
      hints.ai_family = AF_UNSPEC;    // Allow IPv4 & IPv6
      hints.ai_socktype = SOCK_STREAM; // TCP
      hints.ai_flags = AI_PASSIVE;     // Use the wildcard IP address

      getaddrinfo("0.0.0.0", PORT, &hints, &result);

      SOCKET listenSocket = INVALID_SOCKET;

      for (rp = result; rp != NULL; rp = rp->ai_next) {
         listenSocket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
         if (listenSocket == INVALID_SOCKET) continue;

         // Set the socket option to reuse the address to avoid "Address already in use" error
         int optval = 1;
         setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));

         if (bind(listenSocket, rp->ai_addr, (int)rp->ai_addrlen) != SOCKET_ERROR) break;  // Success 
         closesocket(listenSocket);
         listenSocket = INVALID_SOCKET;
      }

      freeaddrinfo(result);

      if (listenSocket == INVALID_SOCKET) {
         std::cerr << "Unable to bind socket";
         exit(EXIT_FAILURE);
      }

      listen(listenSocket, SOMAXCONN);
            
      while (true) {
         SOCKET clientSocket = accept(listenSocket, NULL, NULL);

         SSL* ssl = SSL_new(ctx);
         SSL_set_fd(ssl, static_cast<int>(clientSocket));

         if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
         }
         else {
            while (true) {
               char buf[4096];
               int bytes = SSL_read(ssl, buf, sizeof(buf) - 1);
               if (bytes <= 0) break;  // Client closed connection
               buf[bytes] = '\0';

               std::string cmd = buf;
               if (!handleClientCommand(ssl, cmd)) break;  // Break the loop to close the connection if the 'quit' command was received
            }
         }

         SSL_free(ssl);
         closesocket(clientSocket);
      }

      closesocket(listenSocket);
      WSACleanup();
   }

   // Start the hMS Admin server on specified tcp with TLSv1.3 on port 9999

   void InithRMSAdminServer()
   {
      initOpenSSL();
      SSL_CTX* ctx = createSSLContext();
      serverLoop(ctx);
      SSL_CTX_free(ctx);
      cleanupOpenSSL();
   }



}