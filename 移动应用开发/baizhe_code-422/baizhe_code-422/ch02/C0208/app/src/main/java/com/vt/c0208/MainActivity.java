package com.vt.c0208;

import androidx.appcompat.app.AppCompatActivity;
import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.Switch;

public class MainActivity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Switch livingRoomSwitch = findViewById(R.id.switch_living_room);
        Switch bedroomSwitch = findViewById(R.id.switch_bedroom);
        livingRoomSwitch.setOnCheckedChangeListener(this);
        bedroomSwitch.setOnCheckedChangeListener(this);
    }
    // 重写开关状态改变的事件
    @SuppressLint("NonConstantResourceId")
    @Override
    public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
        switch (compoundButton.getId()) {
            case R.id.switch_living_room:
                if (isChecked) {
                    Log.i("Switch", "打开客厅灯");
                } else {
                    Log.i("Switch", "关闭客厅灯");
                }
                break;
            case R.id.switch_bedroom:
                if (isChecked) {
                    Log.i("Switch", "打开卧室灯");
                } else {
                    Log.i("Switch", "关闭卧室灯");
                }
                break;
        }
    }
}
