// This example shows how a connection to a hMailServer X remote 
// instance can be done using the Freepascal Compiler FPC
// Please check also the build instructions at the end of file.  



program hmsx_freepascal_remote_call;

{$mode objfpc}{$H+}

uses
  Classes, SysUtils, sockets, openssl;

var
  host: string;
  port: string;
  context: PSSL_CTX;
  ssl: PSSL;
  sock: cint;
  ssock: PSSL;
  response: string;

begin
  // Define host and port
  host := '220.240.130.70';
  port := '9999';

  // Initialize OpenSSL library
  SSL_library_init;
  SSL_load_error_strings;
  ERR_load_BIO_strings;
  OpenSSL_add_all_algorithms;

  // Create SSL context and disable certificate verification
  context := SSL_CTX_new(SSLv23_client_method);
  SSL_CTX_set_verify(context, SSL_VERIFY_NONE, nil);
  SSL_CTX_set_options(context, SSL_OP_NO_SSLv2 or SSL_OP_NO_SSLv3);

  // Connect to the server
  sock := fpsocket(PF_INET, SOCK_STREAM, 0);
  if sock = -1 then
  begin
    Writeln('Error creating socket');
    Exit;
  end;

  with sockaddr_in do
  begin
    sin_family := AF_INET;
    sin_port := htons(StrToInt(port));
    sin_addr.s_addr := inet_addr(PChar(host));
  end;

  if cint(connect(sock, PSockAddr(@sockaddr_in), sizeof(sockaddr_in))) = -1 then
  begin
    Writeln('Error connecting to server');
    Exit;
  end;

  ssl := SSL_new(context);
  SSL_set_fd(ssl, sock);

  if SSL_connect(ssl) <= 0 then
  begin
    Writeln('Error establishing TLS/SSL connection');
    Exit;
  end;

  // Call get_domains() after successful TLS connection
  Writeln('hMailServer API call via Free Pascal');
  Writeln('Domains');

  if SSL_write(ssl, 'get_domains()' + LineEnding, Length('get_domains()' + LineEnding)) <= 0 then
  begin
    Writeln('Error sending request to server');
    Exit;
  end;

  SetLength(response, 4096);
  if SSL_read(ssl, PChar(response), Length(response)) <= 0 then
  begin
    Writeln('Error receiving response from server');
    Exit;
  end;

  SetLength(response, StrLen(PChar(response)));
  Writeln(response);

  // Call get_startup_time() after successful TLS connection
  if SSL_write(ssl, 'get_startup_time()' + LineEnding, Length('get_startup_time()' + LineEnding)) <= 0 then
  begin
    Writeln('Error sending request to server');
    Exit;
  end;

  SetLength(response, 4096);
  if SSL_read(ssl, PChar(response), Length(response)) <= 0 then
  begin
    Writeln('Error receiving response from server');
    Exit;
  end;

  SetLength(response, StrLen(PChar(response)));
  Writeln(response);

  // Cleanup and close the connection
  SSL_shutdown(ssl);
  SSL_free(ssl);
  SSL_CTX_free(context);
  close(sock);
end.

 
 // Build: 
 // fpc hmsx_freepascal_remote_call.pas
 
