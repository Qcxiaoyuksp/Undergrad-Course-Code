package com.vt.c0803;

import android.net.Uri;
import android.os.Bundle;
import android.widget.ImageView;
import java.io.File;
import androidx.appcompat.app.AppCompatActivity;

public class PreviewActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_preview);
        this.setTitle("照片预览");

        ImageView imageView = findViewById(R.id.image_view);
        String path = getIntent().getStringExtra("path");
        if(path != null){
            imageView.setImageURI(Uri.fromFile(new File(path)));
        }
    }
}

