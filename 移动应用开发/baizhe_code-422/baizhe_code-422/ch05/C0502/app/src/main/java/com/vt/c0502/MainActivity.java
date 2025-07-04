package com.vt.c0502;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //启动内部Activity(显式)
        Button startInnerActivityButton = findViewById(R.id.button_explicit_open_inner_activity);
        startInnerActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, InnerActivity.class);
            startActivity(intent);
        });
        //启动外部Activity(显式)
        Button startOuterActivityButton = findViewById(R.id.button_explicit_open_outer_activity);
        startOuterActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent("android.intent.action.MAIN");
            intent.setClassName("com.vt.c0407", "com.vt.c0407.MainActivity");
            startActivity(intent);
        });
        //启动外部Activity(预设隐式)
        Button startImplicitPresetOuterActivityButton = findViewById(R.id.button_implicit_preset_open_outer_activity);
        startImplicitPresetOuterActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent();
            intent.setAction(MediaStore.INTENT_ACTION_STILL_IMAGE_CAMERA);
            startActivity(intent);
        });
        //启动外部Activity(自定义隐式)
        Button startImplicitCustomOuterActivityButton = findViewById(R.id.button_implicit_custom_open_outer_activity);
        startImplicitCustomOuterActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent();
            intent.setAction("custom_action");
            intent.addCategory("custom_category");
            startActivity(intent);
        });
        //启动拨打电话(预设隐式)
        Button startContactsActivityButton = findViewById(R.id.button_open_contacts);
        startContactsActivityButton.setOnClickListener(v -> {
            Uri uri = Uri.parse("tel:10086");
            Intent intent = new Intent(Intent.ACTION_DIAL, uri);
            startActivity(intent);
        });
        //启动发送短信(预设隐式)
        Button startSmsActivityButton = findViewById(R.id.button_open_sms);
        startSmsActivityButton.setOnClickListener(v -> {
            Uri uri = Uri.parse("smsto:10086");
            Intent intent = new Intent(Intent.ACTION_SENDTO, uri);
            intent.putExtra("sms_body", "测试短信");
            startActivity(intent);
        });
        //启动发送邮件(预设隐式)
        Button startEmailActivityButton = findViewById(R.id.button_open_email);
        startEmailActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent(Intent.ACTION_SEND);
            intent.putExtra(Intent.EXTRA_EMAIL, "baizhe_22@qq.com");
            intent.putExtra(Intent.EXTRA_SUBJECT, "邮件标题");
            intent.putExtra(Intent.EXTRA_TEXT, "邮件内容");
            intent.setType("text/plain");
            startActivity(intent);
        });
        //启动浏览器(预设隐式)
        Button startBrowserActivityButton = findViewById(R.id.button_open_browser);
        startBrowserActivityButton.setOnClickListener(v -> {
            Uri uri = Uri.parse("http://www.weiju2014.com");
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            startActivity(intent);
        });
    }
}
