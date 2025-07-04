package com.vt.c0604;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class MyIntentService extends IntentService {
    public static final String ACTION_ADD = "com.vt.c0604.action.add";
    public static final String ACTION_MULTPLY = "com.vt.c0604.action.mutiply";
    private static final String EXTRA_PARAM1 = "com.vt.c0604.extra.PARAM1";
    private static final String EXTRA_PARAM2 = "com.vt.c0604.extra.PARAM2";
    private static final String TAG = "MyIntentService";
    public MyIntentService() {
        super("MyIntentService");
        Log.i(TAG, "线程" + Thread.currentThread().getId() + ":MyIntentService()构造方法被调用，MyIntentService实例哈希码为"+this.hashCode());
    }
    //静态方法：启动add动作的MyIntentService
    public static void startActionAdd(Context context, int param1, int param2) {
        Intent intent = new Intent(context, MyIntentService.class);
        intent.setAction(ACTION_ADD);
        intent.putExtra(EXTRA_PARAM1, param1);
        intent.putExtra(EXTRA_PARAM2, param2);
        context.startService(intent);
    }
    //静态方法：启动mutiply动作的MyIntentService
    public static void startActionMutiply(Context context, int param1, int param2) {
        Intent intent = new Intent(context, MyIntentService.class);
        intent.setAction(ACTION_MULTPLY);
        intent.putExtra(EXTRA_PARAM1, param1);
        intent.putExtra(EXTRA_PARAM2, param2);
        context.startService(intent);
    }
    //重写onHandleIntent，根据动作调用不同的方法。
    @Override
    protected void onHandleIntent(Intent intent) {
        if (intent != null) {
            final String action = intent.getAction();
            if (ACTION_ADD.equals(action)) {
                Log.i(TAG, "线程" + Thread.currentThread().getId() + ":调用加法运算方法，MyIntentService实例哈希码为"+this.hashCode());
                final int param1 = intent.getExtras().getInt(EXTRA_PARAM1);
                final int param2 = intent.getExtras().getInt(EXTRA_PARAM2);
                handleActionAdd(param1, param2);
            } else if (ACTION_MULTPLY.equals(action)) {
                Log.i(TAG, "线程" + Thread.currentThread().getId() + ":调用乘法运算方法，MyIntentService实例哈希码为"+this.hashCode());
                final int param1 = intent.getExtras().getInt(EXTRA_PARAM1);
                final int param2 = intent.getExtras().getInt(EXTRA_PARAM2);
                handleActionMutiply(param1, param2);
            }
        }
    }
    //加法运算方法
    public void handleActionAdd(int param1, int param2) {
        Log.i(TAG, "线程" + Thread.currentThread().getId() + ":" + param1 + "+" + param2 + "=" + (param1 + param2)+"，MyIntentService实例哈希码为"+this.hashCode());
    }
    //乘法运算方法
    private void handleActionMutiply(int param1, int param2) {
        Log.i(TAG, "线程" + Thread.currentThread().getId() + ":" + param1 + "*" + param2 + "=" + (param1 * param2)+"，MyIntentService实例哈希码为"+this.hashCode());
    }
}
