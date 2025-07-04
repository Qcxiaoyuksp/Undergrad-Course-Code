package com.vt.c0507;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //设置标题
        setTitle("MainActivity");
        //打开singleInstanceActivity
        findViewById(R.id.button_single_instance).setOnClickListener(v -> SingleInstanceActivity.open(MainActivity.this));
        //打开MainActivity
        findViewById(R.id.button_main).setOnClickListener(view -> open(MainActivity.this));
        Log.e("启动模式", "MainActivity.onCreate(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    public static void open(Context context) {
        context.startActivity(new Intent(context, MainActivity.class));
    }
}
