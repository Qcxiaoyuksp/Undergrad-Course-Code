package com.vt.c0905;

import android.content.ContentResolver;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileDescriptor;
import java.io.IOException;

public class CompressImage {
	public String cachePath;//缓存路径
	public int size;//压缩后的最大文件大小 单位kb	
	private int quality;//压缩质量0-100	

	public CompressImage(String cachePath, int size) {
		this.cachePath=cachePath;
		this.size=size;
		this.quality=80;
	}
	// 压缩位图，Android10以上需要添加<application android:requestLegacyExternalStorage = "true">
	public Bitmap compress(String srcPath) {
		Bitmap bitmap = BitmapFactory.decodeFile(srcPath);
		bitmap = BitmapFactory.decodeFile(srcPath, getSampleSize(bitmap));
		return compressByQuality(bitmap);
	}
	// 压缩位图
	public Bitmap compress(ContentResolver contentResolver, Uri uri)throws IOException {
		ParcelFileDescriptor parcelFileDescriptor = contentResolver.openFileDescriptor(uri, "r");
		FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();

		Bitmap bitmap = BitmapFactory.decodeFileDescriptor(fileDescriptor);
		bitmap = BitmapFactory.decodeFileDescriptor(fileDescriptor,null, getSampleSize(bitmap));
		parcelFileDescriptor.close();
		return compressByQuality(bitmap);
	}
	// 获取缩放采样
	private BitmapFactory.Options getSampleSize(Bitmap bitmap){
		// 位图尺寸
		int w = bitmap.getWidth();
		int h = bitmap.getHeight();
		// 缩放后尺寸
		int hh = 1280;
		int ww = 720;
		// 缩放比例，1表示不缩放。
		int be = 1;
		if (w > h && w > ww) {//如果宽度大的话根据宽度固定大小缩放
			be = w / ww;
		} else if (w < h && h > hh) {//如果高度高的话根据宽度固定大小缩放
			be = h / hh;
		}
		if (be <= 0) be = 1;
		BitmapFactory.Options newOpts = new BitmapFactory.Options();
		newOpts.inSampleSize = be;//设置缩放比例
		return newOpts;
	}
	// 压缩质量
	private Bitmap compressByQuality(Bitmap image) {
		ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
		// 质量压缩方法，这里100表示不压缩，把压缩后的数据存放到baos中
		image.compress(Bitmap.CompressFormat.JPEG, quality, outputStream);
		int options = 100;
		// 循环判断如果压缩后图片是否大于100kb,大于继续压缩
		while ( outputStream.toByteArray().length > 1024*size) {
			Log.e("size", String.valueOf(outputStream.toByteArray().length));
			outputStream.reset();//重置baos即清空baos
			options -= 10;//每次都减少10
			quality=options;
			image.compress(Bitmap.CompressFormat.JPEG, options, outputStream);
		}
		// 压缩后的数据baos存放到ByteArrayInputStream中
		ByteArrayInputStream inputStream = new ByteArrayInputStream(outputStream.toByteArray());
		// ByteArrayInputStream数据生成图片
		Bitmap bitmap = BitmapFactory.decodeStream(inputStream, null, null);
		return bitmap;
	}
}