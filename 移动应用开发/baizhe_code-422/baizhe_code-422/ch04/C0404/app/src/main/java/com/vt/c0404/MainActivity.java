package com.vt.c0404;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.MultiAutoCompleteTextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private static final String[] data = new String[]{"蚊香", "香水", "香料", "香精", "香水品牌", "香水排名", "香水保质期", "女士香水"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AutoCompleteTextView mAct_v = findViewById(R.id.actv);
        MultiAutoCompleteTextView mM_Act_v = findViewById(R.id.mactv);
        //自动完成文本框适配数据
        ArrayAdapter<String> arrayAdapter1 = new ArrayAdapter<>(MainActivity.this, android.R.layout.simple_dropdown_item_1line, data);
        mAct_v.setAdapter(arrayAdapter1);
        mAct_v.setOnFocusChangeListener((v, hasFocus) -> {
            AutoCompleteTextView view = (AutoCompleteTextView) v;
            if (hasFocus) {
                view.showDropDown();//显示可选提示文本列表
            }
        });
        //多提示项自动完成文本框适配数据
        ArrayAdapter<String> arrayAdapter2 = new ArrayAdapter<>(getApplicationContext(), android.R.layout.simple_dropdown_item_1line, data);
        mM_Act_v.setAdapter(arrayAdapter2);
        mM_Act_v.setTokenizer(new MultiAutoCompleteTextView.CommaTokenizer());//设置分隔符
    }
}
