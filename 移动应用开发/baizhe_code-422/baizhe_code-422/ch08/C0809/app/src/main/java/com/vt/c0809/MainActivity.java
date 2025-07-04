package com.vt.c0809;

import androidx.appcompat.app.AppCompatActivity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, SensorEventListener, Runnable {
    private Thread mTimerThread;//计时线程
    private Handler mMainHandler = new Handler(Looper.getMainLooper());//用于线程中更新UI
    private SensorManager mSensorManager;
    private Sensor mSensor;
    private int mCount = 0;//摇动次数
    private int mStopCount = 2;//停止的摇动次数
    private double mMotionRange = 5;//摇晃幅度范围
    private double mLastValue = 0;//上次的模
    private double mCurrentValue = 0;//当前的模
    private boolean mMaxState = true;//是否处于摇晃峰值状态
    private boolean mIsStart = false;//是否开始
    private TextView mNumTextView;
    private Button mStartButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0809：摇一摇 比大小");
        mNumTextView = findViewById(R.id.num_text_view);
        mStartButton = findViewById(R.id.start_button);
        mStartButton.setOnClickListener(this);
        init();
    }
    // 初始化传感器
    private void init(){
        mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);//实例化传感器管理者
        mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);//初始化加速度传感器
        mSensorManager.registerListener(this, mSensor, SensorManager.SENSOR_DELAY_UI);//注册传感器监听器
    }
    @Override
    public void onClick(View v) {
        mNumTextView.setText("0");
        if (mIsStart == true) {
            mStartButton.setText("开始");
            mIsStart = false;
        } else {
            mStartButton.setText("停止");
            mIsStart = true;
            //开启计时线程
            mTimerThread = new Thread(this);
            mTimerThread.start();
        }
    }
    @Override
    public void onSensorChanged(SensorEvent event) {
        if (mIsStart == false) {
            return;
        }
        float[] value = event.values;
        mCurrentValue = getMod(value[0], value[1], value[2]);
        // 监测正向峰值
        if (mMaxState == false) {
            if (mCurrentValue >= mLastValue) {
                mLastValue = mCurrentValue;
            } else {
                if (Math.abs(mCurrentValue - mLastValue) > mMotionRange) {
                    mMaxState = true;
                }
            }
        }
        // 监测反向峰值
        if (mMaxState == true) {
            if (mCurrentValue <= mLastValue) {
                mLastValue = mCurrentValue;
            } else {
                if (Math.abs(mCurrentValue - mLastValue) > mMotionRange) {
                    mCount++;
                    mMaxState = false;
                }
            }
        }
    }
    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) { }
    // 向量求模
    public double getMod(float x, float y, float z) {
        return Math.sqrt(x * x + y * y + z * z);
    }
    @Override
    public void run() {
        // 达到摇晃次数结束循环
        while (mCount < mStopCount) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(!mIsStart){
                return;
            }
        }
        // 摇晃结束
        mMainHandler.post(new Runnable() {
            @Override
            public void run() {
                mCount = 0;
                mIsStart = false;
                mStartButton.setText("开始");
                mNumTextView.setText(String.valueOf((int) (Math.random() * 10)));
            }
        });
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        mSensorManager.unregisterListener(this);
    }
}