package com.vt.c0906;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button mDailyAddButton;
    private Button mDailyListButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0906：动态列表（GET方式）");

        mDailyAddButton = findViewById(R.id.add_button);
        mDailyListButton = findViewById(R.id.list_button);

        mDailyAddButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this,DailyAddActivity.class);
                startActivity(intent);
            }
        });
        mDailyListButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this,DailyListActivity.class);
                startActivity(intent);
            }
        });
    }
}