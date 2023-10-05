/* This example shows how a connection to a hMailServer X remote 
 * instance can be done using the GNU MingGW GCC C/C/++ Compiler 
 * Please check also the build instructions at the end of file.  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // For Windows Sockets
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(int argc, char *argv[]) {
    
    // Host and port of a hMailServer X remote instance
    const char *host = "220.240.130.70";
    const char *port = "9999";

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Create a SSL context structure
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        fprintf(stderr, "Error creating SSL context\n");
        return 1;
    }

    // Disable self-signed SSL certificate checking (not recommended for production)
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

    // Create SSL CTX context
    SSL *ssl = SSL_new(ctx);
    if (!ssl) {
        fprintf(stderr, "Error establishing SSL context\n");
        SSL_CTX_free(ctx);
        return 1;
    }

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Error initializing Winsock\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Connect to hMailServer X
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        fprintf(stderr, "Error creating the socket\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        WSACleanup();
        return 1;
    }

    // Establish a socket structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr(host);

    // Connect with hMailServer X
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "Error connecting to hMailServer X\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Connect with socket
    SSL_set_fd(ssl, sockfd);

    // Run TLS-Handshake 
    if (SSL_connect(ssl) != 1) {
        fprintf(stderr, "Error at TLS handshake\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Executing a hMailServer X remote command while connected
    const char *request = "get_domains()\n";
    if (SSL_write(ssl, request, strlen(request)) <= 0) {
        fprintf(stderr, "Error at sending request to server\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Receive response
    char buffer[4096];
    int ret = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    if (ret <= 0) {
        fprintf(stderr, "Error receiving the response from hMailServer\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    buffer[ret] = '\0';
    printf("Response from hMailServer:\n%s", buffer);

    // Close connection
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
