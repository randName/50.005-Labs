import javax.xml.bind.DatatypeConverter;
import javax.crypto.Cipher;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.security.*;


public class DigitalSignature {

    public static void main(String[] args) throws Exception {
        //Read the text file and save to String data
        String data = "";
        String line;
        BufferedReader bufferedReader = new BufferedReader( new FileReader(args[0]));
        while((line= bufferedReader.readLine())!=null){
            data = data +"\n" + line;
        }

        // generate a RSA keypair, initialize as 1024 bits, get public key and private key from this keypair.
        KeyPairGenerator kg = KeyPairGenerator.getInstance("RSA");
        kg.initialize(1024);
        KeyPair kp = kg.generateKeyPair();
        Key publicKey = kp.getPublic();
        Key privateKey = kp.getPrivate();

        // Calculate message digest, using MD5 hash function
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] digest = md.digest(data.getBytes());

        // print the length of output digest byte[], compare the length of file smallSize.txt and largeSize.txt
        System.out.println("digest ("+digest.length+" bytes): "+DatatypeConverter.printBase64Binary(digest));
        System.out.println("data length: "+data.length());

        // Create RSA("RSA/ECB/PKCS1Padding") cipher object and initialize is as encrypt mode, use PRIVATE key.
        Cipher ce = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        ce.init(Cipher.ENCRYPT_MODE, privateKey);

        // encrypt digest message
        byte[] enc = ce.doFinal(digest);

        // print the encrypted message (in base64format String using DatatypeConverter) 
        String b64 = DatatypeConverter.printBase64Binary(enc);
        System.out.println(b64);

        // Create RSA("RSA/ECB/PKCS1Padding") cipher object and initialize is as decrypt mode, use PUBLIC key.           
        Cipher de = Cipher.getInstance("RSA/ECB/PKCS1Padding");
        de.init(Cipher.DECRYPT_MODE, publicKey);

        // decrypt message
        byte[] dec = de.doFinal(enc);

        // print the decrypted message (in base64format String using DatatypeConverter), compare with origin digest 
        System.out.println("decrypted: "+DatatypeConverter.printBase64Binary(dec));

    }
}
