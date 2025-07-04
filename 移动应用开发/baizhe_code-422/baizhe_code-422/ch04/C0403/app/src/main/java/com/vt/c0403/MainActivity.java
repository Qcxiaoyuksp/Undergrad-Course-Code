package com.vt.c0403;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private Context mContext;
    private List<CategoryModel> mCategoryModel;
    private CategoryAdapter mAdapter;
    private GridView mGridView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mContext = MainActivity.this;
        mCategoryModel = new ArrayList<>();
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category1, "图书音像"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category2, "个化护肤"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category3, "美食外卖"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category4, "鞋靴箱包"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category5, "食品饮料"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category6, "运动户外"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category7, "手机数码"));
        mCategoryModel.add(new CategoryModel(R.mipmap.img_category8, "日用百货"));

        mAdapter = new CategoryAdapter(mContext,mCategoryModel);
        mGridView = findViewById(R.id.grid_view);
        mGridView.setAdapter(mAdapter);//设置适配器
        mGridView.setSelector(new ColorDrawable(Color.TRANSPARENT));//设置被选网格项的背景色

        mGridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Toast.makeText(mContext, "点击了第" + position + "项", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
