package com.vt.c0503;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class SubActivity extends AppCompatActivity {
    final String TAG ="生命周期";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub);
        Log.d(TAG, "SubActivity.onCreate()");
        Button button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SubActivity.this.finish();
                Log.d(TAG, "关闭SubActivity");
            }
        });
    }
    //Activity即将启动时调用
    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "SubActivity.onStart()");
    }
    //Activity即将重新启动时调用
    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d(TAG, "SubActivity.onRestart()");
    }
    //Activity即将进入后台时调用
    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "SubActivity.onResume()");
    }
    //Activity即将进入后台时调用
    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "SubActivity.onPause()");
    }
    //Activity进入后台以后时调用
    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "SubActivity.onStop()");
    }
    //Activity即将被销毁时调用
    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "SubActivity.onDestroy()");
    }
}
