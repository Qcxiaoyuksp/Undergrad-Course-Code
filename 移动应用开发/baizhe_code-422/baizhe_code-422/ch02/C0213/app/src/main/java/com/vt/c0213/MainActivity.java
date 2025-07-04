package com.vt.c0213;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @SuppressLint("DefaultLocale")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //scrollView显示到视图上后执行
        final ScrollView scrollView = findViewById(R.id.scroll_view);
        scrollView.post(() -> scrollView.smoothScrollTo(0, 1000));
        //scrollView上添加50个TextView控件
        final TextView[] textView = new TextView[50];
        LinearLayout linearLayout = findViewById(R.id.linear_layout);
        for (int i = 0; i < 50; i++) {
            //实例化TextView数组的元素
            textView[i] = new TextView(this);
            textView[i].setText(String.format("第%d个TextView控件", 1 + i));
            textView[i].setTextSize(30);
            linearLayout.addView(textView[i]);
        }
        //scrollView滑动到顶部
        Button button1 = findViewById(R.id.button1);
        button1.setOnClickListener(v -> scrollView.fullScroll(ScrollView.FOCUS_UP));
        //scrollView滑动到底部
        Button button2 = findViewById(R.id.button2);
        button2.setOnClickListener(v -> scrollView.fullScroll(ScrollView.FOCUS_DOWN));
        //scrollView滑动到指定控件
        Button button3 = findViewById(R.id.button3);
        button3.setOnClickListener(v -> scrollView.scrollToDescendant(textView[20]));
        //scrollView滑动到随机位置
        Button button4 = findViewById(R.id.button4);

        button4.setOnClickListener(v -> {
            int i = (int) (Math.random() * 5000);
            scrollView.smoothScrollTo(0, i);
            Log.d(TAG, Integer.toString(i));
        });

    }

}
