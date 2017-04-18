package SecStore;

import javax.crypto.*;
import java.security.*;

public class CP1 extends CP {

    public CP1() throws Exception {
        super();
    }

    public CP1(PrivateKey pk) throws Exception {
        super(pk);
        buffer = new byte[128];
    }

    public CP1(PublicKey pk) throws Exception {
        super(pk);
        buffer = new byte[128];
    }

    private byte[] process(byte[] data) throws Exception {
        return c.doFinal(data);
    }
}
