package com.vt.c0902;

import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.ImageView;
import android.widget.ProgressBar;
import java.io.File;

public class ImageLoader {
    private static final int MSG_OK = 0;
    private static final int MSG_ERROR = 1;
    private ImageView mImageView;
    private ProgressBar mProgressBar;
    private File mDownloadFile;
    // 使用新进程加载图片
    public void displayImage(ImageView imageView, final String imageUrl, final String cacheDir, ProgressBar progressBar) {
        mImageView = imageView;
        mProgressBar = progressBar;
        mProgressBar.setVisibility(View.VISIBLE);
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    mDownloadFile = Http.downloadFile(imageUrl, cacheDir);
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
    // 更新UI
    private Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_OK://下载成功
                    mImageView.setImageURI(Uri.fromFile(mDownloadFile));
                    mProgressBar.setVisibility(View.GONE);
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
                    mProgressBar.setVisibility(View.GONE);
                    break;
            }
        }
    };
}