package SecStore;

import java.io.*;
import java.net.*;

public class ServerCP1 extends Server {
    private CP1 cp;

    public static void main(String[] args) throws Exception {
        int portNumber = Integer.parseInt(args[2]);

        InputStream pkfile = new FileInputStream(args[0]);
        InputStream certfile = new FileInputStream(args[1]);
        System.out.print("Starting server...");
        ServerCP1 server = new ServerCP1();
        server.initAP(pkfile, certfile);
        server.initCP();
        server.start(portNumber);
        System.out.println(" OK");
        while (true) {
            final Socket connection = server.getSocket();
            exec.execute(new Runnable() {
                public void run() { server.handleRequest(connection); }
            });
        }
    }

    @Override
    public void initCP() throws Exception {
        cp = new CP1(ap.getPrivateKey());
    }

    @Override
    public void transfer(InputStream in) throws Exception {
        String fn = cp.init(in);
        System.out.print("Receiving " + fn + " ...");
        cp.transfer(new FileOutputStream(fn));
        System.out.print(" OK");
    }
}
