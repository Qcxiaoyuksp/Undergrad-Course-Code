package com.vt.c0602;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("MainActivity");
        findViewById(R.id.button).setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, SubActivity.class);
            startActivity(intent);
        });
    }

    @Override
    protected void onResume(){
        super.onResume();
    }
}
