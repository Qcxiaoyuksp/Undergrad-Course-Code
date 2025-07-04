package com.vt.c0504;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //设置标题
        setTitle("MainActivity");
        //打开StandardActivity
        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                StandardActivity.open(MainActivity.this);
            }
        });
        Log.e("启动模式", "MainActivity.onCreate(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
}
