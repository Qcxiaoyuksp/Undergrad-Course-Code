package com.vt.c0905;

import android.Manifest;
import android.app.Activity;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import androidx.appcompat.app.AppCompatActivity;

public class DailyAddActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "DailyAddActivity";
    private static final int MSG_HTTP_SUCCESS = 1;
    private static final int MSG_HTTP_FAILURE = 2;
    private static final int MSG_THUMNAIL_FINISH = 3;

    private String cacheDir;//缓存文件夹路径
    private Context mContext = this;
    private EditText mNameEditText;//昵称
    private EditText mContentEditText;//内容
    private ImageView[] mImageView;//图片
    private Button mSendButton;//发布按钮
    private String[] mImagePath;//图片路径
    private Uri[] mImageUri;//图片路径
    private Bitmap[] mImageThumbnail;//图片缩略图
    private int[] mImageDegrees;//图片组旋转角度
    private int i;//当前选择ImageView序号
    private HttpPostThread mHttpPostThread;
    private ProgressDialog pd;//进度对话框
    private static final String[] PERMISSIONS = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_daily_add);
        this.setTitle("发布动态");
        cacheDir = getExternalCacheDir().getAbsolutePath() + "/image/";
        // 设置图片数量
        int count = 1;
        mImageView = new ImageView[count];
        mImagePath = new String[count];
        mImageUri = new Uri[count];
        mImageThumbnail = new Bitmap[count];
        mImageDegrees = new int[count];
        // 初始化控件
        mNameEditText = findViewById(R.id.name_edit_text);
        mContentEditText = findViewById(R.id.content_edit_text);
        mImageView[0] = findViewById(R.id.image_view);
        mImageView[0].setOnClickListener(this);
        mSendButton = findViewById(R.id.send_button);
        mSendButton.setOnClickListener(this);
        // 判断权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);//请求权限
        }
    }
    // 请求权限的回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
                    Permissions.requestPermissions(mContext, PERMISSIONS);
                }
                break;
        }
    }
    // 点击事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.image_view://选取图片
                i = 0;
                Intent intent = new Intent(Intent.ACTION_PICK);
                intent.setType("image/*");
                startActivityForResult(intent, RESULT_CANCELED);
                break;
            case R.id.send_button://发布动态
                if (!mNameEditText.getText().toString().equals("")&&!mContentEditText.getText().toString().equals("")) {
                    // 设置上传地址
                    String url = "http://www.weiju2014.com/teachol/android/DailyAdd.php";
                    // post参数
                    Map<String, String> params = new HashMap<>();
                    params.put("name", mNameEditText.getText().toString());
                    params.put("content", mContentEditText.getText().toString());
                    // 将选择的图片存放在数组
                    ArrayList<String> selectFilePath = new ArrayList<>();
                    for (String path : mImagePath) {
                        if (!path.equals("null")) {
                            selectFilePath.add(path);
                        }
                    }
                    String[] uploadFilePath = new String[selectFilePath.size()];
                    selectFilePath.toArray(uploadFilePath);
                    // post上传
                    pd = ProgressDialog.show(mContext, "", "正在发布中……", false, false);
                    mHttpPostThread = new HttpPostThread();
                    mHttpPostThread.url = url;
                    mHttpPostThread.params = params;
                    mHttpPostThread.filePath = uploadFilePath;
                    mHttpPostThread.start();
                    // 关闭软键盘
                    ((InputMethodManager) getSystemService(INPUT_METHOD_SERVICE))
                            .hideSoftInputFromWindow(DailyAddActivity.this.getCurrentFocus()
                                    .getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                } else {
                    Toast.makeText(this, "亲，写点什么吧!", Toast.LENGTH_SHORT).show();
                }
                break;
        }
    }
    // 回调
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == Activity.RESULT_OK) {
            Uri uri = data.getData();
            Log.d(TAG, "uri：" + uri);
            // 启动生成缩略图进程
            ThumbnailThread thumbnailThread = new ThumbnailThread(uri);
            thumbnailThread.start();
        }
    }
    // 生成的缩略图
    public class ThumbnailThread extends Thread {
        Uri uri;//原始图片的URI
        ThumbnailThread(Uri uri){
            this.uri = uri;
        }
        @Override
        public void run() {
            // 创建消息循环
            Looper.prepare();
            try {
                // 将URI转为绝对路径
                ContentResolver cr = mContext.getContentResolver();
                String path = Util.UriToString(cr, uri);
                Log.e(TAG, path);
                // 判断扩展名
                if (path.endsWith("JPEG") || path.endsWith("jpeg") || path.endsWith("JPG") || path.endsWith("jpg") || path.endsWith("PNG") || path.endsWith("png")) {
                    // 压缩图片
                    CompressImage ci = new CompressImage(cacheDir, 50 * 1024);
                    mImageThumbnail[i] = ci.compress(path);
                    mImageDegrees[i] = Util.getImageOrientation(mContext, uri);
                    mImageThumbnail[i] = Util.rotateBitmapByDegree(mImageThumbnail[i], mImageDegrees[i]);
                    mImagePath[i] = path;
                    mImageUri[i] = uri;
                    // 更新UI
                    mHandler.obtainMessage(MSG_THUMNAIL_FINISH).sendToTarget();
                } else {
                    Log.d(TAG, "格式错误" + uri);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            Looper.loop();
        }
    }
    // 上传动态数据进程
    public class HttpPostThread extends Thread {
        private String url;
        private Map<String, String> params;
        private String[] filePath;
        @Override
        public void run() {
            // 压缩并缓存图片
            File cacheFile;//缓存文件
            Map<String, File> postFiles = new HashMap<>();//上传图片文件
            for (int i = 0; i < filePath.length; i++) {
                // 对大图片进行压缩和旋转
                ContentResolver cr = mContext.getContentResolver();
                CompressImage ci = new CompressImage(cacheDir, 500 * 1024);
                String path = Util.UriToString(cr, mImageUri[i]);
                Bitmap bitmap = ci.compress(path);
                bitmap = Util.rotateBitmapByDegree(bitmap, mImageDegrees[i]);
                cacheFile = Util.saveCacheBitmap(cacheDir,"IMG" + i + ".jpg", bitmap);
                // 添加上传图片文件
                postFiles.put(cacheFile.getName(), cacheFile);
            }
            // post方式上传
            try {
                if (!Http.post(url, postFiles, params).equals(Http.FAILURE)) {
                    mHandler.obtainMessage(MSG_HTTP_SUCCESS).sendToTarget();
                } else {
                    mHandler.obtainMessage(MSG_HTTP_FAILURE).sendToTarget();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    // 处理UI
    private Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_HTTP_SUCCESS://发布成功
                    pd.dismiss();
                    Toast.makeText(mContext, "发布成功", Toast.LENGTH_LONG).show();
                    ((Activity) mContext).finish();
                    break;
                case MSG_HTTP_FAILURE://发布失败
                    pd.dismiss();
                    Toast.makeText(mContext, "发布失败!", Toast.LENGTH_SHORT).show();
                    break;
                case MSG_THUMNAIL_FINISH://生成完缩略图
                    mImageView[i].setImageBitmap(mImageThumbnail[i]);
                    break;
            }
        }
    };
    // 点击空白区域隐藏虚拟键盘
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        ((InputMethodManager) getSystemService(INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(DailyAddActivity.this.getCurrentFocus()
                        .getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
        return true;
    }
}