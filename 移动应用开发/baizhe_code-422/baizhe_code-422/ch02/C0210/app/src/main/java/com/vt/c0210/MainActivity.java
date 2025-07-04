package com.vt.c0210;

import android.app.AlertDialog;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.view.LayoutInflater;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private Context mContext;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext = this;
        //单击按钮显示默认对话框
        Button button1 = findViewById(R.id.button1);
        button1.setOnClickListener(v -> showAlertDialog1());
        //单击按钮显示自定义对话框
        Button button2 = findViewById(R.id.button2);
        button2.setOnClickListener(v -> showAlertDialog2());
    }
    //显示默认对话框的方法
    private void showAlertDialog1() {
        //设置默认对话框的图标、标题和文本信息
        AlertDialog.Builder adBuilder = new AlertDialog.Builder(mContext);
        adBuilder.setIcon(R.mipmap.ic_launcher);
        adBuilder.setTitle("默认对话框");
        adBuilder.setMessage("这是一个默认对话框吗？");
        //单击确认按钮事件
        adBuilder.setPositiveButton("是", (dialog, which) -> Toast.makeText(mContext, "点击了确认按钮", Toast.LENGTH_SHORT).show());
        //单击取消按钮事件
        adBuilder.setNegativeButton("否", (dialog, which) -> Toast.makeText(mContext, "点击了取消按钮", Toast.LENGTH_SHORT).show());
        //单击中性按钮事件
        adBuilder.setNeutralButton("不确定", (dialog, which) -> Toast.makeText(mContext, "点击了中性按钮", Toast.LENGTH_SHORT).show());
        adBuilder.show();
    }
    //显示自定义对话框的方法
    private void showAlertDialog2() {
        //通过LayoutInflater加载xml布局文件作为一个View对象
        View view = LayoutInflater.from(mContext).inflate(R.layout.dialog_setting_school, null);
        //设置自定义对话框的标题以及布局文件
        AlertDialog.Builder adBuilder = new AlertDialog.Builder(mContext);
        adBuilder.setTitle("自定义对话框：请输入院校的全称");
        adBuilder.setView(view);
        //获取自定义布局中的EditText控件
        final EditText schoolEditText = view.findViewById(R.id.edit_text_school);
        //单击确定按钮事件：对EditText输入的内容进行判断
        adBuilder.setPositiveButton("确定", (dialog, which) -> {
            String school = schoolEditText.getText().toString().trim();
            if (!school.equals("")) {
                if (school.endsWith("大学") || school.endsWith("学院") || school.endsWith("学校")) {
                    Toast.makeText(mContext, school, Toast.LENGTH_LONG).show();
                } else {
                    Toast.makeText(mContext, "请使用院校标准名称！", Toast.LENGTH_LONG).show();
                }
            } else {
                Toast.makeText(mContext, "院校未设置", Toast.LENGTH_LONG).show();
            }
        });
        adBuilder.setNegativeButton("取消", null);//未设置点击监听器
        //设置对话框显示的位置并显示对话框
        AlertDialog alertDialog = adBuilder.create();
        alertDialog.setOnShowListener(dialog -> {
            //100毫秒后EditText获取焦点并弹出虚拟键盘
            new Handler().postDelayed(() -> {
                schoolEditText.requestFocus();//EditText获取焦点
                showInputMethod();//弹出虚拟键盘
            }, 100);
        });
        alertDialog.setView(view, 0, 50, 0, 50);
        alertDialog.setCanceledOnTouchOutside(false);//点击对话框之外的地方不消失
        alertDialog.show();
    }
    //弹出虚拟键盘的方法
    private void showInputMethod() {
        InputMethodManager inputMethodManager = (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.toggleSoftInput(0, InputMethodManager.HIDE_NOT_ALWAYS);
    }
}