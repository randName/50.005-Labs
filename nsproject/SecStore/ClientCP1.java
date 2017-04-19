package SecStore;

import java.io.*;
import java.net.*;

public class ClientCP1 extends Client {
    private CP1 cp;

    public static void main(String args[]) throws Exception {
        String hostName = args[0];
        String fileName = args[2];
        int portNumber = Integer.parseInt(args[1]);

        System.out.print("Connecting to Server... ");
        ClientCP1 client = new ClientCP1();
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

    @Override
    public void initCP() throws Exception {
        cp = new CP1(ap.getPublicKey());
    }

    @Override
    public void send(String fileName) throws Exception {
        cp.init(out, fileName);
        cp.transfer(new FileInputStream(fileName));
    }
}
