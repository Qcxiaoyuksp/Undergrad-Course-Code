package com.vt.c0601;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    private final String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //创建启动Service的Intent,以及Intent属性
        final Intent intent = new Intent(this, MyService.class);
        findViewById(R.id.button_start).setOnClickListener(v -> {
            startService(intent);//启动service
            Log.i(TAG, "startService方法被调用");
        });
        findViewById(R.id.button_stop).setOnClickListener(v -> {
            stopService(intent);//停止service
            Log.i(TAG, "stopService方法被调用!");
        });
    }
}
