package SecStore;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

public class Server {
    protected static final Executor exec = Executors.newFixedThreadPool(10);
    protected ServerSocket socket;
    protected AP ap;
    private CP cp;

    public static void main(String[] args) throws Exception {
        int portNumber = Integer.parseInt(args[2]);

        InputStream pkfile = new FileInputStream(args[0]);
        InputStream certfile = new FileInputStream(args[1]);
        System.out.print("Starting server...");
        final Server server = new Server();
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

    public void start(int portNumber) throws Exception {
        socket = new ServerSocket(portNumber);
    }

    public Socket getSocket() throws Exception {
        return socket.accept();
    }

    public void initAP(InputStream pkfile, InputStream certfile) throws Exception {
        ap = new AP(certfile, pkfile);
    }

    public void initCP() throws Exception {
        cp = new CP(ap.getPrivateKey());
    }

    public String receive(InputStream in) throws Exception {
        String fn = cp.init(in);
        cp.transfer(new FileOutputStream(fn));
        return fn;
    }

    protected void handleRequest(Socket conn) {
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
            System.out.print("Receiving file...");
            String fn = this.receive(in);
            System.out.println(" OK. Saved to " + fn);

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
