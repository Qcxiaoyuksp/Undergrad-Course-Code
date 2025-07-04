package com.example.yyx71;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class successActivity extends AppCompatActivity implements View.OnClickListener {
    //变量声明
    private String mStr="";
    private String mTime;
    private final static String TAG="successActivity";
    private TextView tv_welcome;
    private TextView tv_time;
    private Button btn_back;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_success);
        btn_back=(Button)findViewById(R.id.btn_back);
        logintime();
        welcome();
        btn_back.setOnClickListener(this);
    }

    //返回登录时间
    private void logintime() {
        tv_time=(TextView)findViewById(R.id.tv_time);
        //用DateUtil中的getNowDateTime格式返回登录时间
        mTime = String.format("登录时间 %s", DateUtil.getNowDateTime());
        tv_time.setText(mTime);
    }

    //将之前跳转时携带的用户信息用到欢迎界面中
    private void welcome(){
        //获取intent
        Intent intent=getIntent();
        //获取intent中名为username的数据的值
        String username = intent.getStringExtra("username");
        tv_welcome=(TextView)findViewById(R.id.tv_welcome);
        mStr=String.format("%s 您好", username);
        tv_welcome.setText(mStr);
    }

    @Override
    //返回  实现跳转回到登录界面
    public void onClick(View v) {
        Intent intent2=new Intent(successActivity.this,MainActivity.class);
        startActivity(intent2);
    }
}

