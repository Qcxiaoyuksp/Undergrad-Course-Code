package com.example.accounting.adapter;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;
import androidx.fragment.app.ListFragment;

import java.util.List;
//2.2 记载页的适配器，将Fragment绑定到ViewPager中，并处理其生命周期管理和界面切换

public class RecordPagerAdapter extends FragmentPagerAdapter {
    List<Fragment>fragmentList;
    String[]titles = {"支出","收入"};
    public RecordPagerAdapter(@NonNull FragmentManager fm, List<Fragment>fragmentList) {
        super(fm);
        this.fragmentList = fragmentList;
    }
    @NonNull
    @Override
    public Fragment getItem(int position) {
        return fragmentList.get(position);
    }

    @Override
    public int getCount() {
        return fragmentList.size();
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return titles[position];
    }
}
