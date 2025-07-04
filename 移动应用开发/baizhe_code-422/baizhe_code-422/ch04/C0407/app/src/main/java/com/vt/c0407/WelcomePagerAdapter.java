package com.vt.c0407;

import android.view.View;
import android.view.ViewGroup;
import java.util.ArrayList;
import androidx.viewpager.widget.PagerAdapter;

public class WelcomePagerAdapter extends PagerAdapter {
    private ArrayList<View> mPagerViews;//分页视图的数组列表
    //构造方法
    WelcomePagerAdapter(ArrayList<View> pagerViews) {
        mPagerViews = pagerViews;
    }
    //获取分页视图的数量
    @Override
    public int getCount() {
        return mPagerViews.size();
    }
    //判断是否由对象生成界面。
    @Override
    public boolean isViewFromObject(View view, Object object) {
        return view == object;
    }
    //显示分页视图或缓存分页时进行布局的初始化。
    @Override
    public Object instantiateItem(ViewGroup container, int position) {
        container.addView(mPagerViews.get(position));
        return mPagerViews.get(position);
    }
    //销毁分页视图时移除相应的分页。
    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        container.removeView(mPagerViews.get(position));
    }
}
