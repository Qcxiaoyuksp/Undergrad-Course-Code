package com.mayinlong.utils;

/**
 * @author 
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
	public static void main(String[] args) {
		System.out.println(valueOf("123456"));
	}
}