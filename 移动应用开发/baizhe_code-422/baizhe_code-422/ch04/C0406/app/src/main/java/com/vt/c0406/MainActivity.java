package com.vt.c0406;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.ViewFlipper;

public class MainActivity extends AppCompatActivity {
private ViewFlipper mVewFlipper;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //通过布局文件获取子视图
        View view3 = View.inflate(MainActivity.this, R.layout.view_flipper_page3, null);
        //创建图片视图作为子视图
        ImageView imageView4 = new ImageView(this);
        imageView4.setAdjustViewBounds(true);
        imageView4.setImageResource(R.mipmap.img_9546);
        //设置翻转视图
        mVewFlipper = findViewById(R.id.view_flipper);
        mVewFlipper.addView(imageView4);
        mVewFlipper.addView(view3,2);
        mVewFlipper.startFlipping();
        mVewFlipper.setOnClickListener(v -> Toast.makeText(MainActivity.this, "当前显示的子视图索引号为"+mVewFlipper.getDisplayedChild(), Toast.LENGTH_SHORT).show());
        //开始按钮
        Button startBtn = findViewById(R.id.button_start);
        startBtn.setOnClickListener(v -> mVewFlipper.startFlipping());
        //停止按钮
        Button stopBtn = findViewById(R.id.button_stop);
        stopBtn.setOnClickListener(v -> mVewFlipper.stopFlipping());
        //上一页按钮
        Button previousBtn = findViewById(R.id.button_previous);
        previousBtn.setOnClickListener(v -> mVewFlipper.showPrevious());
        //下一页按钮
        Button nextBtn = findViewById(R.id.button_next);
        nextBtn.setOnClickListener(v -> mVewFlipper.showNext());
    }
}
