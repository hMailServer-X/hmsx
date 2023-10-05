# This example shows how a connection to a hMailServer X remote 
# instance can be done using the Perl Programming language
# Please check also the build instructions at the end of file.  

use IO::Socket::SSL;

# Define host and port
my $host = '220.240.130.70';
my $port = 9999;

# Create the SSL context and disable certificate verification
my $ssl_options = {
    SSL_verify_mode => IO::Socket::SSL::SSL_VERIFY_NONE,
    SSL_check_hostname => 0,
};

# Connect to the server
my $sock = IO::Socket::SSL->new(
    PeerAddr => $host,
    PeerPort => $port,
    %$ssl_options,
) or die "Failed to connect: $SSL_ERROR";

# Call get_domains() after successful TLS connection
$sock->print("get_domains()\n");
my $response = <$sock>;
print $response . "\n";

# Call get_startup_time() after successful TLS connection
$sock->print("get_startup_time()\n");
$response = <$sock>;
print $response . "\n";

# Build instructions
# 1) Install Perl SSL/TLS module if necessary  by running the command: cpanm IO::Socket::SSL
# 2) On Windows: SET PATH=C:\openssl_builds\msvc\openssl;%PATH% (required for Perl to find the OpenSSL DLL's)
# 3) Set script file permissions by typing: chmod +x hmsx_perl_remote_call.pl
# 4) Execute the Perl script by typing: perl hmsx_perl_remote_call.pl
