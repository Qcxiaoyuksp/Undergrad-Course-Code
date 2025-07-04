package com.vt.c0509;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.vt.c0509.fragment.FollowFragment;
import com.vt.c0509.fragment.MeetFragment;
import com.vt.c0509.fragment.MineFragment;
import com.vt.c0509.fragment.OnShowTabNumListener;
import com.vt.c0509.fragment.RemindFragment;
import com.vt.c0509.fragment.VicinityFragment;

public class MainActivity extends AppCompatActivity implements OnShowTabNumListener, MeetFragment.OnShowTabNumListener {
    private TextView mTitleTextView;
    private FragmentManager mFragmentManager;
    private String[] mTitles = new String[]{"附近", "关注", "偶遇", "提醒", "自己"};
    private TextView[] mTab = new TextView[5];
    private int[] mTabId = new int[]{R.id.tab_vicinity, R.id.tab_follow, R.id.tab_meet, R.id.tab_remind, R.id.tab_mine};
    private int[] mTabNumId = new int[]{R.id.tab_vicinity_num, R.id.tab_follow_num, R.id.tab_meet_num, R.id.tab_remind_num, R.id.tab_mine_num};
    private TextView[] mTabNum = new TextView[5];
    private Fragment[] mFragment = new Fragment[]{new VicinityFragment(), new FollowFragment(), new MeetFragment(), new RemindFragment(), new MineFragment()};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // 初始化控件
        mTitleTextView = findViewById(R.id.text_view_title);
        for (int i = 0; i < mTab.length; i++) {
            mTab[i] = findViewById(mTabId[i]);
            mTab[i].setTag(i);
            mTab[i].setOnClickListener(v -> showTabFragment((int) v.getTag()));
            mTabNum[i] = findViewById(mTabNumId[i]);
        }
        // 必须使用FragmentActivity.getSupportFragmentManager()获取FragmentManager实例
        mFragmentManager = getSupportFragmentManager();
        showTabFragment(2);//设置默认显示的fragment
        showTabNum(4, 5);//设置tab显示圆点数字
    }
    // 隐藏tab的圆点数字
    private void hideTabNum(int index) {
        mTabNum[index].setVisibility(View.GONE);
    }
    // 显示tab的圆点数字
    public void showTabNum(int index, int num) {
        mTabNum[index].setText(String.valueOf(num));
        mTabNum[index].setVisibility(View.VISIBLE);
    }
    // 显示fragment
    private void showTabFragment(int index) {
        // 创建事务
        FragmentTransaction fragmentTransaction = mFragmentManager.beginTransaction();
        // 判断是否已经添加Fragment
        if (mFragmentManager.getFragments().isEmpty()) {
            for (int i = 0; i < mTab.length; i++) {
                fragmentTransaction.add(R.id.fragment_content, mFragment[i]);//添加Fragment
            }
        }
        // 还原状态
        for (int i = 0; i < mTab.length; i++) {
            fragmentTransaction.hide(mFragment[i]);//隐藏Fragment
            mTab[i].setSelected(false);//取消tab选中状态
        }
        mTitleTextView.setText(mTitles[index]);//设置标题
        mTab[index].setSelected(true);//设置tab选中状态
        hideTabNum(index);//隐藏tab圆点
        fragmentTransaction.show(mFragment[index]);//显示Fragment
        fragmentTransaction.commit();//提交事务
    }
    // 实现接口方法
    @Override
    public void onShowTabNum(int index, int num) {
        showTabNum(index, num);
    }
}
