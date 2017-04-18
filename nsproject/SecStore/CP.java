package SecStore;

import java.io.*;
import javax.crypto.*;
import java.security.*;
import javax.crypto.spec.SecretKeySpec;
import javax.xml.bind.DatatypeConverter;

public class CP {
    protected static Cipher c;

    public CP() throws Exception {
        c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
    }

    public CP(PrivateKey pk) throws Exception {
        this();
        c.init(Cipher.DECRYPT_MODE, pk);
    }

    public CP(PublicKey pk) throws Exception {
        this();
        c.init(Cipher.ENCRYPT_MODE, pk);
    }

    public static BufferedReader createReader(InputStream in) {
        return new BufferedReader(new InputStreamReader(in));
    }

    public static BufferedWriter createWriter(OutputStream out) {
        return new BufferedWriter(new OutputStreamWriter(out));
    }

    public static void bufferedXfer(BufferedReader in, BufferedWriter out) throws Exception {
        int count;
        char[] buffer = new char[1024];
        while ((count = in.read(buffer, 0, 1024)) > 0) out.write(buffer, 0, count);
    }

    public static void printBytes(byte[] data) {
        for ( byte i = 0; i < data.length; i++ ) System.out.printf("%02X ", data[i]);
        System.out.println();
    }

    public void send(String fn, OutputStream out) throws Exception {
    }

    public String receive(InputStream in) throws Exception {
        return "";
    }
}
