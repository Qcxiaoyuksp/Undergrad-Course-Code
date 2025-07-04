package com.vt.c0811;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;
import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {
    private SensorManager mSensorManager;//传感器管理器
    private Sensor mLightSensor;
    private Sensor mPressureSensor;
    private TextView mLightTextView;
    private TextView mPressureTextView;
    private TextView mAltitudeTextView;
    private Window mWindow;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0811：光度计和气压计");
        mLightTextView = findViewById(R.id.light_text_view);
        mPressureTextView = findViewById(R.id.pressure_text_view);
        mAltitudeTextView = findViewById(R.id.altitude_text_view);
        init();
    }
    // 初始化
    private void init(){
        mWindow = this.getWindow();
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mLightSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);//光度传感器
        mPressureSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_PRESSURE);//气压传感器
        // 注册光度传感器
        mSensorManager.registerListener(new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent event) {
                float lux = event.values[0];//获取光照强度
                mLightTextView.setText(new DecimalFormat("#.00").format(lux));
                // 根据亮度调整屏幕亮度
                WindowManager.LayoutParams lp = mWindow.getAttributes();
                lp.screenBrightness = lux / 500;
                mWindow.setAttributes(lp);
            }
            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) { }
        }, mLightSensor, SensorManager.SENSOR_DELAY_NORMAL);
        // 注册气压传感器
        mSensorManager.registerListener(new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent event) {
                double pa = event.values[0];//获取大气压力
                mPressureTextView.setText(new DecimalFormat("#.00").format(pa));
                mAltitudeTextView.setText(new DecimalFormat("#.00").format(altitude(pa)));
            }
            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) { }
        }, mPressureSensor, SensorManager.SENSOR_DELAY_NORMAL);
    }
    // 通过气压计算海拔高度
    private double altitude(double pa){
        float p0 = 1013.21f;//海平面大气压
        return 44300*(1- Math.pow(pa/p0,1/5.256));
    }
}