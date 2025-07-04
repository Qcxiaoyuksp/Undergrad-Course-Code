package com.vt.c0705;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;
import java.util.List;

public class ContactListAdapter extends BaseAdapter {
    private MainActivity mContext;
    private List<ContactModel> mContactModel;
    private ViewHolder mViewHolder;
    //构造方法
    public ContactListAdapter(MainActivity mContext, List<ContactModel> mContactModel) {
        this.mContext = mContext;
        this.mContactModel = mContactModel;
    }
    //获取列表项总数
    @Override
    public int getCount() {
        return mContactModel.size();
    }
    //获取列表项对象
    @Override
    public Object getItem(int position) {
        return mContactModel;
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
            convertView = LayoutInflater.from(mContext).inflate(R.layout.list_view_item_contact, parent, false);
            mViewHolder = new ViewHolder();
            mViewHolder.idTextView = convertView.findViewById(R.id.text_view_id);
            mViewHolder.nameTextView = convertView.findViewById(R.id.text_view_name);
            mViewHolder.phoneTextView = convertView.findViewById(R.id.text_view_phone);
            convertView.setTag(mViewHolder);//holder缓存到convertView
        } else {//convertView实例化时
            mViewHolder = (ViewHolder) convertView.getTag();//从convertView获取holder缓存
        }

        mViewHolder.idTextView.setText(mContactModel.get(position).id);
        mViewHolder.idTextView.setId(position);
        mViewHolder.idTextView.setOnClickListener(mTextViewOnClickListener);

        mViewHolder.nameTextView.setText(mContactModel.get(position).name);
        mViewHolder.nameTextView.setId(position);
        mViewHolder.nameTextView.setOnClickListener(mTextViewOnClickListener);

        mViewHolder.phoneTextView.setText(mContactModel.get(position).phone);
        mViewHolder.phoneTextView.setId(position);
        mViewHolder.phoneTextView.setOnClickListener(mTextViewOnClickListener);

        return convertView;
    }
    //初始化监听器
    private View.OnClickListener mTextViewOnClickListener = new View.OnClickListener() {
        public void onClick(View v) {
            (mContext.mIdEditText).setText(mContactModel.get(v.getId()).id);
            (mContext.mNameEditText).setText(mContactModel.get(v.getId()).name);
            (mContext.mPhoneEditText).setText(mContactModel.get(v.getId()).phone);
        }
    };
    //ViewHolder缓存类
    class ViewHolder {
        TextView idTextView;
        TextView nameTextView;
        TextView phoneTextView;
    }
}
