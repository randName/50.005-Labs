import java.io.*;
import java.security.*;
import java.security.cert.*;

public class Verify {
    public static void main(String[] args) throws Exception {
        System.out.print("Opening...");
        InputStream fis = new FileInputStream("CA.cer");
        InputStream tis = new FileInputStream("1001557.cer");
        System.out.println(" OK");

        System.out.print("Creating certificates...");
        CertificateFactory cf = CertificateFactory.getInstance("X.509");
        X509Certificate CAcert = (X509Certificate)cf.generateCertificate(fis); 
        X509Certificate ServerCert = (X509Certificate)cf.generateCertificate(tis); 
        System.out.println(" OK");

        System.out.print("Verifying public key...");
        PublicKey key = CAcert.getPublicKey();
        ServerCert.checkValidity();
        ServerCert.verify(key);
        System.out.println(" OK");
    }
}
