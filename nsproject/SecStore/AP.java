package SecStore;

import java.io.*;
import java.security.*;
import java.util.Arrays;
import javax.crypto.Cipher;
import java.security.cert.*;
import java.security.spec.PKCS8EncodedKeySpec;

public class AP {
    private static Cipher c;
    private static byte[] certificate;
    private static PublicKey publicKey;
    private static PrivateKey privateKey;
    private static X509Certificate serverCert;
    private static byte[] challenge = new byte[16];
    private static byte[] response = new byte[128];

    public AP(InputStream cert, InputStream pk) throws Exception {
        serverCert = getCert(cert); 
        certificate = serverCert.getEncoded();

        KeyFactory kf = KeyFactory.getInstance("RSA");
        byte[] encKey = new byte[pk.available()];
        pk.read(encKey);
        privateKey = kf.generatePrivate(new PKCS8EncodedKeySpec(encKey));

        c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        c.init(Cipher.ENCRYPT_MODE, privateKey);
    }

    public AP(InputStream in) throws Exception {
        serverCert = getCert(in);
        serverCert.checkValidity();
        publicKey = serverCert.getPublicKey();

        c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        c.init(Cipher.DECRYPT_MODE, publicKey);

        SecureRandom random = new SecureRandom();
        random.nextBytes(challenge);
    }

    private X509Certificate getCert(InputStream cert) throws Exception {
        CertificateFactory cf = CertificateFactory.getInstance("X.509");
        X509Certificate serverCert = (X509Certificate) cf.generateCertificate(cert);
        return serverCert;
    }

    public boolean verify(InputStream in) {
        try {
            in.read(response);
            return Arrays.equals(challenge, c.doFinal(response));
        } catch (Exception e) {
            return false;
        }
    }

    public byte[] respond(byte[] q) throws Exception {
        return c.doFinal(q);
    }

    public PrivateKey getPrivateKey() {
        return privateKey;
    }

    public PublicKey getPublicKey() {
        return publicKey;
    }

    public byte[] getCertificate() {
        return certificate;
    }

    public byte[] getChallenge() {
        return challenge;
    }

    public static void ppbytes(byte[] data) {
        for ( byte b : data ) System.out.printf("%02X ", b);
        System.out.println();
    }
}
