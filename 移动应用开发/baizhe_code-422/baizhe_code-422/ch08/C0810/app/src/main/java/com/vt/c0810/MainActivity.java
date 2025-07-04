package com.vt.c0810;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private SensorManager mSensorManager;//传感器管理器
    private Sensor mAccelerometer;//加速度传感器
    private Sensor mMagnetic;//地磁场传感器
    private float[] mAccelerometerValues = new float[3];//加速度数据数组
    private float[] mMagneticFieldValues = new float[3];//地磁场数据数组
    private int mCurrentDegree = 0;//当前方位角
    private ImageView mPointerImageView;//指南针罗盘
    private TextView mOrientationTextView;//手机正前方水平方向
    private TextView mTextView1;//方位角
    private TextView mTextView2;//俯仰角
    private TextView mTextView3;//倾侧角
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0810：指南针");
        mPointerImageView = findViewById(R.id.pointer_image_view);
        mOrientationTextView = findViewById(R.id.orientation_text_view);
        mTextView1 = findViewById(R.id.text_view1);
        mTextView2 = findViewById(R.id.text_view2);
        mTextView3 = findViewById(R.id.text_view3);
        init();
    }
    // 初始化
    private void init(){
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);//实例化传感器管理者
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);//初始化加速度传感器
        mMagnetic = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);//初始化地磁场传感器
        calculateOrientation();//计算方向
    }
    @Override
    protected void onResume() {
        mSensorManager.registerListener(new OrientationSensorEventListener(), mAccelerometer,SensorManager.SENSOR_DELAY_NORMAL);
        mSensorManager.registerListener(new OrientationSensorEventListener(), mMagnetic, SensorManager.SENSOR_DELAY_NORMAL);
        super.onResume();
    }
    @Override
    protected void onPause() {
        mSensorManager.unregisterListener(new OrientationSensorEventListener());
        super.onPause();
    }
    // 计算方向
    private void calculateOrientation() {
        float[] R = new float[9];//旋转矩阵
        float[] values = new float[3];//方位数组
        SensorManager.getRotationMatrix(R, null, mAccelerometerValues, mMagneticFieldValues);//获取旋转矩阵
        SensorManager.getOrientation(R, values);//获取方位数组
        values[0] = (float) Math.toDegrees(values[0]);
        values[1] = (float) Math.toDegrees(values[1]);
        values[2] = (float) Math.toDegrees(values[2]);
        // 手机姿态
        mTextView1.setText("方位角：" + values[0]);
        mTextView2.setText("俯仰角：" + values[1]);
        mTextView3.setText("倾侧角：" + values[2]);
        // 手机正前方水平方向
        if (values[0] >= -5 && values[0] < 5) {
            mOrientationTextView.setText("正北");
        } else if (values[0] >= 5 && values[0] < 85) {
            mOrientationTextView.setText("东北");
        } else if (values[0] >= 85 && values[0] <= 95) {
            mOrientationTextView.setText("正东");
        } else if (values[0] >= 95 && values[0] < 175) {
            mOrientationTextView.setText("东南");
        } else if ((values[0] >= 175 && values[0] <= 180) || (values[0]) >= -180 && values[0] < -175) {
            mOrientationTextView.setText("正南");
        } else if (values[0] >= -175 && values[0] < -95) {
            mOrientationTextView.setText("西南");
        } else if (values[0] >= -95 && values[0] < -85) {
            mOrientationTextView.setText("正西");
        } else if (values[0] >= -85 && values[0] < -5) {
            mOrientationTextView.setText("西北");
        }
        // 转换指南针指针方向
        int degree = -(int)values[0];
        if (degree - mCurrentDegree > 180) {
            degree -= 360;
        } else if (degree - mCurrentDegree < -180) {
            degree += 360;
        }
        // 改变值大于2度改变指针方向
        if (Math.abs(degree - mCurrentDegree) > 2) {
            RotateAnimation ra = new RotateAnimation(mCurrentDegree, degree,
                    Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f);
            ra.setDuration(200);//旋转持续时间
            ra.setFillAfter(true);//旋转结束后停留
            mPointerImageView.startAnimation(ra);//开始旋转动画
            mCurrentDegree = degree;//更新当前指针角度
        }
    }
    // 传感器事件监听器
    class OrientationSensorEventListener implements SensorEventListener {
        @Override
        public void onSensorChanged(SensorEvent event) {
            if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                mAccelerometerValues = event.values;
            }
            if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
                mMagneticFieldValues = event.values;
            }
            calculateOrientation();
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) { }
    }
}