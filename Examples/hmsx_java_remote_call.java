/* This example shows how a connection to a hMailServer X 
 * can be done using the ORACLE Java JDK 21 Java Compiler
 * Please check the build instructions at the end of file.  
 */

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import javax.net.ssl.*;

public class hmsx_api_call_via_java {
    public static void main(String[] args) {
        String host = "220.240.130.70";
        int port = 9999;

        try {
            // Create SSL socket factory with a custom TrustManager
            SSLContext sslContext = SSLContext.getInstance("TLS");
            sslContext.init(null, getTrustAllCertsManager(), new java.security.SecureRandom());
            SSLSocketFactory sslSocketFactory = sslContext.getSocketFactory();

            // Create the SSL socket
            SSLSocket sslSocket = (SSLSocket) sslSocketFactory.createSocket(host, port);

            // Get the input and output streams
            InputStream in = sslSocket.getInputStream();
            OutputStream out = sslSocket.getOutputStream();

            // Call get_domains() after successful TLS connection
            out.write("get_domains()\n".getBytes());
            byte[] response = new byte[4096];
            int bytesRead = in.read(response);
            System.out.println(new String(response, 0, bytesRead));

            // Call get_startup_time() after successful TLS connection
            out.write("get_startup_time()\n".getBytes());
            bytesRead = in.read(response);
            System.out.println(new String(response, 0, bytesRead));

            // Close the SSL socket
            sslSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static TrustManager[] getTrustAllCertsManager() {
        TrustManager[] trustAllCerts = new TrustManager[]{
                new X509TrustManager() {
                    public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                        return null;
                    }

                    public void checkClientTrusted(
                            java.security.cert.X509Certificate[] certs, String authType) {
                    }

                    public void checkServerTrusted(
                            java.security.cert.X509Certificate[] certs, String authType) {
                    }
                }
        };
        return trustAllCerts;
    }
}

// Compile hmsx_java_remote_call.java
// Execute by typing: java hmsx_java_remote_call
