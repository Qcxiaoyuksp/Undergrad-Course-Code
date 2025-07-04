package com.vt.c0803;

import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.util.Size;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    private Context mContext = this;
    private PreviewTextureView mPreview;
    private Button mButton;
    private int mCameraId = 0;
    private Camera mCamera = null;
    private Size mPhotoSize = new Size(1080, 1920);
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mButton = findViewById(R.id.button);
        // 判断是否已经取得相机拍照权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);
        } else {
            init();
        }
    }
    // 初始化
    private void init() {
        mPreview = findViewById(R.id.surface_view);
        // 初始化预览控件的监听
        mPreview.setSurfaceTextureListener(new TextureView.SurfaceTextureListener() {
            @Override
            public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
                setupConfig(surface,width,height);
                startPreview();
            }
            @Override
            public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) { }
            @Override
            public void onSurfaceTextureUpdated(SurfaceTexture surface) { }
            @Override
            public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
                stopPreview();
                return false;
            }
        });
    }
    @Override
    public void onResume() {
        super.onResume();
        if (!mPreview.isAvailable()) {
            mPreview = findViewById(R.id.surface_view);
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
        if (mCamera != null) {
            mCamera.release();
            mCamera = null;
        }
    }
    // 开始预览
    private void startPreview() {
        mCamera.startPreview();
    }
    // 停止预览
    private void stopPreview() {
        if (mCamera != null) {
            mCamera.stopPreview();
            mCamera.release();
            mCamera = null;
        }
    }
    // 设置
    private void setupConfig(SurfaceTexture surface, int width, int height) {
        // 打开摄像头
        mCamera = Camera.open(mCameraId);
        // 设置用于预览的控件尺寸
        mPreview.setAspectRatio(width,height);
        try {
            mCamera.setPreviewTexture(surface);
            mCamera.setDisplayOrientation(90);//旋转90度
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 设置摄像头
        Camera.Parameters parameters = mCamera.getParameters();
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_PICTURE);
        parameters.setPictureFormat(ImageFormat.JPEG);
        parameters.setPreviewSize(mPhotoSize.getHeight(), mPhotoSize.getWidth());
        parameters.setPictureSize(mPhotoSize.getHeight(), mPhotoSize.getWidth());
        parameters.setRotation(90);
        mCamera.setParameters(parameters);
        // 设置拍照按钮的监听器
        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 添加拍照的监听器
                mCamera.takePicture(null, null, new Camera.PictureCallback() {
                    // 拍照后数据的回调
                    @Override
                    public void onPictureTaken(byte[] data, Camera camera) {
                        savePhoto(data, camera);
                    }
                });
            }
        });
    }
    // 保存照片
    private void savePhoto(byte[] data, Camera camera) {
        // 将照片数据保存成图片格式的文件
        File photoFile = Util.creatFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "jpg");
        byte[] photoByte = Util.saveImage(data, photoFile, 90);
        // 通过行为判断该Activity是否是通过Intent对象隐形启动的
        Intent intent = getIntent();
        if (intent.getAction().equals("android.media.action.IMAGE_CAPTURE")||intent.getAction().equals("android.media.action.STILL_IMAGE_CAMERA")) {
            // 判断是否指定了照片保存路径的Uri
            Uri uri = intent.getParcelableExtra(MediaStore.EXTRA_OUTPUT);
            if (uri != null) {
                ContentResolver resolver = mContext.getContentResolver();
                try {
                    // 向Uri指定路径的文件写入照片数据
                    ParcelFileDescriptor descriptor = resolver.openFileDescriptor(uri, "rw");
                    FileOutputStream output = new FileOutputStream(descriptor.getFileDescriptor());
                    output.write(photoByte);
                    descriptor.close();
                    output.close();
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                setResult(RESULT_OK);
                finish();
            } else {
                // 设置照片压缩的参数
                BitmapFactory.Options options = new BitmapFactory.Options();
                options.inPreferredConfig = Bitmap.Config.RGB_565;
                options.inSampleSize = 16;
                // 压缩照片
                Bitmap bitmap = BitmapFactory.decodeFile(photoFile.getAbsolutePath(), options);
                // 返回RESULT_OK，并包含一个Intent对象，其中Extra中key为data，value是保存照片的bitmap对象。
                setResult(RESULT_OK, new Intent().putExtra("data", bitmap));
                finish();
            }
        } else {
            // 在系统相册中显示
            Util.showInAlbum(mContext, photoFile.getAbsolutePath());
            // 启动显示照片的Activity
            intent = new Intent(MainActivity.this, PreviewActivity.class);
            intent.putExtra("path", photoFile.getAbsolutePath());
            startActivity(intent);
        }
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