package com.vt.c0209;

import android.os.Bundle;
import android.view.Gravity;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button showToastButton1 = findViewById(R.id.button_show_toast1);
        showToastButton1.setOnClickListener(v -> {
            //直接通过静态方法调用show()方法
            Toast.makeText(getApplicationContext(), "这是提示信息1", Toast.LENGTH_LONG).show();
        });
        Button showToastButton2 = findViewById(R.id.button_show_toast2);
        showToastButton2.setOnClickListener(v -> {
            //使用静态方法进行赋值后再调用show()方法
            Toast toast = Toast.makeText(MainActivity.this, "这是提示信息1", Toast.LENGTH_LONG);
            toast.setText("这是提示信息2");
            toast.setDuration(Toast.LENGTH_SHORT);
            toast.setGravity(Gravity.TOP, 0, 180);
            toast.show();
        });
    }
}
