package com.vt.c0804;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.FileProvider;
import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import java.io.File;
import java.io.IOException;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "MainActivity";
    private Context mContext = this;
    private PreviewTextureView mPreview;        //预览拍摄画面
    private Button mButton;

    private Camera mCamera;                     //摄像头的对象
    private Camera.Size mSelectSize;            //摄像头的分辨率
    private MediaRecorder mMediaRecorder;       //录制视频的对象
    private boolean isRecorder = false;         //是否在录制视频
    private File mPhotoFile;                    //视频保存路径
    private int mMaxRecordDuration = 60 * 60;   //最长录制时间（秒）
    private int mVideoEncodingBitRate = 8;      //视频码率
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0804:使用Camera类录制视频");
        mButton = findViewById(R.id.button);
        mButton.setOnClickListener(this);
        // 判断是否已经取得相机录制视频权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);
        } else {
            init();
        }
    }
    @Override
    public void onResume() {
        super.onResume();
        if (!mPreview.isAvailable()) {
            isRecorder = false;
            mButton.setText("录制");
            mPreview = findViewById(R.id.texture_view);
        }
        if (mCamera != null) {
            mCamera.startPreview();
        }
    }
    @Override
    public void onPause() {
        super.onPause();
        if (mCamera != null) {
            mCamera.stopPreview();
        }
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mMediaRecorder != null) {
            if (isRecorder) {
                mMediaRecorder.stop();
            }
            mMediaRecorder.release();
            mMediaRecorder = null;
        }
        if (mCamera != null) {
            mCamera.stopPreview();
            mCamera.release();
            mCamera = null;
        }
    }
    // 初始化
    private void init() {
        mPreview = findViewById(R.id.texture_view);
        // 初始化预览控件的监听
        mPreview.setSurfaceTextureListener(new TextureView.SurfaceTextureListener() {
            @Override
            public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
                try {
                    initCamera();
                    mCamera.setPreviewTexture(surface);
                    mCamera.startPreview();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            @Override
            public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) { }
            @Override
            public void onSurfaceTextureUpdated(SurfaceTexture surface) { }
            @Override
            public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
                mCamera.stopPreview();
                return false;
            }
        });
    }
    // 点击事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button:
                if (isRecorder) {
                    stopRecorder();
                    mButton.setText("录制");
                } else {
                    startRecorder();
                    mButton.setText("停止");
                }
                break;
        }
    }
    // 初始化相机
    private void initCamera() {
        mCamera = Camera.open(Camera.CameraInfo.CAMERA_FACING_BACK);
        mSelectSize = selectPreviewSize(mCamera.getParameters());
        mPreview.setAspectRatio(mSelectSize.height, mSelectSize.width);

        Camera.Parameters parameters = mCamera.getParameters();
        parameters.setFlashMode(Camera.Parameters.FLASH_MODE_OFF);              //关闭闪光灯
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO); //设置自动对焦
        parameters.setPreviewSize(mSelectSize.width, mSelectSize.height);       //设置预览尺寸
        parameters.setPictureSize(mSelectSize.width, mSelectSize.height);       //设置图片尺寸
        parameters.set("orientation", "portrait");  //设置相片方向
        parameters.set("rotation", 90);             //设置相片镜头角度转90度
//        mCamera.setParameters(parameters);          //设置参数
        mCamera.setDisplayOrientation(90);          //设置显示方向
    }
    // 配置MedioRecorder
    private void configMedioRecorder() {
        mCamera.unlock();//使用MediaRecorder.setCamera()方法前需要解锁，否则报错。
        Intent intent = getIntent();
        if(intent.getAction().equals("android.media.action.VIDEO_CAPTURE")) {
            mMaxRecordDuration = intent.getIntExtra(MediaStore.EXTRA_DURATION_LIMIT, mMaxRecordDuration);
            if(intent.getIntExtra(MediaStore.EXTRA_VIDEO_QUALITY, 0) == 0) {
                mVideoEncodingBitRate = 1;
            }
        }
        mPhotoFile = Util.creatFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "mp4");
        mMediaRecorder = new MediaRecorder();
        mMediaRecorder.setCamera(mCamera);
        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.DEFAULT);   //设置音频源
        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.DEFAULT);   //设置视频源
        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.DEFAULT); //设置输出格式
        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.DEFAULT); //设置音频编码格式
        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.DEFAULT); //设置视频编码格式
        mMediaRecorder.setVideoSize(mSelectSize.width, mSelectSize.height); //设置视频分辨率
        mMediaRecorder.setVideoEncodingBitRate(mVideoEncodingBitRate * mSelectSize.width * mSelectSize.height);//设置视频的比特率
        mMediaRecorder.setVideoFrameRate(30);   //设置视频的帧率
        mMediaRecorder.setOrientationHint(90);  //设置视频的角度
        mMediaRecorder.setMaxDuration(mMaxRecordDuration * 1000);//设置最大录制时间
        mMediaRecorder.setPreviewDisplay(new Surface(mPreview.getSurfaceTexture()));//设置预览
        mMediaRecorder.setOutputFile(mPhotoFile.getAbsolutePath());//设置文件保存路径
        mMediaRecorder.setOnErrorListener(new MediaRecorder.OnErrorListener() { //录制异常监听
            @Override
            public void onError(MediaRecorder mr, int what, int extra) {
                mMediaRecorder.stop();
                mMediaRecorder.reset();
                try {
                    mCamera.setPreviewTexture(mPreview.getSurfaceTexture());
                    mCamera.startPreview();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        // 监听是否到达最长录制事件
        mMediaRecorder.setOnInfoListener(new MediaRecorder.OnInfoListener() {
            @Override
            public void onInfo(MediaRecorder mr, int what, int extra) {
                if(what == MediaRecorder.MEDIA_RECORDER_INFO_MAX_DURATION_REACHED){
                    stopRecorder();
                }
            }
        });
    }
    // 开启录制视频
    private void startRecorder() {
        mCamera.stopPreview();//暂停相机预览
        configMedioRecorder();//再次配置MedioRecorder
        try {
            mMediaRecorder.prepare();//准备录制
        } catch (IOException e) {
            e.printStackTrace();
        }
        mMediaRecorder.start();//开始录制
        isRecorder = true;
    }
    // 停止录制视频
    private void stopRecorder() {
        mMediaRecorder.stop();//暂停录制
        mMediaRecorder.reset();//重置为空闲状态
        isRecorder = false;
        try {
            mCamera.setPreviewTexture(mPreview.getSurfaceTexture());
            mCamera.startPreview(); //重新开启相机预览
        } catch (IOException e) {
            e.printStackTrace();
        }
        Util.showInAlbum(mContext, mPhotoFile.getAbsolutePath());

        Uri videoUri = FileProvider.getUriForFile(this, "com.vt.c0804.fileprovider", mPhotoFile);
        Intent intent = getIntent();
        // 判断是否被其他APP隐式启动
        if (intent.getAction().equals("android.media.action.VIDEO_CAPTURE")) {
            intent = new Intent();
            intent.setDataAndType(videoUri, "video/mp4");//设置返回的数据及其类型
            intent.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);//授予临时读取权限
            setResult(RESULT_OK, intent);
            // 关闭返回到其他APP
            finish();
        } else {
            // 启动播放录制视频的Activity
            intent = new Intent(MainActivity.this, PreviewActivity.class);
            intent.setDataAndType(videoUri, "video/mp4");
            startActivity(intent);
        }
    }
    // 计算获取预览尺寸
    private Camera.Size selectPreviewSize(Camera.Parameters parameters) {
        List<Camera.Size> previewSizeList = parameters.getSupportedPreviewSizes();
        if (previewSizeList.size() == 0) {
            return null;
        }
        Camera.Size currentSelectSize = null;
        DisplayMetrics displayMetrics = getResources().getDisplayMetrics();
        int deviceWidth = displayMetrics.widthPixels;
        int deviceHeight = displayMetrics.heightPixels;
        for (int i = 1; i < 41; i++) {
            for (Camera.Size itemSize : previewSizeList) {
                Log.e(TAG, "可选尺寸： 宽=" + itemSize.width + "高" + itemSize.height);
                if (itemSize.height > (deviceWidth - i * 5) && itemSize.height < (deviceWidth + i * 5)) {
                    if (currentSelectSize != null) { //判断是否已经找到一个匹配的宽度
                        if (Math.abs(deviceHeight - itemSize.width) < Math.abs(deviceHeight - currentSelectSize.width)) { //求绝对值算出最接近设备高度的尺寸
                            currentSelectSize = itemSize;
                            continue;
                        }
                    } else {
                        currentSelectSize = itemSize;
                    }
                }
            }
        }
        Log.e(TAG, "匹配尺寸： 宽=" + currentSelectSize.width + "高" + currentSelectSize.height);
        return currentSelectSize;
    }
    // 权限请求的回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
                    Permissions.requestPermissions(mContext, PERMISSIONS);
                } else {
                    init();
                }
                break;
        }
    }
}