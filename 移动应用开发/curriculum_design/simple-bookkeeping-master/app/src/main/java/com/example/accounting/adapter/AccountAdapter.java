package com.example.accounting.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.accounting.R;
import com.example.accounting.db.AccountBean;

import java.util.Calendar;
import java.util.List;

public class AccountAdapter extends BaseAdapter {
    Context context;
    List<AccountBean>mDatas;
    LayoutInflater inflater;
    int year,month,day;

    //2.2基础适配器的构造方法
    public AccountAdapter(Context context, List<AccountBean> mDatas) {
        this.context = context;
        this.mDatas = mDatas;
        inflater = LayoutInflater.from(context);//将布局文件转换为视图
        Calendar calendar = Calendar.getInstance();
        year = calendar.get(Calendar.YEAR);
        month = calendar.get(Calendar.MONTH)+1;
        day = calendar.get(Calendar.DAY_OF_MONTH);
    }

    //2.2
    @Override
    public int getCount() {
        return mDatas.size();
    }

    //2.2得到选中位置的物件
    @Override
    public Object getItem(int position) {
        return mDatas.get(position);
    }

    //2.2
    @Override
    public long getItemId(int position) {
        return position;
    }

    //2.2返回列表项的视图对象
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder = null;//减少findViewByid()的调用次数，提高性能
        if (convertView == null) {
            convertView = inflater.inflate(R.layout.item_mainlv,parent,false);
            holder = new ViewHolder(convertView);
            convertView.setTag(holder);//设计标记
        }else{
            holder = (ViewHolder) convertView.getTag();
        }
        AccountBean bean = mDatas.get(position);
        holder.typeIv.setImageResource(bean.getsImageId());
        holder.typeTv.setText(bean.getTypename());
        holder.beizhuTv.setText(bean.getBeizhu());
        holder.moneyTv.setText("￥ "+bean.getMoney());
        if (bean.getYear()==year&&bean.getMonth()==month&&bean.getDay()==day) {
            String time = bean.getTime().split(" ")[1];
            holder.timeTv.setText("今天 "+time);
        }else {
            holder.timeTv.setText(bean.getTime());
        }
        return convertView;
    }

    class ViewHolder{
        ImageView typeIv;
        TextView typeTv,beizhuTv,timeTv,moneyTv;
        //2.2
        public ViewHolder(View view){
            typeIv = view.findViewById(R.id.item_mainlv_iv);
            typeTv = view.findViewById(R.id.item_mainlv_tv_title);
            timeTv = view.findViewById(R.id.item_mainlv_tv_time);
            beizhuTv = view.findViewById(R.id.item_mainlv_tv_beizhu);
            moneyTv = view.findViewById(R.id.item_mainlv_tv_money);

        }
    }
}
