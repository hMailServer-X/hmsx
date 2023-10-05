<?php

/* This example shows how a connection to a hMailServer X remote 
 * instance can be done using the PHP Programming language
 * Please check also the build instructions at the end of file.  
 * This also works for termial scripts and dynamic web pages
 */


$host = '220.240.130.70';
$port = 9999;
$timeout = 30;

$context = stream_context_create(
    array('ssl' => array(
        'verify_peer' => false,
        'verify_peer_name' => false,
        'allow_self_signed' => true,
        'crypto_method' => STREAM_CRYPTO_METHOD_TLSv1_3_CLIENT
    ))
);

if ($socket = stream_socket_client(
        'ssl://'.$host.':'.$port,
        $errno,
        $errstr,
        $timeout,
        STREAM_CLIENT_CONNECT,
        $context)
) {
	
	echo "<strong> hMailServer X - API calls - via PHP <br /></strong>";
	
	echo "<strong> <br />Domains</strong>";
    fwrite($socket, "get_domains()\n");
    echo "<strong> <br />" . fread($socket,8192) . "<br /> </strong>";
     
     
    echo "<strong> <br />Startuptime<br /> </strong>";
    fwrite($socket, "get_startup_time()\n");
    echo "<strong>" . fread($socket,8192) . "<br /> </strong>";
    
    fclose($socket);
} else {
	echo "ERROR: $errno - $errstr\n";
}

// Build instructions: 
// 1) type in: php hmsx_php_remote_call.php (to execute from terminal)
// 2) To run as Dynamic Web script, just upload it to your webspace and call it in your Browser

?>



