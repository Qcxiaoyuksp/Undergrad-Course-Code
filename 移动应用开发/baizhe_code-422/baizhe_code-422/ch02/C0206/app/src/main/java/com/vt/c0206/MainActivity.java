package com.vt.c0206;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final RadioGroup radioGroup = findViewById(R.id.radio_group);
/*      JDK1.7 的写法
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int checkedId) {
                RadioButton radioButton = findViewById(checkedId);
                Log.i("RadioButton", "您当前选择的选项：" + radioButton.getText());
            }
        });*/
        radioGroup.setOnCheckedChangeListener((radioGroup123, checkedId) -> {
            RadioButton radioButton = findViewById(checkedId);
            Log.i("RadioButton", "您当前选择的选项：" + radioButton.getText());
        });
        Button button = findViewById(R.id.button);
/*      JDK1.7 的写法
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                for (int i = 0; i < radioGroup.getChildCount(); i++) {
                    RadioButton radioButton = (RadioButton) radioGroup.getChildAt(i);
                    if (radioButton.isChecked()) {
                        Log.v("RadioButton",  "您提交的选项是:" + radioButton.getText());
                        break;
                    }
                }
            }
        });*/
        button.setOnClickListener((View v) -> {     // JDK1.8 的写法
            for (int i = 0; i < radioGroup.getChildCount(); i++) {
                RadioButton radioButton = (RadioButton) radioGroup.getChildAt(i);
                if (radioButton.isChecked()) {
                    Log.v("RadioButton", "您提交的选项是:" + radioButton.getText());
                    break;
                }
            }
        });

    }
}