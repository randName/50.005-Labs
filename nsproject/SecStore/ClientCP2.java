package SecStore;

public class ClientCP2 extends Client {

    public static void initCP() throws Exception {
        cp = new CP2(ap.getPublicKey());
    }

}
