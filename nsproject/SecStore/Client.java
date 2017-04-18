package SecStore;

import java.io.*;
import java.net.*;

public class Client {
    private static Socket conn;
    private static InputStream in;
    private static OutputStream out;

    public static void main(String args[]) throws Exception {
        String hostName = args[0];
        String fileName = args[2];
        int portNumber = Integer.parseInt(args[1]);

        System.out.print("Connecting to Server... ");
        conn = new Socket(hostName, portNumber);
        out = conn.getOutputStream();
        in = conn.getInputStream();
        System.out.println("OK");

        // receive signed certificate
        System.out.print("Authenticating Server... ");
        AP ap = new AP(in);
        out.write(ap.getChallenge());
        //System.out.print("Sent challenge: ");
        //CP.printBytes(ap.getChallenge());

        // check with certificate
        if ( ! ap.verify(in) ) {
            System.out.println("Response invalid! Spoopy!");
            return;
        } else {
            System.out.println("OK. Proceeding.");
        }

        // send file
        System.out.print("Sending file... ");
        CP cp = new CP2(ap.getPublicKey());
        cp.send(fileName, out);
        System.out.println("OK");

        // cleanup
        in.close();
        out.close();
        conn.close();
    }
}
