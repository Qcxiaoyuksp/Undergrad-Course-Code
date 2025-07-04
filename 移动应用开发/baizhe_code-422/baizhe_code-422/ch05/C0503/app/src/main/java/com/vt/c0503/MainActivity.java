package com.vt.c0503;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    final String TAG ="生命周期";
    //Activity创建时调用
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d(TAG, "MainActivity.onCreate()");
        Button button= findViewById(R.id.button);
        button.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, SubActivity.class);
            startActivity(intent);
            Log.d(TAG, "启动SubActivity");
        });
    }
    //Activity即将启动时调用
    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "MainActivity.onStart()");
    }
    //Activity即将重新启动时调用
    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d(TAG, "MainActivity.onRestart()");
    }
    //Activity即将进入后台时调用
    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "MainActivity.onResume()");
    }
    //Activity即将进入后台时调用
    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "MainActivity.onPause()");
    }
    //Activity进入后台以后时调用
    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "MainActivity.onStop()");
    }
    //Activity即将被销毁时调用
    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "MainActivity.onDestroy()");
    }
}
