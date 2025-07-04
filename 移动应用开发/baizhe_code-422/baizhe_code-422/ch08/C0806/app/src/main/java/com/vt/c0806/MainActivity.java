package com.vt.c0806;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.FileProvider;
import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;
import android.util.Size;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private static final String TAG = "MainActivity";
    private HandlerThread mBackgroundThread;//后台线程
    private Handler mBackgroundHandler;//后台线程的句柄
    private static final int MAX_PREVIEW_WIDTH = 1080;//预览的最大宽度限制
    private static final int MAX_PREVIEW_HEIGHT = 1920;//预览的最大高度限制
    private final Context mContext = this;
    private PreviewTextureView mPreviewView;//预览拍摄画面
    private Button mButton;//录制按钮
    private CameraManager mCameraManager;//摄像头管理器
    private CameraDevice mCameraDevice;//摄像头设备
    private CameraCaptureSession mCaptureSession;//摄像头捕捉会话
    private CaptureRequest.Builder mCaptureRequestBuilder;
    private CaptureRequest mCaptureRequest;//捕捉图像请求
    private MediaRecorder mMediaRecorder;//媒体录制器
    private Size mPreviewSize = new Size(1080, 1920);//预览画面尺寸
    private Size mVideoSize;//录制画面尺寸
    private boolean mIsRecordingVideo;//是否在录制视频
    private File mVideoFile;//保存视频的文件
    private Semaphore mSemaphore = new Semaphore(1);//设置信号许可数量
    // 所需权限
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };
    // TextureView的生命周期事件
    private TextureView.SurfaceTextureListener mSurfaceTextureListener = new TextureView.SurfaceTextureListener() {
        @Override
        public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
            Log.d(TAG, "TextureView.onSurfaceTextureAvailable()");
            openCamera(width, height);
        }
        @Override
        public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height) { }
        @Override
        public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) { }
        @Override
        public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
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
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // 初始化
        this.setTitle("C0806：使用Camera2类录制视频");
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
    // 开启后台线程
    private void startBackgroundThread() {
        Log.d(TAG, "startBackgroundThread()");
        mBackgroundThread = new HandlerThread("CameraBackground");
        mBackgroundThread.start();
        mBackgroundHandler = new Handler(mBackgroundThread.getLooper());
    }
    // 停止后台线程
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
    @Override
    public void onClick(View v) {
        if (mIsRecordingVideo) {
            stopRecordingVideo(false);
        } else {
            startRecordingVideo();
        }
    }
    // 打开摄像头
    @SuppressWarnings("MissingPermission")
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
            mCameraManager = (CameraManager) mContext.getSystemService(Context.CAMERA_SERVICE);
            // 获取后置摄像头
            String cameraId = mCameraManager.getCameraIdList()[0];
            // 获取预览和录制视频的尺寸
            CameraCharacteristics characteristics = mCameraManager.getCameraCharacteristics(cameraId);
            StreamConfigurationMap map = characteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
            mVideoSize = Util.chooseVideoSize(map.getOutputSizes(MediaRecorder.class));
            mPreviewSize = Util.chooseOptimalSize(mContext, map.getOutputSizes(SurfaceTexture.class), width, height, MAX_PREVIEW_WIDTH, MAX_PREVIEW_HEIGHT, mVideoSize);
            mPreviewView.setAspectRatio(mPreviewSize.getHeight(), mPreviewSize.getWidth());
            mMediaRecorder = new MediaRecorder();
            mCameraManager.openCamera(cameraId, mCameraDeviceStateCallback, mBackgroundHandler);
        } catch (CameraAccessException e) {
            Toast.makeText(mContext, "摄像头不可用", Toast.LENGTH_LONG).show();
        } catch (InterruptedException e) {
            throw new RuntimeException("打开摄像头被中断", e);
        }
    }
    // 设置录制参数
    private void setUpMediaRecorder() throws IOException {
        Log.d(TAG, "setUpMediaRecorder()");
        mVideoFile = Util.creatFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "mp4");
        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.SURFACE);
        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        mMediaRecorder.setOutputFile(mVideoFile.getAbsolutePath());
        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        mMediaRecorder.setVideoEncodingBitRate(8 * mVideoSize.getWidth() * mVideoSize.getHeight());
        mMediaRecorder.setVideoFrameRate(30);
        mMediaRecorder.setVideoSize(mVideoSize.getWidth(), mVideoSize.getHeight());
        mMediaRecorder.setOrientationHint(90);//设置视频的角度
        mMediaRecorder.setOnErrorListener(new MediaRecorder.OnErrorListener() {
            @Override
            public void onError(MediaRecorder mr, int what, int extra) {
                stopRecordingVideo(true);
            }
        });
        mMediaRecorder.prepare();
    }
    // 开始预览
    private void startPreview() {
        Log.d(TAG, "startPreview()");
        if (null == mCameraDevice || !mPreviewView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreview();
            // 设置预览的缓冲区大小
            SurfaceTexture texture = mPreviewView.getSurfaceTexture();
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            // 设置预览输出的Surface
            Surface previewSurface = new Surface(texture);
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            mCaptureRequestBuilder.addTarget(previewSurface);
            // 创建摄像头的捕获会话
            mCameraDevice.createCaptureSession(Collections.singletonList(previewSurface), new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    mCaptureSession = session;
                    updatePreview();
                }
                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                    Toast.makeText(mContext, "摄像头配置失败", Toast.LENGTH_LONG).show();
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
    // 开始录制视频
    private void startRecordingVideo() {
        Log.d(TAG, "startRecordingVideo()");
        if (null == mCameraDevice || !mPreviewView.isAvailable() || null == mPreviewSize) {
            return;
        }
        try {
            closePreview();
            setUpMediaRecorder();
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_RECORD);
            // 设置预览的缓冲区大小
            SurfaceTexture texture = mPreviewView.getSurfaceTexture();
            texture.setDefaultBufferSize(mPreviewSize.getWidth(), mPreviewSize.getHeight());
            // 设置预览的Surface
            List<Surface> surfaces = new ArrayList<>();
            Surface previewSurface = new Surface(texture);
            surfaces.add(previewSurface);
            mCaptureRequestBuilder.addTarget(previewSurface);
            // 设置录制视频的Surface
            Surface recorderSurface = mMediaRecorder.getSurface();
            surfaces.add(recorderSurface);
            mCaptureRequestBuilder.addTarget(recorderSurface);
            // 创建捕捉会话
            mCameraDevice.createCaptureSession(surfaces, new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    mCaptureSession = session;
                    updatePreview();
                    ((Activity) mContext).runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            mButton.setText("停止");
                            mIsRecordingVideo = true;
                            mMediaRecorder.start();
                        }
                    });
                }
                @Override
                public void onConfigureFailed(CameraCaptureSession cameraCaptureSession) {
                    Toast.makeText(mContext, "摄像头配置失败", Toast.LENGTH_LONG).show();
                }
            }, mBackgroundHandler);
        } catch (CameraAccessException | IOException e) {
            e.printStackTrace();
        }
    }
    // 停止录制视频
    private void stopRecordingVideo(boolean error) {
        mMediaRecorder.stop();
        mMediaRecorder.reset();
        mIsRecordingVideo = false;
        mButton.setText("录制");
        startPreview();
        if (error) {//如果因为错误停止，则直接返回不进行后续处理。
            return;
        }
        Util.showInAlbum(mContext, mVideoFile.getAbsolutePath());
        Uri videoUri = FileProvider.getUriForFile(this, "com.vt.c0806.fileprovider", mVideoFile);
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
    // 更新预览
    private void updatePreview() {
        try {
            // 设置自动对焦
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
            // 显示预览
            mCaptureRequest = mCaptureRequestBuilder.build();
            HandlerThread thread = new HandlerThread("CameraPreview");
            thread.start();
            // 捕捉图像会话设置重复请求
            mCaptureSession.setRepeatingRequest(mCaptureRequest, null, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }
    // 关闭预览会话
    private void closePreview() {
        if (mCaptureSession != null) {
            mCaptureSession.close();
            mCaptureSession = null;
        }
    }
    // 关闭摄像头
    private void closeCamera() {
        closePreview();
        if (null != mCaptureSession) {
            mCaptureSession.close();
            mCaptureSession = null;
        }
        if (null != mCameraDevice) {
            mCameraDevice.close();
            mCameraDevice = null;
        }
        if (null != mMediaRecorder) {
            mMediaRecorder.release();
            mMediaRecorder = null;
        }
        mSemaphore.release();//释放1个信号许可
    }
    // 请求权限回调
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