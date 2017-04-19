package SecStore;

import java.io.*;
import javax.crypto.*;
import java.security.*;
import java.util.Arrays;
import javax.crypto.spec.SecretKeySpec;
import javax.xml.bind.DatatypeConverter;

public class CP {
    private int count;
    private byte[] enc;
    protected String data;
    protected byte[] buffer;
    protected Cipher c;
    protected PrintWriter out;
    protected BufferedReader in;

    public CP(PrivateKey privatek, PublicKey publick) throws Exception {
        c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        if ( privatek != null ) {
            c.init(Cipher.DECRYPT_MODE, privatek);
        } else if ( publick != null ) {
            c.init(Cipher.ENCRYPT_MODE, publick);
        }
        buffer = new byte[8192];
    }

    public CP(PrivateKey pk) throws Exception {
        this(pk, null);
    }

    public CP(PublicKey pk) throws Exception {
        this(null, pk);
    }

    public void init(OutputStream outs, String fn) throws Exception {
        out = new PrintWriter(outs);
        out.println(DatatypeConverter.printBase64Binary(c.doFinal(fn.getBytes())));
        out.flush();
    }

    public String init(InputStream ins) throws Exception {
        in = new BufferedReader(new InputStreamReader(ins));
        return new String(c.doFinal(
            DatatypeConverter.parseBase64Binary(in.readLine())));
    }

    public void transfer(FileInputStream fin) throws Exception {
        while ((count = fin.read(buffer)) > 0) {
            if ( count < buffer.length ) {
                enc = process(Arrays.copyOf(buffer, count));
            } else {
                enc = process(buffer);
            }
            data = DatatypeConverter.printBase64Binary(enc);
            out.println(data);
            out.flush();
            //System.out.print(".");
        }
        fin.close();
    }

    public void transfer(FileOutputStream fout) throws Exception {
        while ((data = in.readLine()) != null) {
            fout.write(process(DatatypeConverter.parseBase64Binary(data)));
            //System.out.print(".");
        }
        fout.close();
    }

    public byte[] process(byte[] data) throws Exception {
        return data;
    }
}
