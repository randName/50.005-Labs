package SecStore;

import javax.crypto.*;
import java.security.*;

public class CP1 extends CP {

    public CP1(PrivateKey privatek, PublicKey publick) throws Exception {
        super(privatek, publick);
        buffer = new byte[117];
    }

    public CP1(PrivateKey pk) throws Exception {
        this(pk, null);
    }

    public CP1(PublicKey pk) throws Exception {
        this(null, pk);
    }

    @Override
    public byte[] process(byte[] data) throws Exception {
        return c.doFinal(data);
    }
}
