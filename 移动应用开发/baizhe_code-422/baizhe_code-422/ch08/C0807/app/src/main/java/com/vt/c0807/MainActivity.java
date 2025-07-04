package com.vt.c0807;

import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.content.Context;
import android.media.AudioAttributes;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.view.View;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, RadioGroup.OnCheckedChangeListener, Runnable  {
    private Context mContext = this;
    private ThreadPoolExecutor mExecutor = new ThreadPoolExecutor(3, 5, 60, TimeUnit.SECONDS, new LinkedBlockingQueue<Runnable>());//任务线程池
    private Thread mTimerThread;//计时线程
    private long mBaseTimer = 0;//开始时的开机时间
    private long mPauseTimer = 0;//暂停时的开机时间
    private Handler mMainHandler = new Handler(Looper.getMainLooper());//用于线程中更新UI
    private int mAudioSource = MediaRecorder.AudioSource.DEFAULT;//音源模式
    private AudioTrack mAudioTrack;//音频轨道
    private AudioRecord mAudioRecord;//音频录制
    private int mBufferSize;//录制缓冲区尺寸
    private byte[] mAudioData;//音频流数据
    private int mInSampleRate = 44100;//输入采样率
    private int mInAudioFormat = AudioFormat.ENCODING_PCM_16BIT;//输入编码位数
    private int mInChannelConfig = AudioFormat.CHANNEL_IN_STEREO;//输入声道数量
    private int mOutSampleRate = 44100; //输出采样率
    private int mOutAudioFormat = AudioFormat.ENCODING_PCM_16BIT;//输出编码位数
    private int mOutChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;//输出声道数量
    private boolean mIsStartRecording = false;//是否开始录制
    private boolean mIsPauseRecording = false;//是否暂停录制
    private File mPCMFile;//PCM文件
    private File mWAVFile;//WAV文件
    private TextView mTimeTextView;
    private TextView mLogTextView;
    private Button mStartButton;
    private Button mEndButton;
    private Button mPlayButton;
    private RadioGroup mRadioGroup;
    private static final String[] PERMISSIONS = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0807：AudioRecord录音");
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
        mPlayButton.setEnabled(false);
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
    // 点击监听
    @Override
    public void onClick(View v) {
        if (!Permissions.hasPermissionsGranted(this, PERMISSIONS)) {
            Permissions.requestPermissions(this, PERMISSIONS);
            return;
        }
        switch (v.getId()) {
            case R.id.start_btn:
                if(mIsStartRecording){
                    if (mIsPauseRecording) {
                        continueRecord();
                    } else {
                        pauseRecord();
                    }
                }else{
                    startRecording();
                }
                break;
            case R.id.end_btn:
                stopRecord();
                break;
            case R.id.play_btn:
                if(mWAVFile != null) {
                    createAudioTrack();
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
    // 开始录音
    void startRecording() {
        mIsStartRecording = true;
        mIsPauseRecording = false;
        mPlayButton.setEnabled(false);
        mStartButton.setText("暂停");
        mPCMFile = Util.creatFile(this.getExternalFilesDir("audio").getAbsolutePath(), "", "pcm");
        mWAVFile = Util.creatFile(this.getExternalFilesDir("audio").getAbsolutePath(), "", "wav");
        mLogTextView.setText(mPCMFile.getAbsolutePath());
        mBufferSize = AudioRecord.getMinBufferSize(mInSampleRate, mInChannelConfig, mInAudioFormat);
        mAudioData = new byte[mBufferSize];
        mAudioRecord = new AudioRecord(mAudioSource, mInSampleRate, mInChannelConfig, mInAudioFormat, mBufferSize);
        // 开始录音（此后能够读取音频数据）
        mAudioRecord.startRecording();
        // 开启计时线程
        mTimerThread = new Thread(this);
        mTimerThread.start();
        // 录制音频的线程
        mExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    FileOutputStream outputStream = new FileOutputStream(mPCMFile.getAbsoluteFile());
                    // 开始录制时循环
                    while (mIsStartRecording) {
                        // 暂停时循环
                        while (mIsStartRecording&&mIsPauseRecording) {
                            try {
                                Thread.sleep(100);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                        mAudioRecord.read(mAudioData, 0, mAudioData.length);
                        outputStream.write(mAudioData);
                    }
                    outputStream.close();
                    // 将PCM文件转为WAV文件
                    Util.pcmToWave(mPCMFile.getAbsolutePath(), mWAVFile.getAbsolutePath(), mInSampleRate, mBufferSize);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
    // 暂停录音
    void pauseRecord() {
        mAudioRecord.stop();
        mIsPauseRecording = true;
        mStartButton.setText("继续");
    }
    // 继续录音
    void continueRecord() {
        mAudioRecord.startRecording();
        mIsPauseRecording = false;
        mStartButton.setText("暂停");
    }
    // 停止录音
    void stopRecord() {
        mAudioRecord.stop();
        mIsStartRecording = false;
        mIsPauseRecording = true;
        mStartButton.setText("开始录音");
        Toast.makeText(this, "录音已结束", Toast.LENGTH_SHORT).show();
        mPlayButton.setEnabled(true);
    }
    // 创建音轨
    public void createAudioTrack() throws IllegalStateException {
        int mBufferSizeInBytes = AudioTrack.getMinBufferSize(mOutSampleRate, mOutChannelConfig, mOutAudioFormat);
        if (mBufferSizeInBytes <= 0) {
            throw new IllegalStateException("最小缓冲区尺寸：" + mBufferSizeInBytes);
        }
        // 判断当前版本是否大于等于Android M（API level 23）
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            mAudioTrack = new AudioTrack.Builder()
                    .setAudioAttributes(new AudioAttributes.Builder()
                            .setUsage(AudioAttributes.USAGE_MEDIA)
                            .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                            .setLegacyStreamType(AudioManager.STREAM_MUSIC)
                            .build())
                    .setAudioFormat(new AudioFormat.Builder()
                            .setEncoding(mInAudioFormat)
                            .setSampleRate(mInSampleRate)
                            .setChannelMask(mInChannelConfig)
                            .build())
                    .setTransferMode(AudioTrack.MODE_STREAM)
                    .setBufferSizeInBytes(mBufferSizeInBytes)
                    .build();
        } else {
            mAudioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, mOutSampleRate, mOutChannelConfig, mOutAudioFormat,
                    mBufferSizeInBytes, AudioTrack.MODE_STREAM);
        }
        mAudioTrack.setVolume(1.0f);
    }
    // 播放录音
    public void play() throws IllegalStateException {
        mExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    playAudioData(mWAVFile);
                } catch (IOException e) {
                    mMainHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(mContext, "录音播放出现错误", Toast.LENGTH_SHORT).show();
                        }
                    });
                }
            }
        });
    }
    // 播放音频数据
    private void playAudioData(File audioFile) throws IOException {
        FileInputStream fis = new FileInputStream(audioFile);
        DataInputStream dis = new DataInputStream(new BufferedInputStream(fis));
        byte[] bytes = new byte[mInSampleRate];
        int len;
        mAudioTrack.play();//播放音轨（此时不会播放出声音）
        while ((len = dis.read(bytes)) != -1) {
            mAudioTrack.write(bytes, 0, len);//写入音轨播放音频
        }
        mMainHandler.post(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(mContext, "录音播放完毕", Toast.LENGTH_SHORT).show();
            }
        });
        if (dis != null) {
            dis.close();//关闭释放资源
        }
    }
    // 计时线程
    @Override
    public void run() {
        while (mIsStartRecording) {
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
            mIsPauseRecording = true;
            mBaseTimer = 0;
            mPauseTimer = 0;
        }
    }
}