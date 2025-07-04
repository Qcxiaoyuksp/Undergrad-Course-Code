package com.vt.c0902;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private String mUrl;
    private ImageLoadView mImageLoadView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0902：加载网络图片（带下载提示）");
        mUrl = "http://www.weiju2014.com/teachol/android/IMG225.jpg";
        mImageLoadView = findViewById(R.id.image_load_view);
        mImageLoadView.setImageURL(mUrl);
        // 加载图片
        Button displayButton = findViewById(R.id.display_button);
        displayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mImageLoadView.setImageURL(mUrl);
            }
        });
        // 清除缓存
        Button cleanCacheButton = findViewById(R.id.clean_cache_button);
        cleanCacheButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FileHelper.delete(getExternalCacheDir().getAbsolutePath() + "/image");
                mImageLoadView.setImageResource(R.mipmap.img_error_m);
            }
        });
    }
}
