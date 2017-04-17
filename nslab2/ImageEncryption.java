import java.lang.Object;
import javax.imageio.ImageIO;
import java.io.*;
import java.awt.image.BufferedImage;
import java.nio.*;
import javax.crypto.*;
import javax.xml.bind.DatatypeConverter;


public class ImageEncryption {
	public static void main(String[] args) throws Exception {
		int image_width;
		int image_length;
		// read image file and save pixel value into int[][] imageArray
		BufferedImage img = ImageIO.read(new File(args[0])); // pass the image globe.bmp as first command-line argument. 
		image_width = img.getWidth();
		image_length = img.getHeight();
		//byte[][] imageArray = new byte[image_width][image_length];
		int[][] imageArray = new int[image_width][image_length];
		for(int idx = 0; idx < image_width; idx++) {
			for(int idy = 0; idy < image_length; idy++) {
				int color = img.getRGB(idx, idy);
				imageArray[idx][idy] = color;            
			}
		} 
		// generate secret key using DES algorithm
        SecretKey sk = KeyGenerator.getInstance("DES").generateKey();

		// Create cipher object, initialize the ciphers with the given key, choose encryption algorithm/mode/padding,
		//you need to try both ECB and CBC mode, use PKCS5Padding padding method
        //Cipher ce = Cipher.getInstance("DES/ECB/PKCS5Padding");
        Cipher ce = Cipher.getInstance("DES/CBC/PKCS5Padding");
        ce.init(Cipher.ENCRYPT_MODE, sk);
        
		// define output BufferedImage, set size and format
		BufferedImage outImage = new BufferedImage(image_width,image_length, BufferedImage.TYPE_3BYTE_BGR);

		for(int idx = 0; idx < image_width; idx++) {
			// convert each column int[] into a byte[] (each_width_pixel)
			byte[] each_width_pixel = new byte[4*image_length];
			for(int idy = 0; idy < image_length; idy++) {
				ByteBuffer dbuf = ByteBuffer.allocate(4);
				dbuf.putInt(imageArray[idx][idy]);
				byte[] bytes = dbuf.array();
				System.arraycopy(bytes, 0, each_width_pixel, idy*4, 4);
			}

			// encrypt each column or row bytes 
            byte[] enc_b = ce.doFinal(each_width_pixel);
            byte[] enc_p = new byte[4];

			// convert the encrypted byte[] back into int[] and write to outImage (use setRGB)
			for(int idy = 0; idy < image_length; idy++) {
                System.arraycopy(enc_b, idy*4, enc_p, 0, 4);
                outImage.setRGB(idx, idy, ByteBuffer.wrap(enc_p).getInt());
            }

		}
		//write outImage into file
		//ImageIO.write(outImage, "BMP",new File("ecb.bmp"));//for the ECB mode output
		ImageIO.write(outImage, "BMP",new File("cbc.bmp"));//for the CBC mode output
	}
}
