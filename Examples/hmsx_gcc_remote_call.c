/* This example shows how a connection to a hMailServer X remote 
 * instance can be done using the GNU GCC C/C/++ Compiler 
 * Please check also the build instructions at the end of file.  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int main(int argc, char *argv[]) {
    
    // Host and port of a hMailServer X remote instannce
    const char *host = "220.240.130.70";
    const char *port = "9999";

    // Initialize OpenSSL
    OPENSSL_init_ssl(0, NULL);
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_SSL_STRINGS | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);

    // Create a SSL context structure
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        fprintf(stderr, "Error creating SSL context\n");
        return 1;
    }

    // Disable selfsigned SSL- certificate checking
    SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

    // Create SSL CTX context
    SSL *ssl = SSL_new(ctx);
    if (!ssl) {
        fprintf(stderr, "Error establishing SSL context\n");
        SSL_CTX_free(ctx);
        return 1;
    }

    // Connect to hMailserver X
    int ret = SSL_set_tlsext_host_name(ssl, host);
    if (ret != 1) {
        fprintf(stderr, "Error at setting Hostnamens\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating the Sockets\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Establish a socket structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    inet_pton(AF_INET, host, &server_addr.sin_addr);

    // Connect with hMailServer X
    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        fprintf(stderr, "Error connecting to hMailServer X\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return 1;
    }

    // Connect with socket
    SSL_set_fd(ssl, sockfd);

    // Run TLS-Handshake 
    ret = SSL_connect(ssl);
    if (ret != 1) {
        fprintf(stderr, "Error at TLS-Handshake\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return 1;
    }

    // Executing a hMailServer X remote command while connected
    const char *request = "get_domains()\n";
    ret = SSL_write(ssl, request, strlen(request));
    if (ret <= 0) {
        fprintf(stderr, "Error at sending request to server\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return 1;
    }

    // Receive response
    char buffer[4096];
    ret = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    if (ret <= 0) {
        fprintf(stderr, "Error receiving the response from hMailServer\n");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockfd);
        return 1;
    }
    buffer[ret] = '\0';
    printf("Response from hMailServer:\n%s", buffer);

    // Close conenction
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockfd);

    return 0;
}

// Build instructions:
// 1) You can use a GNU GCC Compiler or the LLVM Projekt groups CLANG C/C++ Compiler to build this example
// 2) With system defaults you can build it like this:
// 3) GCC with defaults type in:  gcc -o hmsx_gcc_remote_call hmsx_gcc_remote_call.c -lssl -lcrypto 
// 4) OR by specifying a custom OpenSSL build directory:
// 5) export CC=clang
// 6) export CFLAGS="-I/<path_to_openssl>/include"
// 7) $CC -o hmsx_gcc_remote_call hmsx_gcc_remote_call $CFLAGS /<path_to_openssl>/libssl.a /<path_to_openssl>/libcrypto.a 
// 8) Executing the compiled binary by typing ./hmsx_gcc_remote_call
