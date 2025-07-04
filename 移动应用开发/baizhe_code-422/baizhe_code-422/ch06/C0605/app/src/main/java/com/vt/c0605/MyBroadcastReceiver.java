package com.vt.c0605;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.BatteryManager;
import android.util.Log;

public class MyBroadcastReceiver extends BroadcastReceiver {
    private static final String TAG = "MyBroadcastReceiver";
    private int mBatteryLevel;//缓存电量值
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "-----------Receiver-----------");
        Log.d(TAG, "Action: " + intent.getAction());
        Log.d(TAG, "URI: " + intent.toUri(Intent.URI_INTENT_SCHEME));
        // 网络
        if (ConnectivityManager.CONNECTIVITY_ACTION.equals(intent.getAction())) {
            //获取联网状态的NetworkInfo对象
            NetworkInfo info = ((ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE)).getActiveNetworkInfo();
            if (info != null && info.isAvailable()) {
                if ((info.getType() == ConnectivityManager.TYPE_WIFI)) {
                    Log.d(TAG, "正在使用wifi网络");
                } else if (info.getType() == ConnectivityManager.TYPE_MOBILE) {
                    String mobleType = Util.getMobleType(info);
                    Log.d(TAG, "正在使用" + mobleType + "移动网络");
                }
            } else {
                Log.d(TAG, "网络关闭");
            }
        }
        // 屏幕
        if (Intent.ACTION_SCREEN_ON.equals(intent.getAction())) {
            Log.i(TAG, "屏幕打开");
        } else if (Intent.ACTION_SCREEN_OFF.equals(intent.getAction())) {
            Log.i(TAG, "屏幕关闭");
        } else if (Intent.ACTION_USER_PRESENT.equals(intent.getAction())) {
            Log.i(TAG, "屏幕解锁");
        }
        // 电量
        if (Intent.ACTION_BATTERY_OKAY.equals(intent.getAction())) {
            Log.i(TAG, "电量已满");
        } else if (Intent.ACTION_BATTERY_LOW.equals(intent.getAction())) {
            Log.i(TAG, "电量不足");
        } else if (Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())) {
            int level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, 0);
            if (mBatteryLevel != level) {
                Log.i(TAG, "电量：" + level + "%");
                mBatteryLevel = level;
            }
        }
        // 自定义广播
        if ("MyBroadcastReceiver.Custom".equals(intent.getAction())) {
            Log.d(TAG, "自定义广播的info：" + intent.getStringExtra("info"));
        }
    }
}