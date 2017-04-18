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
        AP ap = new AP(in);
        //System.out.print("Challenge: ");
        //AP.ppbytes(ap.getChallenge());
        System.out.print("Authenticating Server... ");
        out.write(ap.getChallenge());

        // check with certificate
        if ( ! ap.verify(in) ) {
            System.out.println("Response invalid! Spoopy!");
            return;
        } else {
            System.out.println("OK. Proceeding.");
        }

        // send file
        System.out.print("Sending file...");
        CP cp = new CP2(ap.getPublicKey());
        cp.init(out, fileName);
        long startTime = System.currentTimeMillis();
        cp.transfer(new FileInputStream(fileName));
        long endTime = System.currentTimeMillis();
        System.out.println(" OK. Time taken: " + (endTime - startTime) + "ms");

        // cleanup
        in.close();
        out.close();
        conn.close();
    }
}
