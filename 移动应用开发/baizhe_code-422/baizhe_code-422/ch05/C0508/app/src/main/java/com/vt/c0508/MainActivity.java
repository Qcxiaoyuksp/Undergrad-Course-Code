package com.vt.c0508;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private static final int REQUEST_CODE = 101;
    private EditText mResultEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mResultEditText = findViewById(R.id.edit_text_result);
        //发送数据（没有回传数据）
        findViewById(R.id.button_send).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, ReceiveActivity.class);
                intent.putExtra("id", 10407);
                intent.putExtra("msg", "MainActivity发送的信息1");
                startActivity(intent);
                mResultEditText.setText("");
            }
        });
        //发送数据（接收回传数据）
        findViewById(R.id.button_send_for_result).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, ReceiveActivity.class);
                intent.putExtra("id", 20408);
                intent.putExtra("msg", "MainActivity发送的信息2");
                startActivityForResult(intent, REQUEST_CODE);
                mResultEditText.setText("");
            }
        });
    }
    //处理回调数据
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mResultEditText.setText("正在处理回调数据");
        //判断请求码
        if (requestCode == REQUEST_CODE) {
            //判断结果码
            if (resultCode == ReceiveActivity.RESULT_CODE) {
                String result = data.getStringExtra("data");
                mResultEditText.setText(result);
            }else{
                mResultEditText.setText("没有回传数据");
            }
        }
    }
}
