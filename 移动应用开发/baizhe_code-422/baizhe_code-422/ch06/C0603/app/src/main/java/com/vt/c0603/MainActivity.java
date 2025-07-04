package com.vt.c0603;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Intent intent = new Intent(this, MyService.class);
        findViewById(R.id.button_start_foreground).setOnClickListener(v -> startService(intent));
        findViewById(R.id.button_stop_foreground).setOnClickListener(v -> stopService(intent));
    }
}
