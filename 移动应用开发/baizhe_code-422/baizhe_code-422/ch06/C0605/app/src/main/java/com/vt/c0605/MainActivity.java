package com.vt.c0605;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    private MyBroadcastReceiver myReceiver = new MyBroadcastReceiver();
    private boolean mRegistered = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //注册广播接收器
        findViewById(R.id.button_register).setOnClickListener(v -> {
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
            intentFilter.addAction(Intent.ACTION_SCREEN_ON);
            intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
            intentFilter.addAction(Intent.ACTION_USER_PRESENT);
            intentFilter.addAction(Intent.ACTION_BATTERY_OKAY);
            intentFilter.addAction(Intent.ACTION_BATTERY_LOW);
            intentFilter.addAction(Intent.ACTION_BATTERY_CHANGED);
//                intentFilter.addAction("com.vt.c0701.MyBroadcastReceiver.ss");
            registerReceiver(myReceiver, intentFilter);
            mRegistered = true;
        });
        //注销广播接收器
        findViewById(R.id.button_unregister).setOnClickListener(v -> {
            if(mRegistered) {
                unregisterReceiver(myReceiver);
                mRegistered = false;
            }
        });
        //启动新窗口
        findViewById(R.id.button_start_activity).setOnClickListener(v -> {
            Intent i =new Intent(MainActivity.this,MainActivity.class);
            startActivity(i);
        });
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(mRegistered) {
            unregisterReceiver(myReceiver);
        }
    }
}
