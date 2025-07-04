package com.vt.c0207;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener {
    private final ArrayList<String> mHobbies = new ArrayList<>();

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView resultTextView = findViewById(R.id.text_view_result);
        CheckBox checkBox1 = findViewById(R.id.check_box1);
        CheckBox checkBox2 = findViewById(R.id.check_box2);
        CheckBox checkBox3 = findViewById(R.id.check_box3);
        CheckBox checkBox4 = findViewById(R.id.check_box4);
        Button submitButton = findViewById(R.id.button_submit);
        //CheckBox设置监听器
        checkBox1.setOnCheckedChangeListener(this);
        checkBox2.setOnCheckedChangeListener(this);
        checkBox3.setOnCheckedChangeListener(this);
        checkBox4.setOnCheckedChangeListener(this);
        //Button设置监听器
        submitButton.setOnClickListener(v -> {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < mHobbies.size(); i++) {
                //选择的兴趣爱好添加到StringBuilder尾部
                if (i == (mHobbies.size() - 1)) {
                    sb.append(mHobbies.get(i));
                } else {
                    sb.append(mHobbies.get(i)).append("、");
                }
            }
            //显示选择结果
            if (sb.length() == 0) {
                resultTextView.setText("您还没有进行选择了！");
            } else {
                resultTextView.setText("您选择了：" + sb + "。");
            }
        });
    }
    //提示 '@param compoundButton' tag description is missing，'@param isChecked' tag description is missing
    // 自动 fix

    /**
     * 实现改变选项的接口方法
     *
     * @param compoundButton
     * @param isChecked
     * @return void
     */
    @Override
    public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
        if (isChecked) {
            //添加到数组
            mHobbies.add(compoundButton.getText().toString().trim());
        } else {
            //从数组中移除
            mHobbies.remove(compoundButton.getText().toString().trim());
        }
    }
}
