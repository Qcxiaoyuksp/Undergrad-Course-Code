package com.vt.c0801;

import android.content.Context;
import android.content.Intent;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.webkit.MimeTypeMap;
import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Util {
    // 创建文件
    public static File createFile(String parentPath, String childPath, String extension) {
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
}