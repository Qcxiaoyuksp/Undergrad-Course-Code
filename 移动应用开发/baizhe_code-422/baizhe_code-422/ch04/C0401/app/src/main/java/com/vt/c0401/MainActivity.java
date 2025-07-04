package com.vt.c0401;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private ListView mListView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ArrayAdapter<CharSequence> resAdapter = ArrayAdapter.createFromResource(this,R.array.movie_type_array,android.R.layout.simple_expandable_list_item_1);//movie_type_array数组资源适配
        @SuppressLint("InflateParams") View headerView = LayoutInflater.from(MainActivity.this).inflate(R.layout.list_view_header, null);//顶部视图

        mListView = findViewById(R.id.list_view);//获取ListView标签
        mListView.setAdapter(resAdapter);//设置数据适配器
        mListView.addHeaderView(headerView);//添加顶部视图

        //添加单击列表项事件监听器
        mListView.setOnItemClickListener((parent, view, position, id) -> Toast.makeText(MainActivity.this, ((TextView)mListView.getChildAt(position)).getText(), Toast.LENGTH_SHORT).show());
    }
}
