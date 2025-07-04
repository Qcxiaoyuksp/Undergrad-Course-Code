package com.vt.c0501;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //设置标题
        setTitle("MainActivity");
        Button startInnerActivityButton = findViewById(R.id.button_open_inner_activity);
        startInnerActivityButton.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, Sub1Activity.class);
            startActivity(intent);
        });
    }
}
