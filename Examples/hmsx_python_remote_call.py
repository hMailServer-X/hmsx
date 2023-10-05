# This example shows how a connection to a hMailServer X remote 
# instance can be done using the Python Programming Language
# Please check also the build instructions at the end of file.  
# This also works for dynamic web pages in Python.

import socket
import ssl

# Define host and port
host = '220.240.130.70'
port = 9999

# Create the SSL context and disable certificate verification
context = ssl.create_default_context()
context.check_hostname = False
context.verify_mode = ssl.CERT_NONE

# Connect to the server
with socket.create_connection((host, port)) as sock:
    with context.wrap_socket(sock, server_hostname=host) as ssock:
        # Call get_domains() after successful TLS connection
        print("\nhMailServer API call via Python\n")
        print("\nDomains\n")
        ssock.sendall(b'get_domains()\n')
        response = ssock.recv(4096)
        print(response.decode() + "\n")

        # Call get_startup_time() after successful TLS connection
        ssock.sendall(b'get_startup_time()\n')
        response = ssock.recv(4096)
        print(response.decode() + "\n")

# Build instructions: 
# 1) type in: python or python3 hmsx_python_remote_call.py (to execute from terminal)
# 2) To run as Dynamic Web script, just upload it to your webspace and call it in your Browser
