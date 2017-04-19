package SecStore;

public class ServerCP1 extends Server {

    public static void initCP() throws Exception {
        cp = new CP1(ap.getPrivateKey());
    }

}
