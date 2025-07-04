package com.vt.c0211;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final DatePicker datePicker = findViewById(R.id.date_picker);
        datePicker.updateDate(2021, 0, 1);
        datePicker.setOnDateChangedListener((view, year, monthOfYear, dayOfMonth) -> {
            Calendar calendar = Calendar.getInstance();
            calendar.set(year, monthOfYear, dayOfMonth);
            @SuppressLint("SimpleDateFormat") SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy年MM月dd日");
            Toast.makeText(getApplicationContext(), "当前选择时间：" + simpleDateFormat.format(calendar.getTime()), Toast.LENGTH_SHORT).show();
        });
        Button button1 = findViewById(R.id.button1);
        button1.setOnClickListener(v -> {
            datePicker.updateDate(2020, 0, 1);
            Toast.makeText(getApplicationContext(), "已经到恢复默认起始时间！", Toast.LENGTH_LONG).show();
        });
        Button button2 = findViewById(R.id.button2);
        button2.setOnClickListener(v -> {
            Calendar calendar = Calendar.getInstance();
            calendar.set(datePicker.getYear(), datePicker.getMonth(), datePicker.getDayOfMonth());
            @SuppressLint("SimpleDateFormat") SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy年MM月dd日");
            Toast.makeText(getApplicationContext(), "当前设置时间：" + simpleDateFormat.format(calendar.getTime()), Toast.LENGTH_SHORT).show();
        });
    }
}
