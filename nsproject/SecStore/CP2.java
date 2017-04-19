package SecStore;

import java.io.*;
import javax.crypto.*;
import java.security.*;
import javax.crypto.spec.SecretKeySpec;

public class CP2 extends CP {
    private static Cipher s;

    public CP2(PrivateKey privatek, PublicKey publick) throws Exception {
        super(privatek, publick);
        s = Cipher.getInstance("AES/ECB/PKCS5Padding");
    }

    public CP2(PrivateKey pk) throws Exception {
        this(pk, null);
    }

    public CP2(PublicKey pk) throws Exception {
        this(null, pk);
    }

    @Override
    public void init(OutputStream outs, String fn) throws Exception {
        SecretKey sk = KeyGenerator.getInstance("AES").generateKey();
        byte[] keyb = c.doFinal(sk.getEncoded());
        outs.write(keyb, 0, keyb.length);
        outs.flush();
        s.init(Cipher.ENCRYPT_MODE, sk);
        super.init(outs, fn);
    }

    @Override
    public String init(InputStream ins) throws Exception {
        byte[] keyb = new byte[128];
        ins.read(keyb);
        SecretKey sk = new SecretKeySpec(c.doFinal(keyb), "AES");
        s.init(Cipher.DECRYPT_MODE, sk);
        return super.init(ins);
    }

    @Override
    public byte[] process(byte[] data) throws Exception {
        return s.doFinal(data);
    }
}
