package SecStore;

import java.io.*;
import javax.crypto.*;
import java.security.*;

public class CP1 extends CP {

    public CP1() throws Exception {
        super();
    }

    public CP1(PrivateKey pk) throws Exception {
        super(pk);
    }

    public CP1(PublicKey pk) throws Exception {
        super(pk);
    }

    public void send(String fn, OutputStream out) throws Exception {
        BufferedWriter cout = createWriter(new CipherOutputStream(out, c));
        cout.write(fn, 0, fn.length());
        cout.write('\n');
        cout.flush();

        BufferedReader fin = createReader(new FileInputStream(fn));
        bufferedXfer(fin, cout);
        fin.close();
        cout.close();
    }

    public String receive(InputStream in) throws Exception {
        BufferedReader cin = createReader(new CipherInputStream(in, c));
        String fn = cin.readLine();

        BufferedWriter fout = createWriter(new FileOutputStream(fn));
        bufferedXfer(cin, fout);
        fout.close();
        cin.close();
        return fn;
    }
}
