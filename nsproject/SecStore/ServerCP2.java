package SecStore;

public class ServerCP2 extends Server {

    public static void initCP() throws Exception {
        cp = new CP2(ap.getPrivateKey());
    }

}
