package com.vt.c0602;

import androidx.appcompat.app.AppCompatActivity;
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class SubActivity extends AppCompatActivity {
    private final String TAG = "MainActivity";
    private boolean mIsBind = false;
    //保持所启动的Service的IBinder对象,同时定义一个ServiceConnection对象
    private MyService.MyBinder mIBinder;
    private ServiceConnection mConn = new ServiceConnection() {
        //Activity与Service连接成功时回调该方法
        @Override
        public void onServiceConnected(ComponentName name, IBinder iBinder) {
            Log.i(TAG, "onServiceConnected方法被调用!");
            mIBinder = (MyService.MyBinder) iBinder;
        }
        //Activity与Service断开连接时回调该方法
        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i(TAG, "onServiceDisconnected方法被调用!");
            mIBinder = null;
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub);
        this.setTitle("SubActivity");
        //创建启动Service的Intent
        final Intent intent = new Intent(this, MyService.class);
        findViewById(R.id.button_start).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService(intent);//启动service
            }
        });
        findViewById(R.id.button_stop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopService(intent);//停止service
            }
        });
        findViewById(R.id.button_bind).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bindService(intent, mConn, Service.BIND_IMPORTANT);//绑定service
                mIsBind = true;
            }
        });
        findViewById(R.id.button_unbind).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                unbindService(mConn);//解除绑定service
                mIsBind = false;
            }
        });
        findViewById(R.id.button_get).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mIBinder != null) {
                    Toast.makeText(getApplicationContext(), "Service已经运行了" + mIBinder.getSecond() + "秒！", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "onDestroy方法被调用!");
        if(mIsBind) {
            unbindService(mConn);//解除绑定service
        }
    }
}
