package com.vt.c0402;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import java.util.List;

public class PhotoListAdapter extends BaseAdapter {
    private Context mContext;
    private List<PhotoModel> mPhotoModel;
    private ViewHolder mViewHolder;
    private int mConvertViewCount;
    public PhotoListAdapter(Context mContext, List<PhotoModel> mPhotoModel) {
        this.mContext = mContext;
        this.mPhotoModel = mPhotoModel;
        this.mConvertViewCount = 0;
    }
    //获取列表项总数
    @Override
    public int getCount() {
        return mPhotoModel.size();
    }
    //获取列表项对象
    @Override
    public Object getItem(int position) {
        return mPhotoModel;
    }
    //获取列表项id
    @Override
    public long getItemId(int position) {
        return position;
    }
    //获取列表项视图
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {//convertView未实例化时
            convertView = LayoutInflater.from(mContext).inflate(R.layout.list_view_item, parent, false);
            mConvertViewCount ++;
            //实例化ViewHolder缓存类对象
            mViewHolder = new ViewHolder();
            mViewHolder.orderTextView = convertView.findViewById(R.id.text_view_order);
            mViewHolder.photoImageView = convertView.findViewById(R.id.image_view_photo);
            mViewHolder.hitsTextView = convertView.findViewById(R.id.text_view_hits);
            convertView.setTag(mViewHolder);//holder缓存到convertView
            convertView.setId(mConvertViewCount);
            Log.i("getView","当前位置position："+position+"，初始化convertView的id：" +convertView.getId()+"。");
        } else {//convertView实例化时
            mViewHolder = (ViewHolder) convertView.getTag();//从convertView获取holder缓存
            Log.i("getView","当前位置position："+position+"，重用convertView的id：" +convertView.getId()+"。");
        }
        mViewHolder.orderTextView.setText("No." + (position + 1));
        mViewHolder.photoImageView.setImageResource(mPhotoModel.get(position).photoResId);
        mViewHolder.hitsTextView.setText("点击量:" + mPhotoModel.get(position).hits);
        mViewHolder.photoImageView.setId(position);
        mViewHolder.photoImageView.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                mPhotoModel.get(v.getId()).hits++;
                notifyDataSetChanged();//更新视图数据
                Toast.makeText(mContext, "点击No." + ((int) v.getId() + 1), Toast.LENGTH_SHORT).show();
            }
        });
        return convertView;
    }
    //ViewHolder缓存类
    class ViewHolder {
        TextView orderTextView;
        ImageView photoImageView;
        TextView hitsTextView;
    }
}
