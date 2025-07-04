package com.vt.c0501;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class Sub1Activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sub1);
        //设置标题
        setTitle("Sub1Activity");
    }
}
