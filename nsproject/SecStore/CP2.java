package SecStore;

import java.io.*;
import javax.crypto.*;
import java.security.*;
import javax.crypto.spec.SecretKeySpec;
import javax.xml.bind.DatatypeConverter;

public class CP2 extends CP {
    private static Cipher s;

    public CP2() throws Exception {
        super();
    }

    public CP2(PrivateKey pk) throws Exception {
        super(pk);
        s = Cipher.getInstance("AES/ECB/PKCS5Padding");
    }

    public CP2(PublicKey pk) throws Exception {
        super(pk);
        s = Cipher.getInstance("AES/ECB/PKCS5Padding");
    }

    public void send(String fn, OutputStream out) throws Exception {
        SecretKey sk = KeyGenerator.getInstance("AES").generateKey();
        byte[] keyb = c.doFinal(sk.getEncoded());
        out.write(keyb, 0, keyb.length);
        out.flush();

        s.init(Cipher.ENCRYPT_MODE, sk);
        BufferedWriter cout = createWriter(new CipherOutputStream(out, s));
        cout.write(fn, 0, fn.length());
        cout.write('\n');
        cout.flush();

        BufferedReader fin = createReader(new FileInputStream(fn));
        bufferedXfer(fin, cout);
        fin.close();
        cout.close();
    }

    public String receive(InputStream in) throws Exception {
        byte[] keyb = new byte[128];
        in.read(keyb);
        SecretKey sk = new SecretKeySpec(c.doFinal(keyb), "AES");

        s.init(Cipher.DECRYPT_MODE, sk);
        BufferedReader cin = createReader(new CipherInputStream(in, s));
        String fn = cin.readLine();

        BufferedWriter fout = createWriter(new FileOutputStream(fn));
        bufferedXfer(cin, fout);
        fout.close();
        cin.close();
        return fn;
    }
}
