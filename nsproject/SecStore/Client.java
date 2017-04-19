package SecStore;

import java.io.*;
import java.net.*;

public class Client {
    protected Socket conn;
    protected InputStream in;
    protected OutputStream out;
    protected AP ap;

    public static void main(String args[]) throws Exception {
        String hostName = args[0];
        String fileName = args[2];
        int portNumber = Integer.parseInt(args[1]);

        System.out.print("Connecting to Server... ");
        Client client = new Client();
        client.connect(hostName, portNumber);
        System.out.println("OK");

        System.out.print("Authenticating Server... ");
        if( ! client.authenticate() ) {
            System.out.println("Response invalid! Spoopy!");
            return;
        } else {
            System.out.println("OK. Proceeding.");
        }

        // send file
        System.out.print("Sending file...");
        long startTime = System.currentTimeMillis();
        client.initCP();
        client.send(fileName);
        long endTime = System.currentTimeMillis();
        System.out.println(" OK. Time taken: " + (endTime - startTime) + "ms");

        client.close();
    }

    public void connect(String hostName, int portNumber) throws Exception {
        conn = new Socket(hostName, portNumber);
        out = conn.getOutputStream();
        in = conn.getInputStream();
    }

    public void close() throws Exception {
        in.close();
        out.close();
        conn.close();
    }

    public boolean authenticate() throws Exception {
        // receive signed certificate
        ap = new AP(in);
        out.write(ap.getChallenge());
        //System.out.print("Challenge: ");
        //AP.ppbytes(ap.getChallenge());
        // check with certificate
        return ap.verify(in);
    }

    public void initCP() throws Exception {
    }

    public void send(String fileName) throws Exception {
    }
}
