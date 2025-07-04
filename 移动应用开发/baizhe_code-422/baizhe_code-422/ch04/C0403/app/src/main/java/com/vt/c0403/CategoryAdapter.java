package com.vt.c0403;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.List;

public class CategoryAdapter extends BaseAdapter {
    private Context mContext;
    private List<CategoryModel> mCategoryModel;
    private ViewHolder mViewHolder;
    private int mConvertViewCount;
    CategoryAdapter(Context mContext, List<CategoryModel> mCategoryModel) {
        this.mContext = mContext;
        this.mCategoryModel = mCategoryModel;
    }
    //获取网格项总数
    @Override
    public int getCount() {
        return mCategoryModel.size();
    }
    //获取网格项对象
    @Override
    public Object getItem(int position) {
        return mCategoryModel;
    }
    //获取网格项id
    @Override
    public long getItemId(int position) {
        return position;
    }
    //获取网格项视图
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {//convertView未实例化时
            convertView = LayoutInflater.from(mContext).inflate(R.layout.grid_view_item, parent, false);
            mConvertViewCount++;
            //实例化ViewHolder缓存类对象
            mViewHolder = new ViewHolder();
            mViewHolder.icoImageView = convertView.findViewById(R.id.image_view_ico);
            mViewHolder.nameTextView = convertView.findViewById(R.id.text_view_name);
            convertView.setTag(mViewHolder);//holder缓存到convertView
            convertView.setId(mConvertViewCount);
            Log.i("getView", "当前位置position：" + position + "，初始化convertView的id：" + convertView.getId() + "。");
        } else {//convertView实例化时
            mViewHolder = (ViewHolder) convertView.getTag();//从convertView获取holder缓存
            Log.i("getView", "当前位置position：" + position + "，重用convertView的id：" + convertView.getId() + "。");
        }

        mViewHolder.icoImageView.setImageResource(mCategoryModel.get(position).ico);
        mViewHolder.nameTextView.setText(mCategoryModel.get(position).name);
        return convertView;
    }
    //ViewHolder缓存类
    class ViewHolder {
        ImageView icoImageView;
        TextView nameTextView;
    }
}
