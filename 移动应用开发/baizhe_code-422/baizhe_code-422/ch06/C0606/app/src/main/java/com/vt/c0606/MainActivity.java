package com.vt.c0606;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //发送标准广播
        findViewById(R.id.button_send_broadcast).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setAction("MyBroadcastReceiver.Custom");
                intent.putExtra("info","悄悄地告诉你一个秘密^6^");
                intent.addFlags(Intent.FLAG_ACTIVITY_PREVIOUS_IS_TOP);
                sendBroadcast(intent);
            }
        });
        //发送有序广播（连续传递）
        findViewById(R.id.button_send_ordered_broadcast).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setAction("OrderedBroadcast.Custom");
                intent.putExtra("info","悄悄地告诉你一个秘密^6^");
                intent.addFlags(Intent.FLAG_ACTIVITY_PREVIOUS_IS_TOP);
                sendOrderedBroadcast(intent,null);
            }
        });
        //发送有序广播（传递一次）
        findViewById(R.id.button_send_ordered_broadcast_stop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setAction("OrderedBroadcast.Custom");
                intent.putExtra("stop",true);
                intent.putExtra("info","悄悄地告诉你一个秘密 不要告诉别人哦^6^");
                intent.addFlags(Intent.FLAG_ACTIVITY_PREVIOUS_IS_TOP);
                sendOrderedBroadcast(intent,null);
            }
        });
    }
}
