package com.vt.c0602;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service {
    private final String TAG = "MyService";
    private MyBinder mBinder = new MyBinder();
    private boolean mServiceRunning = false;
    private int mSecond;
    //创建MyBinder类，继承于Binder，用于与Activity传递数据
    public class MyBinder extends Binder {
        public int getSecond() {
            return mSecond;
        }
    }
    //Service绑定时回调该方法，继承Service后该方法必须实现的方法
    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "onBind方法被调用!");
        return mBinder;
    }
    //Service被创建时回调
    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "onCreate方法被调用!");
        mSecond = 0;
    }
    //Service被启动时调用
    @Override
    public int onStartCommand(Intent intent, int flag, int startId) {
        new Thread() {
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
        return super.onStartCommand(intent, flag, startId);
    }
    //Service重新绑定时回调
    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
        Log.i(TAG, "onRebind方法被调用!");
    }
    //Service解除绑定时回调
    @Override
    public boolean onUnbind(Intent intent) {
        Log.i(TAG, "onUnbind方法被调用!");
        mServiceRunning = false;
        return true;
    }
    //Service被关闭前回调
    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "onDestroyed方法被调用!");
        mServiceRunning = false;
    }
    //Service所属的APP被移除时回调该方法
    @Override
    public void onTaskRemoved(Intent rootIntent) {
        Log.i(TAG, "onTaskRemoved方法被调用!");
    }
}
