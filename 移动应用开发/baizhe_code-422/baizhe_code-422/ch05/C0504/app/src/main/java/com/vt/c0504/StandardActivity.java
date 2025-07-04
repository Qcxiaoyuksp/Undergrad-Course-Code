package com.vt.c0504;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class StandardActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_standard);
        //设置标题
        setTitle("StandardActivity");
        //打开StandardActivity
        findViewById(R.id.button).setOnClickListener(view -> open(StandardActivity.this));
        Log.e("启动模式", "StandardActivity.onCreate(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    public static void open(Context context) {
        context.startActivity(new Intent(context, StandardActivity.class));
    }
}
