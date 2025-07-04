package com.vt.c0802;

import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.MediaController;
import android.widget.VideoView;

public class MainActivity extends AppCompatActivity {
    private static final int REQUEST_CODE_RECORD = 0;
    private static final int REQUEST_CODE_SELECT = 1;
    private Context mContext = this;
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0802:录制、选取和播放视频");
        // 判断是否已经获取权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);
        }else {
            setOnClickListener();
        }
    }
    private void setOnClickListener(){
        findViewById(R.id.button_record_video).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                recordVideo();
            }
        });
        findViewById(R.id.button_select_video).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                selectVideo();
            }
        });
    }
    // 调用系统相机录制视频
    public void recordVideo() {
        Intent intent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);
        intent.putExtra(MediaStore.EXTRA_VIDEO_QUALITY, 1);//设置视频质量（1为高画质）
        intent.putExtra(MediaStore.EXTRA_DURATION_LIMIT, 15);//设置最大时长为15秒
        startActivityForResult(intent, REQUEST_CODE_RECORD);
    }
    // 调用系统相册选择视频
    public void selectVideo() {
        Intent intent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Video.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(intent, REQUEST_CODE_SELECT);
    }
    // 权限请求的回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
                    Permissions.requestPermissions(mContext, PERMISSIONS);
                }else {
                    setOnClickListener();
                }
                break;
        }
    }
    // 回调播放录制的视频
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
        if ((requestCode == REQUEST_CODE_RECORD || requestCode == REQUEST_CODE_SELECT) && resultCode == RESULT_OK) {
            Uri videoUri = intent.getData();
            final VideoView videoView = findViewById(R.id.video_view);
            videoView.setVideoURI(videoUri);
            videoView.setMediaController(new MediaController(this));
            videoView.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mp) {
                    videoView.start();
                }
            });
        }
    }
}
