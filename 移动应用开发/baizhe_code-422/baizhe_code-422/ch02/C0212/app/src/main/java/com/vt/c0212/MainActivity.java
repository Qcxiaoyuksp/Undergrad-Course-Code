package com.vt.c0212;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TimePicker;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //24小时制显示时间
        TimePicker timePicker1 = findViewById(R.id.time_picker1);
        timePicker1.setIs24HourView(true);
        timePicker1.setOnTimeChangedListener((view, hourOfDay, minute) -> Toast.makeText(MainActivity.this, "timePicker1的时间是：" + hourOfDay + "时" + minute + "分!", Toast.LENGTH_LONG).show());
        //12小时制显示时间
        TimePicker timePicker2 = findViewById(R.id.time_picker2);
        timePicker2.setOnTimeChangedListener((view, hourOfDay, minute) ->
                Toast.makeText(MainActivity.this, "timePicker2的时间是：" + hourOfDay + "时" + minute + "分!!", Toast.LENGTH_LONG)
                        .show());
    }
}
