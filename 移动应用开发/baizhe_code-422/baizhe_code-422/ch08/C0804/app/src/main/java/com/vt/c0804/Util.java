package com.vt.c0804;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.webkit.MimeTypeMap;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Util {
    // 创建文件
    public static File creatFile(String parentPath, String childPath, String extension) {
        // 使用时间生成文件名
        SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd_hhmmss");
        String fileName = format.format(new Date());
        // 存储路径
        File storageDir = new File(parentPath, childPath);
        if (!storageDir.exists()) {
            storageDir.mkdirs();
        }
        // 创建文件
        File saveRecorderFile = new File(storageDir, "IMG_" + fileName + "." + extension);
        if (saveRecorderFile.exists()) {
            saveRecorderFile.delete();
        }
        return saveRecorderFile;
    }
    // 将图片或视频显示在系统相册
    public static void showInAlbum(Context context, String path) {
        // Android中分割字符串需要在分隔符左右两侧加上中括号
        String[] str = path.split("[.]");
        // 获取扩展名对应的文件类型值
        String mimeType = MimeTypeMap.getSingleton().getMimeTypeFromExtension(str[str.length - 1]);
        // 根据路径和扩展名的类型扫描媒体文件
        MediaScannerConnection.scanFile(context, new String[]{path}, new String[]{mimeType}, null);
        // 将图片显示在系统相册内
        context.sendBroadcast(new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE, Uri.parse("file://" + path)));
    }
    // 保存照片
    public static byte[] saveImage(byte[] bytes, File file, int degree) {
        if (degree != 0) {
            // byte[]转Bitmap
            Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
            // 旋转
            bitmap = rotateBitmapByDegree(bitmap, degree);
            // Bitmap转byte[]
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            bitmap.compress(Bitmap.CompressFormat.JPEG, 100, baos);
            bytes = baos.toByteArray();
        }
        // 写入文件
        FileOutputStream output = null;
        try {
            output = new FileOutputStream(file);
            output.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (null != output) {
                try {
                    output.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return bytes;
    }
    // 旋转位图
    public static Bitmap rotateBitmapByDegree(Bitmap bitmap, int degree) {
        Bitmap returnBitmap = null;
        // 根据旋转角度，生成旋转矩阵
        Matrix matrix = new Matrix();
        matrix.postRotate(degree);
        try {
            // 将原始图片按照旋转矩阵进行旋转，并得到新的图片
            returnBitmap = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), matrix, true);
        } catch (OutOfMemoryError e) {
        }
        if (returnBitmap == null) {
            returnBitmap = bitmap;
        }
        // 回收内存
        if (bitmap != returnBitmap && !bitmap.isRecycled()) {
            bitmap.recycle();
        }
        return returnBitmap;
    }
}