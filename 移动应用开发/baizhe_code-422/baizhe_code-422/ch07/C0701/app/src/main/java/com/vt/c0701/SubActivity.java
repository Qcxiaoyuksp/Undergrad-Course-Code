package com.vt.c0701;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.TextView;

public class SubActivity extends AppCompatActivity {
    private Context mContext;
    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub);
        mContext = this;
        //获取登录用户数据
        SharedPreferences sp = mContext.getSharedPreferences("User", Context.MODE_PRIVATE);
        ((TextView)findViewById(R.id.text_view)).setText("欢迎"+sp.getString("phone", "")+"访问！");
        //退出登录
        findViewById(R.id.btn_quit).setOnClickListener(v -> {
            SharedPreferences sp1 = mContext.getSharedPreferences("User", Context.MODE_PRIVATE);
            SharedPreferences.Editor editorSP = sp1.edit();
            editorSP.clear();
            editorSP.apply();
            finish();
        });
    }
}
