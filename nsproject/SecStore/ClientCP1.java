package SecStore;

public class ClientCP1 extends Client {

    public static void initCP() throws Exception {
        cp = new CP1(ap.getPublicKey());
    }

}
