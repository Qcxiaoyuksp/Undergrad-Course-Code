package com.vt.c0906;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.Point;
import android.media.Image;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.provider.MediaStore;
import android.util.Size;
import android.webkit.MimeTypeMap;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;

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
        File saveFile = new File(storageDir, "AUD_" + fileName + "." + extension);
        if (saveFile.exists()) {
            saveFile.delete();
        }
        return saveFile;
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
    // bitmap转byte[]
    public  static byte[] imageToBytes(Image image){
        ByteBuffer buffer = image.getPlanes()[0].getBuffer();
        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);
        return bytes;
    }
    // 获取最佳尺寸
    public static Size chooseOptimalSize(Context context, Size[] choices, int previewWidth, int previewHeight, int maxPreviewWidth, int maxPreviewHeight, Size aspectRatio) {
        Point displaySize = new Point();
        // 获取屏幕尺寸
        ((Activity) context).getWindowManager().getDefaultDisplay().getSize(displaySize);
        int textureViewWidth = previewWidth;
        int textureViewHeight = previewHeight;
        int maxWidth = displaySize.x;
        int maxHeight = displaySize.y;
        if (maxWidth > maxPreviewWidth) { maxWidth = maxPreviewWidth; }
        if (maxHeight > maxPreviewHeight) { maxHeight = maxPreviewHeight; }
        List<Size> bigEnough = new ArrayList<>();//用于保存支持的不小于预览图像的尺寸
        List<Size> notBigEnough = new ArrayList<>();//用于保存支持的小于预览图像的尺寸
        int w = aspectRatio.getWidth();
        int h = aspectRatio.getHeight();
        // 将设备支持的尺寸分类保存
        for (Size option : choices) {
            if (option.getWidth() <= maxWidth && option.getHeight() <= maxHeight && option.getHeight() == option.getWidth() * h / w) {
                if (option.getWidth() >= textureViewWidth &&
                        option.getHeight() >= textureViewHeight) {
                    bigEnough.add(option);
                } else {
                    notBigEnough.add(option);
                }
            }
        }
        // 选择足够大的最小的尺寸。如果没有足够大的尺寸，就从不够大的尺寸中挑选最大的尺寸。
        if (bigEnough.size() > 0) {
            return Collections.min(bigEnough, new Util.CompareSizesByArea());
        } else if (notBigEnough.size() > 0) {
            return Collections.max(notBigEnough, new Util.CompareSizesByArea());
        } else {
            return choices[0];
        }
    }
    // 计算视频尺寸
    public static Size chooseVideoSize(Size[] choices) {
        for (Size size : choices) {
            System.out.println(size.getWidth()+"*"+size.getHeight());
            if (size.getWidth() == size.getHeight() * 4 / 3 && size.getWidth() <= 1080) {
                return size;
            }
        }
        return choices[choices.length - 1];
    }
    // 比较两个Size的大小的规则
    static class CompareSizesByArea implements Comparator<Size> {
        @Override
        public int compare(Size lhs, Size rhs) {
            return Long.signum((long) lhs.getWidth() * lhs.getHeight() - (long) rhs.getWidth() * rhs.getHeight());
        }
    }
    // PCM转WAV格式文件
    public static void pcmToWave(String inFileName, String outFileName,long mSampleRateInHZ,int mRecorderBufferSize) {
        int channels = 2;
        long byteRate = 16 * mSampleRateInHZ * channels / 8;
        byte[] data = new byte[mRecorderBufferSize];
        try {
            FileInputStream in = new FileInputStream(inFileName);
            FileOutputStream out = new FileOutputStream(outFileName);
            long totalAudioLen = in.getChannel().size();
            long totalDataLen = totalAudioLen + 36;
            // 写入文件头
            writeWaveFileHeader(out, totalAudioLen, totalDataLen, mSampleRateInHZ, channels, byteRate);
            // 逐行将PCM文件写入到WAV文件
            while (in.read(data) != -1) {
                out.write(data);
            }
            in.close();
            out.close();
        }  catch (IOException e) {
            e.printStackTrace();
        }
    }
    // 添加wav文件头用于识别文件类型，文件头属于RIFF文件结构，每一部分为一个chunk，其中有RIFF WAVE chunk，FMT Chunk，Fact chunk,Data chunk,其中Fact chunk是可以选择的。
    private static void writeWaveFileHeader(FileOutputStream out, long totalAudioLen, long totalDataLen, long longSampleRate, int channels, long byteRate) throws IOException {
        byte[] header = new byte[44];
        // RIFF WAVE chunk
        header[0] = 'R';
        header[1] = 'I';
        header[2] = 'F';
        header[3] = 'F';
        header[4] = (byte) (totalDataLen & 0xff);//数据大小
        header[5] = (byte) ((totalDataLen >> 8) & 0xff);
        header[6] = (byte) ((totalDataLen >> 16) & 0xff);
        header[7] = (byte) ((totalDataLen >> 24) & 0xff);
        // 文件格式
        header[8] = 'W';
        header[9] = 'A';
        header[10] = 'V';
        header[11] = 'E';
        // FMT Chunk
        header[12] = 'f';
        header[13] = 'm';
        header[14] = 't';
        header[15] = ' ';//过渡字节
        // 数据大小
        header[16] = 16;//4bytes
        header[17] = 0;
        header[18] = 0;
        header[19] = 0;
        // 编码方式 10H为PCM编码格式
        header[20] = 1;//format = 1
        header[21] = 0;
        // 通道数
        header[22] = (byte) channels;
        header[23] = 0;
        // 采样率
        header[24] = (byte) (longSampleRate & 0xff);
        header[25] = (byte) ((longSampleRate >> 8) & 0xff);
        header[26] = (byte) ((longSampleRate >> 16) & 0xff);
        header[27] = (byte) ((longSampleRate >> 24) & 0xff);
        // 传送速率（采样率*通道数*采样深度/8）
        header[28] = (byte) (byteRate & 0xff);
        header[29] = (byte) ((byteRate >> 8) & 0xff);
        header[30] = (byte) ((byteRate >> 16) & 0xff);
        header[31] = (byte) ((byteRate >> 24) & 0xff);
        // 缓冲区大小（通道数*采样位数）
        header[32] = (byte) (1 * 16 / 8);
        header[33] = 0;
        // 每个样本的数据位数
        header[34] = 16;
        header[35] = 0;
        // Data chunk
        header[36] = 'd';//data
        header[37] = 'a';
        header[38] = 't';
        header[39] = 'a';
        header[40] = (byte) (totalAudioLen & 0xff);
        header[41] = (byte) ((totalAudioLen >> 8) & 0xff);
        header[42] = (byte) ((totalAudioLen >> 16) & 0xff);
        header[43] = (byte) ((totalAudioLen >> 24) & 0xff);
        out.write(header, 0, 44);
    }
    //将uri转为string
    public static String UriToString(ContentResolver contentResolver, Uri fileUrl) {
        String fileName = null;
        if (fileUrl != null) {
            if (fileUrl.getScheme().compareTo("content") == 0) {//content://开头的uri
                Cursor cursor = contentResolver.query(fileUrl, null, null, null, null);
                if (cursor != null && cursor.moveToFirst()) {
                    int column_index = cursor.getColumnIndexOrThrow("_data");
                    fileName = cursor.getString(column_index); //取出文件路径
                    cursor.close();
                }
            } else if (fileUrl.getScheme().compareTo("file") == 0) {//file:///开头的uri
                fileName = fileUrl.toString().replace("file://", "");//替换file:
                int index = fileName.indexOf("/sdcard");
                fileName = index == -1 ? fileName : fileName.substring(index);
            }
        }
        return fileName;
    }
    // 获取图片旋转角度
    public static int getImageOrientation(Context context, Uri photoUri) {
        int orientation = 0;
        // 通过媒体库查询图片的旋转角度
        Cursor cursor = context.getContentResolver().query(photoUri, new String[] { MediaStore.Images.ImageColumns.ORIENTATION }, null, null, null);
        if (cursor != null) {
            if (cursor.getCount() != 1) {
                return -1;
            }
            cursor.moveToFirst();
            orientation = cursor.getInt(0);
            cursor.close();
        }
        return orientation;
    }
    // 保存缓存图片
    public static File saveCacheBitmap(String cachePath,String filename, Bitmap bitmap) {
        File dir = new File(cachePath);
        if (!dir.exists()) {
            dir.mkdir();
        }
        // bitmap转byte[]
        File file = new File(cachePath,filename);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        byte[] bytes = baos.toByteArray();
        // 写入文件
        try {
            FileOutputStream output = new FileOutputStream(file);
            output.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return file;
    }
}