package com.vt.c0812;

import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Settings;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements RadioGroup.OnCheckedChangeListener {
    private Context mContext = this;
    private LocationManager mLocationManager;//定位管理
    private Location mLocation;//定位
    private RadioGroup mRadioGroup;//定位模式选择
    private TextView mLocationTextView;//定位信息
    private static final String[] PERMISSIONS = {
            Manifest.permission.ACCESS_FINE_LOCATION
    };
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0812：定位服务");
        // 判断权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            Permissions.requestPermissions(mContext, PERMISSIONS);
        } else {
            init();
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
    // 初始化
    @SuppressLint("MissingPermission")
    private void init() {
        mRadioGroup = findViewById(R.id.radio_group);
        mRadioGroup.setOnCheckedChangeListener(this);
        mLocationTextView = findViewById(R.id.location_text_view);
        // 获取定位服务
        mLocationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        if (!isGpsAble(mLocationManager)) {
            Toast.makeText(MainActivity.this, "请打开GPS", Toast.LENGTH_SHORT).show();
            openGps();
        }
        // 默认使用GPS进行定位
        mLocation = mLocationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        displayLocationData(mLocation);
        // 设置间隔两秒请求一次GPS定位信息
        mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 2000, 8, new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                displayLocationData(location);
            }
            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) { }
            @Override
            public void onProviderEnabled(String provider) { }
            @Override
            public void onProviderDisabled(String provider) {
                displayLocationData(null);
            }
        });
    }
    // 显示定位数据
    private void displayLocationData(Location location) {
        if (location != null) {
            StringBuilder sb = new StringBuilder();
            sb.append("经度：" + location.getLongitude() + "\n");
            sb.append("纬度：" + location.getLatitude() + "\n");
            sb.append("高度：" + location.getAltitude() + "\n");
            sb.append("速度：" + location.getSpeed() + "\n");
            sb.append("方位角：" + location.getBearing() + "\n");
            sb.append("定位精度：" + location.getAccuracy() + "\n");
            mLocationTextView.setText(sb.toString());
        } else {
            mLocationTextView.setText("无法获取定位数据");
        }
    }
    // 判断GPS是否可用
    private boolean isGpsAble(LocationManager lm) {
        return lm.isProviderEnabled(android.location.LocationManager.GPS_PROVIDER) ? true : false;
    }
    // 打开设置页面
    private void openGps() {
        // 位置信息设置
        Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
        startActivityForResult(intent, 0);
    }
    @Override
    @SuppressLint("MissingPermission")
    public void onCheckedChanged(RadioGroup group, int checkedId) {
        switch (checkedId) {
            case R.id.gnss_button:
                mLocation = mLocationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
                break;
            case R.id.network_button:
                mLocation = mLocationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);
                break;
        }
        displayLocationData(mLocation);
    }
}