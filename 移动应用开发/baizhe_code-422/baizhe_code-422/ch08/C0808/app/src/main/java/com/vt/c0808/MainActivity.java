package com.vt.c0808;

import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.view.View;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import java.io.File;
import java.io.IOException;
import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, RadioGroup.OnCheckedChangeListener, Runnable {
    private Thread mTimerThread;//计时线程
    private long mBaseTimer = 0;//开始时的开机时间
    private long mPauseTimer = 0;//暂停时的开机时间
    private Handler mMainHandler = new Handler(Looper.getMainLooper());//用于线程中更新UI
    private int mAudioSource = MediaRecorder.AudioSource.DEFAULT;//音源模式
    private MediaRecorder mMediaRecorder = null;
    private TextView mTimeTextView;
    private RadioGroup mRadioGroup;
    private Button mStartButton;
    private Button mEndButton;
    private Button mPlayButton;
    private TextView mLogTextView;
    private boolean mIsStartRecording = false;//是否开始录制
    private boolean mIsPauseRecording = true;//是否暂停录制
    private File mAudioFile;//音频文件
    private static final String[] PERMISSIONS = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0808：MediaRecorder录音");
        init();
    }
    // 初始化
    private void init() {
        if (!Permissions.hasPermissionsGranted(this, PERMISSIONS)) {
            Permissions.requestPermissions(this, PERMISSIONS);
            return;
        }
        mTimeTextView =  findViewById(R.id.recoder_time_tv);
        mLogTextView = findViewById(R.id.log_tv);
        mStartButton = findViewById(R.id.start_btn);
        mEndButton = findViewById(R.id.end_btn);
        mPlayButton = findViewById(R.id.play_btn);
        mRadioGroup = findViewById(R.id.radio_group);

        mStartButton.setOnClickListener(this);
        mEndButton.setOnClickListener(this);
        mPlayButton.setOnClickListener(this);
        mRadioGroup.setOnCheckedChangeListener(this);
    }
    //点击监听事件
    @Override
    public void onClick(View v) {
        if (!Permissions.hasPermissionsGranted(this, PERMISSIONS)) {
            Permissions.requestPermissions(this, PERMISSIONS);
            return;
        }
        switch (v.getId()) {
            case R.id.start_btn:
                if(mIsPauseRecording){
                    startRecord();
                }else{
                    pauseRecord();
                }
                break;
            case R.id.end_btn:
                stopRecord();
                break;
            case R.id.play_btn:
                if(mAudioFile != null) {
                    play();
                }else{
                    Toast.makeText(this, "还没有录制音频文件", Toast.LENGTH_SHORT).show();
                }
                break;
        }
    }
    // 单选组选项改变监听事件
    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
        switch (checkedId) {
            case R.id.default_radio_button:
                mAudioSource = MediaRecorder.AudioSource.DEFAULT;
                break;
            case R.id.mic_radio_button:
                mAudioSource = MediaRecorder.AudioSource.MIC;
                break;
            case R.id.call_radio_button:
                mAudioSource = MediaRecorder.AudioSource.VOICE_CALL;
                break;
            case R.id.communication_radio_button:
                mAudioSource = MediaRecorder.AudioSource.VOICE_COMMUNICATION;
                break;
        }
    }
    // 开始录制
    private void startRecord(){
        try {
            if (!mIsStartRecording) {
                mAudioFile = Util.creatFile(this.getExternalFilesDir("audio").getAbsolutePath(), "", "amr");
                mLogTextView.setText(mAudioFile.getAbsolutePath());
                mMediaRecorder = new MediaRecorder();
                mMediaRecorder.setAudioSource(mAudioSource);//音频输入源
                mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.AMR_WB);//设置输出格式
                mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_WB);//设置编码格式
                mMediaRecorder.setOutputFile(mAudioFile.getAbsolutePath());//设置输出文件
                mMediaRecorder.prepare();//录制准备
                mIsStartRecording = true;
                mIsPauseRecording = false;
            }
            if (mIsPauseRecording) {
                mMediaRecorder.resume();//继续录音
                mIsPauseRecording = false;
            } else {
                mMediaRecorder.start();//开始录制
            }
            mStartButton.setText("暂停");
            //开启计时线程
            mTimerThread = new Thread(this);
            mTimerThread.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    // 暂停录制
    private void pauseRecord(){
        if(mMediaRecorder != null){
            mMediaRecorder.pause();//暂停录制
            mIsPauseRecording = true;
            mStartButton.setText("继续");
        }
    }
    // 停止录制
    private void stopRecord(){
        if(mMediaRecorder != null){
            mMediaRecorder.stop();//停止录制
            mMediaRecorder.release();
            mMediaRecorder = null;
            mIsStartRecording = false;
            mIsPauseRecording = true;
            mStartButton.setText("开始录制");
            Toast.makeText(this, "录音结束", Toast.LENGTH_SHORT).show();
        }
    }
    // 播放录音
    private void play(){
        try {
            Uri uri = Uri.fromFile(mAudioFile);
            MediaPlayer mediaPlayer = new MediaPlayer();
            mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
            mediaPlayer.setDataSource(getApplicationContext(), uri);
            mediaPlayer.prepare();
            mediaPlayer.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    // 请求权限回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(this, PERMISSIONS)) {
                    Permissions.requestPermissions(this, PERMISSIONS);
                }else{
                    init();
                }
                break;
        }
    }
    // 计时线程
    @Override
    public void run() {
        while (mIsStartRecording ) {
            if (!mIsPauseRecording) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                // 计算并更新计时
                mMainHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        // 获取计时开始时的开机时间
                        if (0 == mBaseTimer) {
                            mBaseTimer = SystemClock.elapsedRealtime();//系统开机到当前的时间
                        }
                        // 如果有暂停时间，则将暂停时间加到开始时间，相当于开始时间向后延。
                        if (mPauseTimer > 0) {
                            mBaseTimer = mBaseTimer + (SystemClock.elapsedRealtime() - mPauseTimer);
                            mPauseTimer = 0;
                        }
                        // 计算计时的小时、分钟、秒、毫秒
                        long time = SystemClock.elapsedRealtime() - mBaseTimer;
                        int second = (int) ((SystemClock.elapsedRealtime() - mBaseTimer) / 1000);
                        String millisecond = new DecimalFormat("00").format((time - second * 1000) / 10);
                        String hh = new DecimalFormat("00").format(second / 3600);
                        String mm = new DecimalFormat("00").format(second % 3600 / 60);
                        String ss = new DecimalFormat("00").format(second % 60);
                        // 更新显示计时的控件
                        if (null != MainActivity.this.mTimeTextView) {
                            mTimeTextView.setText(hh + ":" + mm + ":" + ss + ":" + millisecond);
                        }
                    }
                });
            }
            // 获取计时暂停时的开机时间
            if(mPauseTimer==0) {
                mPauseTimer = SystemClock.elapsedRealtime();
            }
        }
        // 暂停100毫秒等待UI更新完成
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        // 重置开始时间和暂停时间
        if(!mIsStartRecording){
            mBaseTimer = 0;
            mPauseTimer = 0;
        }
    }
}