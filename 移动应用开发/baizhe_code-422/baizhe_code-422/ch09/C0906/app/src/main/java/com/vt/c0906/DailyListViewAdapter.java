package com.vt.c0906;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class DailyListViewAdapter extends BaseAdapter {
    private String mDonmain;
    public Context mContext;
    private DailyModel mDailyModel;
    private int mLayoutResource;
    private ViewHolder mViewHolder;

    public DailyListViewAdapter(String doMain, Context context, DailyModel dailyModel, int layoutResource) {
        this.mDonmain = doMain;
        this.mContext = context;
        this.mDailyModel = dailyModel;
        this.mLayoutResource = layoutResource;
    }
    //获取列表项总数
    public int getCount() {
        if(this.mDailyModel==null){
            return 0;
        }
        return this.mDailyModel.ides.size();
    }
    // 获取列表项对象
    public Object getItem(int position) {
        return mDailyModel;
    }
    // 获取列表项id
    public long getItemId(int position) {
        return position;
    }
    // 获取列表项视图
    public View getView(final int position, View view, ViewGroup arg2) {
        Log.e("position", String.valueOf(position));
        if (view == null) {//view未实例化时
            view = LayoutInflater.from(mContext).inflate(mLayoutResource, null);
            mViewHolder = new ViewHolder();
            mViewHolder.nameTextView = view.findViewById(R.id.name_text_view);
            mViewHolder.contentTextView = view.findViewById(R.id.content_text_view);
            mViewHolder.imageImageView = view.findViewById(R.id.image_image_view);
            mViewHolder.creatTimeTextView = view.findViewById(R.id.creat_time_text_view);
        } else {//view实例化后
            mViewHolder = (ViewHolder) view.getTag();//从view获取holder缓存
            Log.i("getView", "当前位置position：" + position + "，重用convertView的id：" + view.getId() + "。");
        }
        // 昵称
        mViewHolder.nameTextView.setText(this.mDailyModel.names.get(position) + "：");
        mViewHolder.nameTextView.setId(position);
        mViewHolder.nameTextView.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                displayPosition(v.getId());
            }
        });
        // 内容
        mViewHolder.contentTextView.setText(this.mDailyModel.contents.get(position));
        mViewHolder.contentTextView.setLineSpacing(1.0f, 1.0f);
        mViewHolder.contentTextView.setId(position);
        mViewHolder.contentTextView.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                displayPosition(v.getId());
            }
        });
        // 图片
        if (!this.mDailyModel.images.get(position).equals("")) {
            mViewHolder.imageImageView.setVisibility(View.VISIBLE);
            mViewHolder.imageImageView.setId(position);
            mViewHolder.imageImageView.setOnClickListener(new View.OnClickListener() {
                public void onClick(View v) {
                    displayPosition(v.getId());
                }
            });
            String url = mDonmain + this.mDailyModel.images.get(position).replace("d/", "d/_S_");
            ImageLoader mImageLoader = new ImageLoader();
            mImageLoader.displayImage(mViewHolder.imageImageView, url, mContext.getExternalCacheDir().getAbsolutePath() + "/image");
        } else {
            mViewHolder.imageImageView.setVisibility(View.GONE);
        }
        // 发布时间
        mViewHolder.creatTimeTextView.setText(this.mDailyModel.createTimes.get(position));
        // 设置当前位置的视图
        view.setTag(mViewHolder);
        return view;
    }
    // 显示位置
    public void displayPosition(int position) {
        Toast.makeText(mContext, "第" + position + "个动态", Toast.LENGTH_LONG).show();
    }
    // ViewHolder缓存类
    final static class ViewHolder {
        TextView nameTextView;
        TextView contentTextView;
        ImageView imageImageView;
        TextView creatTimeTextView;
    }
}
