package com.vt.c0706;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "MainActivity";
    private EditText mNameEditText;
    private EditText mContentEditText;
    private EditText[] mExtraEditText = new EditText[3];
    private Button mEncodeSingleJSONBtn;
    private Button mEncodeMultiJSONBtn;
    private Button mDecodeJSONBtn;
    private Button mEmptyBtn;
    private TextView mResultTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("C0706:合成和解析JSON数据");
        //初始化
        mNameEditText = findViewById(R.id.edit_text_name);
        mContentEditText = findViewById(R.id.edit_text_content);
        mExtraEditText[0] = findViewById(R.id.edit_text_extra0);
        mExtraEditText[1] = findViewById(R.id.edit_text_extra1);
        mExtraEditText[2] = findViewById(R.id.edit_text_extra2);
        mEncodeSingleJSONBtn = findViewById(R.id.button_encode_json_single);
        mEncodeMultiJSONBtn = findViewById(R.id.button_encode_json_multi);
        mDecodeJSONBtn = findViewById(R.id.button_decode_json);
        mResultTextView = findViewById(R.id.text_view_result);
        mEmptyBtn = findViewById(R.id.button_empty);
        //设置点击监听器
        mEncodeSingleJSONBtn.setOnClickListener(this);
        mEncodeMultiJSONBtn.setOnClickListener(this);
        mDecodeJSONBtn.setOnClickListener(this);
        mEmptyBtn.setOnClickListener(this);
    }
    //合成JSON
    private void encodeJSON(boolean isSingle) {
        JSONObject jsonObject = new JSONObject();
        try {
            //将昵称和内容存入jsonObject对象
            jsonObject.put("name", mNameEditText.getText());
            jsonObject.put("content", mContentEditText.getText());
            //将图片分别存入新建的JSONObject类对象内
            JSONObject pic0JsonObject = new JSONObject();
            pic0JsonObject.put("type", "pic");
            pic0JsonObject.put("url", mExtraEditText[0].getText());
            JSONObject pic1JsonObject = new JSONObject();
            pic1JsonObject.put("type", "pic");
            pic1JsonObject.put("url", mExtraEditText[1].getText());
            JSONObject pic2JsonObject = new JSONObject();
            pic2JsonObject.put("type", "pic");
            pic2JsonObject.put("url", mExtraEditText[2].getText());
            //将存入图片的三个JSONObject类对象存入jsonArray对象
            JSONArray jsonArray = new JSONArray();
            jsonArray.put(pic0JsonObject);
            jsonArray.put(pic1JsonObject);
            jsonArray.put(pic2JsonObject);
            //将保存图片存入jsonObject对象
            jsonObject.put("extra", jsonArray);
            //判断是单行还是多行显示
            if (isSingle) {
                mResultTextView.setText(jsonObject.toString());
            } else {
                mResultTextView.setText(jsonObject.toString(4));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    //解析JSON
    private void decodeJSON() {
        try {
            JSONObject jsonObject = new JSONObject(mResultTextView.getText().toString().trim());
            //获取name键值的数据
            String name = jsonObject.getString("name");
            mNameEditText.setText(name);
            //获取content键值的数据
            String content = jsonObject.getString("content");
            mContentEditText.setText(content);
            //获取extra键值的数据
            JSONArray jsonArray = jsonObject.getJSONArray("extra");
            //遍历extra存储的JSONArray数据
            for (int i = 0; i < jsonArray.length(); i++) {
                JSONObject extraJSONObject = jsonArray.getJSONObject(i);
                mExtraEditText[i].setText(extraJSONObject.optString("url", "images/default.jpg"));
            }
            //额外知识：Logcat中递归自动解析JSON字符串的所有数据
            iterateJSON(jsonObject, "");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    //遍历显示JSON字符串解析后的数据
    private void iterateJSON(Object obj, String tab) {
        String addTab = "    ";//Log输出时缩进的空格
        JSONObject jsonObject = (JSONObject) obj;
        JSONArray names = jsonObject.names();
        //遍历JSONObject的键名
        for (int i = 0; i < names.length(); i++) {
            try {
                //判断是否是JSONArray类型的键值
                if (jsonObject.get(names.get(i).toString()) instanceof JSONArray) {
                    //Logcat中输出键值为JSONArray类型的键名
                    Log.d(TAG, tab + names.get(i).toString() + ":");
                    //将JSONArray类型的键值强制转换成JSONArray类型的对象
                    JSONArray jsonJSONArray = (JSONArray) jsonObject.get(names.get(i).toString());
                    //遍历JSONArray的元素
                    for (int j = 0; j < jsonJSONArray.length(); j++) {
                        try {
                            //递归
                            iterateJSON(jsonJSONArray.get(j), tab + addTab);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                } else {
                    //Logcat中输出键名和对应的键值
                    Log.d(TAG, tab + names.get(i).toString() + ":" + jsonObject.optString(names.get(i).toString()));
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }
    //点击事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button_encode_json_single:
                encodeJSON(true);
                break;
            case R.id.button_encode_json_multi:
                encodeJSON(false);
                break;
            case R.id.button_decode_json:
                decodeJSON();
                break;
            case R.id.button_empty:
                mNameEditText.setText("");
                mContentEditText.setText("");
                mExtraEditText[0].setText("");
                mExtraEditText[1].setText("");
                mExtraEditText[2].setText("");
                break;
        }
    }
}
