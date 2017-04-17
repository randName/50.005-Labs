import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import javax.crypto.*;
import javax.xml.bind.DatatypeConverter;


public class TextEncryption {
	public static void main(String[] args) throws Exception {
		String data = "";
		String line;
		BufferedReader bufferedReader = new BufferedReader( new FileReader(args[0])); //args[0] is the file you are going to encrypt. 
		while((line = bufferedReader.readLine())!=null) {
			data = data +"\n" + line;
		}

        // Print to screen contents of the file
        //System.out.println(data);

        // generate secret key using DES algorithm
        SecretKey sk = KeyGenerator.getInstance("DES").generateKey();

        // create cipher object, initialize the ciphers with the given key, choose encryption mode as DES
        Cipher ce = Cipher.getInstance("DES");
        ce.init(Cipher.ENCRYPT_MODE, sk);

        // do encryption, by calling method Cipher.doFinal().
        byte[] enc = ce.doFinal(data.getBytes());

        // print the length of output encrypted byte[], compare the length of file smallSize.txt and largeSize.txt
        System.out.println("Encrpyted length: "+enc.length);

        // do format conversion. Turn the encrypted byte[] format into base64format String using DatatypeConverter
        String b64 = DatatypeConverter.printBase64Binary(enc);

        // print the encrypted message (in base64format String format)
        System.out.println(b64);

        // create cipher object, initialize the ciphers with the given key, choose decryption mode as DES
        Cipher de = Cipher.getInstance("DES");
        de.init(Cipher.DECRYPT_MODE, sk);

        // do decryption, by calling method Cipher.doFinal().
        byte[] dec = de.doFinal(enc);

        // do format conversion. Convert the decrypted byte[] to String, using "String a = new String(byte_array);"
        String a = new String(dec);

        // print the decrypted String text and compare it with original text
        System.out.println(a);

    }
}

