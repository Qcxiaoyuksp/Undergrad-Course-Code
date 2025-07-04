package com.vt.c0205;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ImageButton button = this.findViewById(R.id.image_button);
        //button.setOnClickListener(new View.OnClickListener() {  //提示：Anonymous new View.OnClickListener() can be replaced with lambda
        button.setOnClickListener((View v) -> {//jdk1.8之后的写法，上一行是1.7的写法
            //@Override                         //JDK1.7的写法
            //public void onClick(View v) {     //JDK1.7的写法
                if (v.isSelected()) {
                    v.setSelected(false);
                    Log.i("ImageButton", "选中图片");
                } else {
                    v.setSelected(true);
                    Log.i("ImageButton", "取消选中图片");
                }
            //}                                 //JDK1.7的写法
        });
    }
}
