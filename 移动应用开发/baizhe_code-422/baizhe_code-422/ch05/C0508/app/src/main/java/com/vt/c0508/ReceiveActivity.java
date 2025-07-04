package com.vt.c0508;

import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class ReceiveActivity extends AppCompatActivity {
    public static final int RESULT_CODE = 201;
    private EditText mIdEditText;
    private EditText mMsgEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receive);
        //获取传递数据
        Intent intent = getIntent();
        int id = intent.getIntExtra("id", 0);
        String msg = intent.getStringExtra("msg");
        //显示传递数据
        mIdEditText = findViewById(R.id.edit_text_id);
        mIdEditText.setText(String.valueOf(id));
        mMsgEditText = findViewById(R.id.edit_text_name);
        mMsgEditText.setText(msg);
        //关闭（没有回传数据）
        findViewById(R.id.button_finish).setOnClickListener(view -> {
            //关闭当前Activity
            finish();
        });
        //关闭（发送回传数据）
        findViewById(R.id.button_finish_result).setOnClickListener(view -> {
            //设置返回的数据
            Intent intent1 = new Intent();
            intent1.putExtra("data", "已经查阅信息！");
            setResult(RESULT_CODE, intent1);
            //关闭当前Activity
            finish();
        });
    }
}
