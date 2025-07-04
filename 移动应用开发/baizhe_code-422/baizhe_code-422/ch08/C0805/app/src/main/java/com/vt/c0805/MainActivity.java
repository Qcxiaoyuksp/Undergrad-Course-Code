package com.vt.c0805;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.ImageReader;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.util.Log;
import android.util.Size;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "MainActivity";
    private static final int MAX_PREVIEW_WIDTH = 1080;//预览的最大宽度限制
    private static final int MAX_PREVIEW_HEIGHT = 1920;//预览的最大高度限制
    private final Context mContext = this;
    private Size mPreviewSize;//预览尺寸
    private PreviewTextureView mPreviewView;//预览摄像头画面的控件
    private Button mButton;//拍照按钮
    private Semaphore mSemaphore = new Semaphore(1);//设置信号许可数量
    private HandlerThread mBackgroundThread;//后台线程
    private Handler mBackgroundHandler;//后台线程的句柄
    private String mCameraId = "0";//摄像头id
    private CameraManager mCameraManager;//摄像头管理器
    private CameraCaptureSession mCaptureSession;//摄像头捕捉会话
    private CameraDevice mCameraDevice;//摄像头设备
    private CaptureRequest.Builder mCaptureRequestBuilder;//捕捉图像请求构建器
    private CaptureRequest mCaptureRequest;//捕捉图像请求
    private ImageReader mImageReader;//捕获图片的读取器
    private File mPhotoFile;//保存图片的文件
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };
    // TextureView的生命周期事件
    private TextureView.SurfaceTextureListener mSurfaceTextureListener = new TextureView.SurfaceTextureListener() {
        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture texture, int width, int height) {
            Log.d(TAG, "TextureView.onSurfaceTextureAvailable()");
            openCamera(width, height);
        }
        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture texture, int width, int height) { }
        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture texture) { }
        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture texture) {
            return true;
        }
    };
    // 摄像头设备状态的回调
    private CameraDevice.StateCallback mCameraDeviceStateCallback = new CameraDevice.StateCallback() {
        @Override
        public void onOpened(@NonNull CameraDevice cameraDevice) {
            Log.d(TAG, "CameraDevice.onOpened()");
            mCameraDevice = cameraDevice;
            startPreview();
            mSemaphore.release();//释放1个信号许可
        }
        @Override
        public void onDisconnected(@NonNull CameraDevice cameraDevice) {
            Log.d(TAG, "CameraDevice.onDisconnected()");
            mSemaphore.release();//释放1个信号许可
            cameraDevice.close();
            mCameraDevice = null;
        }
        @Override
        public void onError(@NonNull CameraDevice cameraDevice, int error) {
            Log.d(TAG, "CameraDevice.onError()");
            mSemaphore.release();//释放1个信号许可
            cameraDevice.close();
            mCameraDevice = null;
        }
    };
    // ImageReader的监听器
    private ImageReader.OnImageAvailableListener mOnImageAvailableListener = new ImageReader.OnImageAvailableListener() {
        @Override
        public void onImageAvailable(final ImageReader reader) {
            Log.d(TAG, "ImageReader.onImageAvailable()");
            // 解除mImageReader的监听器
            mImageReader.setOnImageAvailableListener(null, null);
            // ImageReader读取到图像后使用新线程处理图像数据
            ((Activity) mContext).runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    handlePhoto(reader);
                }
            });
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // 初始化
        this.setTitle("C0805：使用Camera2类拍摄照片");
        mPreviewView = findViewById(R.id.texture_view);
        mButton = findViewById(R.id.button);
        mButton.setOnClickListener(this);
    }
    @Override
    public void onResume() {
        super.onResume();
        startBackgroundThread();
        // 预览显示时打开摄像头，否则通过监听器监测打开摄像头。
        if (mPreviewView.isAvailable()) {
            openCamera(mPreviewView.getWidth(), mPreviewView.getHeight());
        } else {
            mPreviewView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }
    @Override
    public void onPause() {
        closeCamera();
        stopBackgroundThread();
        super.onPause();
    }
    //开启后台线程
    private void startBackgroundThread() {
        Log.d(TAG, "startBackgroundThread()");
        mBackgroundThread = new HandlerThread("CameraBackground");
        mBackgroundThread.start();
        mBackgroundHandler = new Handler(mBackgroundThread.getLooper());
    }
    //停止后台线程
    private void stopBackgroundThread() {
        Log.d(TAG, "stopBackgroundThread()");
        mBackgroundThread.quitSafely();
        try {
            mBackgroundThread.join();
            mBackgroundThread = null;
            mBackgroundHandler = null;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    //点击事件
    @Override
    public void onClick(View view) {
        takePhoto();
    }
    // 打开摄像头
    @SuppressLint("MissingPermission")
    private void openCamera(int width, int height) {
        Log.d(TAG, "openCamera()");
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);
            return;
        }
        try {
            // 2500毫秒内请求获取1个许可，否则抛出异常。
            if (!mSemaphore.tryAcquire(2500, TimeUnit.MILLISECONDS)) {
                throw new RuntimeException("打开摄像头超时");
            }
            mCameraManager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
            // 获取摄像头支持的属性特征
            CameraCharacteristics characteristics = mCameraManager.getCameraCharacteristics(mCameraId);
            // 获取摄像头支持的可用流配置，包括每种格式、大小组合的最小帧持续时间和停顿持续时间。
            StreamConfigurationMap map = characteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
            // 获取摄像头捕捉的最大尺寸读取图片
            Size largest = Collections.max(Arrays.asList(map.getOutputSizes(ImageFormat.JPEG)), new Util.CompareSizesByArea());
            mImageReader = ImageReader.newInstance(largest.getWidth(), largest.getHeight(), ImageFormat.JPEG, 2);
            // 选择最佳预览尺寸
            mPreviewSize = Util.chooseOptimalSize(mContext, map.getOutputSizes(SurfaceTexture.class), width, height, MAX_PREVIEW_WIDTH, MAX_PREVIEW_HEIGHT, largest);
            // 设置预览尺寸
            mPreviewView.setAspectRatio(mPreviewSize.getHeight(), mPreviewSize.getWidth());
            //打开摄像头
            mCameraManager.openCamera(mCameraId, mCameraDeviceStateCallback, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            throw new RuntimeException("打开摄像头被中断", e);
        }
    }
    // 创建摄像头预览会话
    private void startPreview() {
        Log.d(TAG, "startPreview()");
        if (null == mCameraDevice || !mPreviewView.isAvailable() || null == mPreviewSize) { return; }
        try {
            closePreview();
            // 设置预览的缓冲区大小
            SurfaceTexture texture = mPreviewView.getSurfaceTexture();
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            // 设置预览输出的Surface
            Surface surface = new Surface(texture);
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            mCaptureRequestBuilder.addTarget(surface);
            // 创建摄像头的捕获会话
            mCameraDevice.createCaptureSession(Arrays.asList(surface, mImageReader.getSurface()), new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(CameraCaptureSession cameraCaptureSession) {
                    mCaptureSession = cameraCaptureSession;
                    updatePreview();
                }
                @Override
                public void onConfigureFailed(CameraCaptureSession cameraCaptureSession) {
                    Toast.makeText(mContext, "摄像头配置失败", Toast.LENGTH_LONG).show();
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
    // 拍照
    private void takePhoto() {
        Log.d(TAG, "takePhoto()");
        if (null == mCameraDevice || !mPreviewView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreview();
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
            // 设置预览的缓冲区大小
            SurfaceTexture texture = mPreviewView.getSurfaceTexture();
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            // 设置预览的Surface
            List<Surface> surfaces = new ArrayList<>();
            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
            mCaptureRequestBuilder.addTarget(previewSurface);
            // 设置拍照的Surface
            Surface imageReaderSurface = mImageReader.getSurface();
            surfaces.add(imageReaderSurface);
            mCaptureRequestBuilder.addTarget(imageReaderSurface);
            // 创建捕捉会话
            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession cameraCaptureSession) {
                    Log.d(TAG, "CameraCaptureSession.onConfigured()");
                    mCaptureSession = cameraCaptureSession;
                    // 添加ImageReader监听器处理拍摄照片
                    mImageReader.setOnImageAvailableListener(mOnImageAvailableListener, mBackgroundHandler);
                    mCaptureRequest = mCaptureRequestBuilder.build();
                    try {// 拍摄照片
                        mCaptureSession.capture(mCaptureRequest, null, null);
                    } catch (CameraAccessException e) {
                        e.printStackTrace();
                    }
                }
                @Override
                public void onConfigureFailed(CameraCaptureSession cameraCaptureSession) {
                    Toast.makeText(mContext, "摄像头配置失败", Toast.LENGTH_LONG).show();
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
    // 处理拍摄的照片
    private void handlePhoto(ImageReader reader){
        Log.d(TAG, "handlePhoto()");
        byte[] photoByte = Util.imageToBytes(reader.acquireNextImage());
        mPhotoFile = Util.creatFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "jpg");
        // 保存拍摄的照片
        photoByte = Util.saveImage(photoByte, mPhotoFile, 90);
        // 将拍摄的照片显示在系统相册内
        Util.showInAlbum(mContext, mPhotoFile.getAbsolutePath());
        // 恢复预览
        startPreview();
        // 获取启动该Activity的Intent
        Intent intent = getIntent();
        // 判断是否是通过外部APP隐式启动
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
                Bitmap bitmap = BitmapFactory.decodeFile(mPhotoFile.getAbsolutePath(), options);
                // 返回RESULT_OK，并包含一个Intent对象，其中Extra中key为data，value是保存照片的bitmap对象。
                setResult(RESULT_OK, new Intent().putExtra("data", bitmap));
                finish();
            }
        } else {
            // 启动预览照片的Activity
            intent = new Intent(MainActivity.this, PreviewActivity.class);
            intent.putExtra("path", mPhotoFile.getAbsolutePath());
            startActivity(intent);
        }
    }
    //更新预览
    private void updatePreview() {
        try {
            // 设置自动对焦
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AF_MODE, CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE);
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
            // 显示预览
            mCaptureRequest = mCaptureRequestBuilder.build();
            // 捕捉图像会话设置重复请求
            mCaptureSession.setRepeatingRequest(mCaptureRequest, null, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
    //关闭预览会话
    private void closePreview() {
        if (mCaptureSession != null) {
            mCaptureSession.close();
            mCaptureSession = null;
        }
    }
    //关闭摄像头
    private void closeCamera() {
        Log.d(TAG, "closeCamera()");
        if (null != mCaptureSession) {
            mCaptureSession.close();
            mCaptureSession = null;
        }
        if (null != mCameraDevice) {
            mCameraDevice.close();
            mCameraDevice = null;
        }
        if (null != mImageReader) {
            mImageReader.close();
            mImageReader = null;
        }
        mSemaphore.release();// 释放1个信号许可
    }
    //请求权限回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        Log.d(TAG, "onRequestPermissionsResult()");
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
                    Permissions.requestPermissions(mContext, PERMISSIONS);
                }
                break;
        }
    }
}