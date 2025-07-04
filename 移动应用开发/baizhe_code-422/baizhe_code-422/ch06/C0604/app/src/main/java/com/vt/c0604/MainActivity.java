package com.vt.c0604;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MyIntentService";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(TAG, "线程" + Thread.currentThread().getId() + ":MainActivity.onCreate()被调用");
        //"启动add动作的IntentService"按钮点击事件
        findViewById(R.id.button_start_foo).setOnClickListener(v -> MyIntentService.startActionAdd(MainActivity.this, 13, 7));
        //"启动multiply动作的IntentService"按钮点击事件
        findViewById(R.id.button_start_baz).setOnClickListener(v -> MyIntentService.startActionMutiply(MainActivity.this, 43, 27));
    }
}
