// This example shows how a connection to a hMailServer X remote instance 
// can be done using the  Javascript within a Node JS environment. This also 
// works for dynamic web pages made with Node vanilla or for example Express JS
// Please check also the build instructions at the end of file. JS / Express JS etc.

const net = require('net');
const tls = require('tls');

// Define host and port
const host = '220.240.130.70';
const port = 9999;

// Create the SSL context and allow all certificates
const context = tls.createSecureContext({
    rejectUnauthorized: false,
});

// Connect to the server
const socket = net.createConnection(port, host, () => {
    const options = {
        socket,
        secureContext: context,
        servername: host,
        checkServerIdentity: () => undefined, // Disable server identity check
    };

    const ssock = tls.connect(options, () => {
        // Call get_domains() after successful TLS connection
        console.log("\nhMailServer API call via Node.js\n");
        console.log("\nDomains\n");
        ssock.write('get_domains()\n');

        ssock.on('data', (data) => {
            console.log(data.toString() + "\n");
        });

        // Call get_startup_time() after successful TLS connection
        ssock.write('get_startup_time()\n');
    });
});

socket.on('error', (err) => {
    console.error('Error:', err);
});

socket.on('close', () => {
    console.log('Connection closed.');
});


// Build instructions:
// Open a Windows Command prompt or Linux/Unix/MacOS Shell
// 1) Install dependencies: npm install net tls
// 2) Set Environment variable: set NODE_TLS_REJECT_UNAUTHORIZED=0 (windows) or export NODE_TLS_REJECT_UNAUTHORIZED=0 on Linux/Unix/MacOS
// 3) Run the script by typing: node hmsx_nodejs_remote_call.js
