package com.vt.c0906;

import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.widget.ImageView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class ImageLoader {
    private static final String EXCEPTION_FAILURE = "请求URL失败";
    private static final int MSG_OK = 0;
    private static final int MSG_ERROR = 1;
    private ImageView mImageView;
    private File mDownloadFile;
    // 使用新进程加载图片
    public void displayImage(ImageView imageView, final String imageUrl, final String cacheDir) {
        mImageView = imageView;
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    mDownloadFile = downloadFile(imageUrl, cacheDir);
                    if (mDownloadFile.exists()) {
                        mHandler.obtainMessage(MSG_OK).sendToTarget();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    mHandler.obtainMessage(MSG_ERROR).sendToTarget();
                }
            }
        }).start();
    }
    // 下载文件
    public File downloadFile(String path, String cachePath) throws Exception {
        // 判断缓存文件夹是否存在
        File storageDir = new File(cachePath);
        if (!storageDir.exists()) {
            storageDir.mkdirs();
        }
        // 获取缓存文件
        String[] temp = path.split("\\/");//拆分路径字符串
        String fileName = temp[temp.length - 1];//获取文件名
        File cacheFile = new File(storageDir, fileName);
        // 判断是否缓存
        if (cacheFile.exists()) {
            mDownloadFile = cacheFile;
            mHandler.obtainMessage(MSG_OK).sendToTarget();
        }
        // 将字符串格式的路径转为URL
        URL url = new URL(path);
        // 创建连接
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setConnectTimeout(5000);//设置连接超时时间
        conn.setReadTimeout(5000);//设置下载超时时间
        conn.setRequestMethod("GET");//设置请求类型为Get类型
        // 判断请求Url是否成功
        if (conn.getResponseCode() != 200) {
            throw new RuntimeException(EXCEPTION_FAILURE);
        }
        long contentLength = conn.getContentLengthLong();//文件数据大小
        // 判断是否缓存
        if (cacheFile.exists()) {
            // 如果缓存文件与下载文件大小相等则直接返回缓存文件
            if(cacheFile.length() == contentLength)
                return cacheFile;
        }
        // 下载文件
        InputStream is = conn.getInputStream();//获取输入流
        FileOutputStream fileOutputStream = null;//文件输出流
        if (is != null) {
            fileOutputStream = new FileOutputStream(cacheFile);//指定文件保存路径，代码看下一步
            byte[] buf = new byte[1024];
            int ch;
            while ((ch = is.read(buf)) != -1) {
                fileOutputStream.write(buf, 0, ch);//将获取到的流写入文件中
            }
        }
        if (fileOutputStream != null) {
            fileOutputStream.flush();
            fileOutputStream.close();
        }
        conn.disconnect();
        return cacheFile;
    }
    // 更新UI
    private Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_OK://下载成功
                    mImageView.setImageURI(Uri.fromFile(mDownloadFile));
                    break;
                case MSG_ERROR://下载出错
                    // 根据控件宽度显示不同的错误图片
                    if(mImageView.getWidth()>900){
                        mImageView.setImageResource(R.mipmap.img_error_h);
                    }else if(mImageView.getWidth()>300){
                        mImageView.setImageResource(R.mipmap.img_error_m);
                    }else{
                        mImageView.setImageResource(R.mipmap.img_error_s);
                    }
                    break;
            }
        }
    };
}