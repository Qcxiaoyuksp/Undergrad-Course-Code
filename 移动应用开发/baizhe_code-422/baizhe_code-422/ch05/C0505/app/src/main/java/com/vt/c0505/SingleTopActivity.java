package com.vt.c0505;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class SingleTopActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_single_top);
        //设置标题
        setTitle("SingleTopActivity");
        //打开SingleTopActivity
        findViewById(R.id.button_single_top).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                open(SingleTopActivity.this);
            }
        });
        //打开MainActivity
        findViewById(R.id.button_main).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MainActivity.open(SingleTopActivity.this);
            }
        });
        Log.e("启动模式", "SingleTopActivity.onCreate(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        Log.e("启动模式", "SingleTopActivity.onNewIntent(): TaskId: " + getTaskId() +",  hashCode: " + hashCode());
    }
    public static void open(Context context) {
        context.startActivity(new Intent(context, SingleTopActivity.class));
    }
}
