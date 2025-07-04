package com.vt.c0405;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.PopupWindow;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private Context mContext;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mContext = MainActivity.this;
        Button replyBtn = findViewById(R.id.btn_reply);
        replyBtn.setOnClickListener(v -> Toast.makeText(mContext, "回复信息", Toast.LENGTH_SHORT).show());
        Button shareBtn = findViewById(R.id.btn_share);
        shareBtn.setOnClickListener(this::initPopWindow);
    }
    // 初始化
    private void initPopWindow(View v) {
        //实例化悬浮框视图
        @SuppressLint("InflateParams") View popupView = LayoutInflater.from(mContext).inflate(R.layout.popup_share, null, false);
        //实例化悬浮框
        final PopupWindow popupWindow = new PopupWindow(popupView, ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, true);
        popupWindow.setAnimationStyle(R.style.PopupAnimation);//设置动画
        popupWindow.showAsDropDown(v, 10, 0);//显示悬浮框
        //设置悬浮框视图里的按钮事件
        Button weixinBtn = popupView.findViewById(R.id.btn_weixin);
        Button weiboBtn = popupView.findViewById(R.id.btn_weibo);
        weixinBtn.setOnClickListener(v1 -> {
            Toast.makeText(mContext, "已经分享到微信", Toast.LENGTH_SHORT).show();
            popupWindow.dismiss();//关闭悬浮框
        });
        weiboBtn.setOnClickListener(v12 -> {
            Toast.makeText(mContext, "已经分享到微信", Toast.LENGTH_SHORT).show();
            popupWindow.dismiss();//关闭悬浮框
        });
    }
}
