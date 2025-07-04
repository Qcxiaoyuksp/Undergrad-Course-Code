package com.vt.c0201;

import androidx.appcompat.app.AppCompatActivity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);//设置布局文件
        // 设置LayoutParams
        LinearLayout.LayoutParams helloLayoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, 500);
        // 通过id获取TextView实例并修改属性
        TextView helloTextView = this.findViewById(R.id.text_view_hello);
        helloTextView.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.CENTER_VERTICAL);
        helloTextView.setText("Hello Android!!!");
        helloTextView.setTextSize(36f);
        helloTextView.setLayoutParams(helloLayoutParams);
        // 通过id获取xml布局里的linearLayout布局
        LinearLayout mainActivityLinearLayout = this.findViewById(R.id.linear_layout_main_activity);
        //动态创建TextView实例
        TextView welcomeTextView = new TextView(this);
        welcomeTextView.setGravity(Gravity.CENTER);
        welcomeTextView.setText("welcome!");
        welcomeTextView.setTextSize(36f);
        welcomeTextView.setTextColor(Color.rgb(255, 25, 25));
        // 添加到linearLayout布局内
        mainActivityLinearLayout.addView(welcomeTextView);
    }
}
