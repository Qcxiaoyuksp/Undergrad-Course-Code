package com.example.accounting.utils;
//2.1
import android.inputmethodservice.Keyboard;
import android.inputmethodservice.KeyboardView;
import android.text.Editable;
import android.text.InputType;
import android.view.View;
import android.widget.EditText;

import com.example.accounting.R;

public class KeyBoardUtils {
    private final Keyboard k1;
    private KeyboardView keyboardView;
    private EditText editText;

    public interface OnEnsureListener
    {
        public void onEnsure();
    }
    OnEnsureListener onEnsureListener;

    public void setOnEnsureListener(OnEnsureListener onEnsureListener) {
        this.onEnsureListener = onEnsureListener;
    }
    KeyboardView.OnKeyboardActionListener listener=new KeyboardView.OnKeyboardActionListener() {
        @Override
        public void onPress(int i) {

        }

        @Override
        public void onRelease(int i) {

        }

        @Override
        public void onKey(int i, int[] ints)     //关注对象
        {
            Editable editable =editText.getText();
            int start =editText.getSelectionStart();
            switch (i)
            {
                case -5:       //删除
                    if (editable!=null)
                        if(start>0)
                            editable.delete(start-1,start);
                    break;
                case -4:       //确认
                    onEnsureListener.onEnsure();//通过这个接口，来调用方法
                    break;
                case -3:       //清零
                    editable.clear();
                    break;
                default:       //数字键
                    editable.insert(start, Character.toString( (char)i ));
                    break;
            }
        }

        @Override
        public void onText(CharSequence charSequence) {

        }

        @Override
        public void swipeLeft() {

        }

        @Override
        public void swipeRight() {

        }

        @Override
        public void swipeDown() {

        }

        @Override
        public void swipeUp() {

        }
    };

    public KeyBoardUtils(KeyboardView keyboardView, EditText editText) {
        this.keyboardView = keyboardView;
        this.editText = editText;

        this.editText.setInputType(InputType.TYPE_NULL);//取消弹出系统键盘
        k1 = new Keyboard(this.editText.getContext(), R.xml.key);

        this.keyboardView.setKeyboard(k1);
        this.keyboardView.setEnabled(true);
        this.keyboardView.setPreviewEnabled(false);
        this.keyboardView.setOnKeyboardActionListener(listener);
    }

    public void showKeyboard()
    {
        if(keyboardView.getVisibility()==View.INVISIBLE || keyboardView.getVisibility()==View.GONE)
        {
            keyboardView.setVisibility(View.VISIBLE);
        }
    }
    public void hidekeyboard()
    {
        if(keyboardView.getVisibility()==View.VISIBLE)
        {
            keyboardView.setVisibility(View.INVISIBLE);
        }
    }



}
