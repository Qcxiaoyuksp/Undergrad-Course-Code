package com.vt.c0606;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class MyBroadcastReceivers1 extends BroadcastReceiver {
    private static final String TAG = "MyBroadcastReceiver";
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d(TAG, "-----------Receivers1-----------");
        Log.d(TAG, "Action: " + intent.getAction());
        Log.d(TAG, "URI: " + intent.toUri(Intent.URI_INTENT_SCHEME));
        Log.d(TAG, "自定义广播的info：" + intent.getStringExtra("info"));
    }
}