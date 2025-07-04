package com.example.yyx71;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

//这个页面没有什么花里胡哨的
public class FaultActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btn_back;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fault);
        btn_back=(Button)findViewById(R.id.btn_back);
        btn_back.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent intent=new Intent(FaultActivity.this,MainActivity.class);
        startActivity(intent);
    }
}

