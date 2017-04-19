package SecStore;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class Server {
    private static final Executor exec = Executors.newFixedThreadPool(10);
    protected static CP cp;
    protected static AP ap;
    
    public static void main(String[] args) throws Exception {
        int portNumber = Integer.parseInt(args[2]);

        InputStream pkfile = new FileInputStream(args[0]);
        InputStream certfile = new FileInputStream(args[1]);
        System.out.print("Starting server...");
        ap = new AP(certfile, pkfile);
        initCP();
        ServerSocket socket = new ServerSocket(portNumber);
        System.out.println(" OK");
        while (true) {
            final Socket connection = socket.accept();
            exec.execute(new Runnable() {
                public void run() { handleRequest(connection); }
            });
        }
    }

    private static void initCP() throws Exception {
        cp = new CP(ap.getPrivateKey());
    }

    private static void handleRequest(Socket conn) {
        final byte[] challenge = new byte[16];

        try {
            InputStream in = conn.getInputStream();
            OutputStream out = conn.getOutputStream();

            // send signed certificate
            out.write(ap.getCertificate());

            // authentication challenge
            in.read(challenge);
            //System.out.print("Received challenge: ");
            //AP.ppbytes(challenge);
            out.write(ap.respond(challenge));

            // receive file
            String fn = cp.init(in);
            System.out.print("Receiving " + fn + " ...");
            cp.transfer(new FileOutputStream(fn));
            System.out.println(" OK");

            // cleanup
            in.close();
            out.close();
            conn.close();
        } catch (Exception e) {
            //System.out.println(e);
            e.printStackTrace(new PrintStream(System.out));
            return;
        }
    }
}
