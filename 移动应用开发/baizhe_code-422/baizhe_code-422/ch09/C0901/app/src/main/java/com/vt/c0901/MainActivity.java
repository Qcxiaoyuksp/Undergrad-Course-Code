package com.vt.c0901;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {
    private String mUrl;
    private ImageLoader mImageLoader;
    private ImageView mImageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0901：加载网络图片(带缓存)");
        mUrl = "http://www.weiju2014.com/teachol/android/IMG225.jpg";
        // 初始化加载图片
        mImageView = findViewById(R.id.image_view);
        mImageLoader = new ImageLoader();
        // 加载图片
        Button displayButton = findViewById(R.id.display_button);
        displayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mImageLoader.displayImage(mImageView, mUrl,getExternalCacheDir().getAbsolutePath() + "/image");
            }
        });
        // 清除缓存
        Button cleanCacheButton = findViewById(R.id.clean_cache_button);
        cleanCacheButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FileHelper.delete(getExternalCacheDir().getAbsolutePath() + "/image");
                mImageView.setImageResource(R.mipmap.img_error_m);
            }
        });
    }
}
