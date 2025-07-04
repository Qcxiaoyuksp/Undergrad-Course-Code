package com.vt.c0601;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service {
    private final String TAG = "MyService";
    private boolean mServiceRunning = false;
    private int mSecond = 0;
    //Service绑定时调用该方法，必须要实现的Service类接口方法。
    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "onBind方法被调用!");
        return null;
    }
    //Service被创建时调用
    @Override
    public void onCreate() {
        Log.i(TAG, "onCreate方法被调用!");
        super.onCreate();
    }
    //Service被启动时调用
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i(TAG, "onStartCommand方法被调用!");
        new Thread() {
            @Override
            public void run() {
                mServiceRunning = true;
                while (mServiceRunning) {
                    Log.i(TAG, "新线程已经运行了" + mSecond + "秒");
                    try {
                        sleep(1000);
                        mSecond++;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();
        return super.onStartCommand(intent, flags, startId);
    }
    //Service被关闭之前回调
    @Override
    public void onDestroy() {
        Log.i(TAG, "onDestory方法被调用!");
        mServiceRunning = false;
        super.onDestroy();
    }
}
