package com.vt.c0701;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private Context mContext;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext = this;
        checkLogin();
        //登录按钮点击事件
        findViewById(R.id.btn_login).setOnClickListener(v -> {
            String phone = ((EditText) findViewById(R.id.edit_text_phone)).getText().toString().trim();
            String pwd = ((EditText) findViewById(R.id.edit_text_pwd)).getText().toString().trim();
            if (phone.equals("110") && pwd.equals("999")) {
                SharedPreferences sp = mContext.getSharedPreferences("User", Context.MODE_PRIVATE);
                SharedPreferences.Editor editorSP = sp.edit();
                editorSP.putBoolean("login", true);
                editorSP.putString("phone", phone);
                editorSP.putString("pwd", pwd);
                editorSP.apply();
                Intent intent = new Intent(mContext, SubActivity.class);
                startActivity(intent);
            } else {
                ((TextView) findViewById(R.id.text_view_error)).setText("密码错误！");
            }
        });
    }
    //自动登录
    private void checkLogin(){
        SharedPreferences sp = mContext.getSharedPreferences("User", Context.MODE_PRIVATE);
        if(sp.getBoolean("login", false)){
            Intent intent = new Intent(mContext, SubActivity.class);
            startActivity(intent);
        }
    }
}
