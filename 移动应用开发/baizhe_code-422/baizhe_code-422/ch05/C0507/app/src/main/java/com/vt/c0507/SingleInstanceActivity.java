package com.vt.c0507;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class SingleInstanceActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_single_instance);
        //设置标题
        setTitle("SingleInstanceActivity");
        //打开singleTaskActivity
        findViewById(R.id.button_single_instance).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open(SingleInstanceActivity.this);
            }
        });
        //打开MainActivity
        findViewById(R.id.button_main).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MainActivity.open(SingleInstanceActivity.this);
            }
        });
        Log.e("启动模式", "SingleInstanceActivity.onCreate(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        Log.e("启动模式", "SingleInstanceActivity.onNewIntent(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    public static void open(Context context) {
        context.startActivity(new Intent(context, SingleInstanceActivity.class));
    }
}
