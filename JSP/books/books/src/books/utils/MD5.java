package books.utils;
//
/**加密工具
 * MD5 信息摘要演算法（Message-Digest Algorithm），一种被广泛使用的密码杂凑函数，
 * 可以产生出一个128位元（16位元组）的散列值（hash value），用于确保信息传输完整一致。
 *  * @author 
 * @date Feb 21, 2012
 */
import java.security.*;
import java.util.Base64;
import java.util.Base64.Encoder;

public class MD5 {
	public static String valueOf(String str) {
		String s = str;
		if (s == null) {
			return "";
		} else {
			String value = null;
			MessageDigest md5 = null;
			try {
				md5 = MessageDigest.getInstance("MD5");
			} catch (NoSuchAlgorithmException ex) {
			}
//			sun.misc.BASE64Encoder baseEncoder = new sun.misc.BASE64Encoder();
			Encoder encoder = Base64.getEncoder();
			try {
//				value = baseEncoder.encode(md5.digest(s.getBytes("utf-8")));
				value = encoder.encodeToString(md5.digest(s.getBytes("utf-8")));  
			} catch (Exception ex) {
			}
			return value;
		}
	}
	/* 测试
	public static void main(String[] arg)
	{
		System.out.println(valueOf("wyh"));
	}
	*/
	
}