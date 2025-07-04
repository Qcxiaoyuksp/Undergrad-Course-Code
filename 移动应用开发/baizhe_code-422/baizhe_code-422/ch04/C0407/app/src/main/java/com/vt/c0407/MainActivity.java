package com.vt.c0407;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;
import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private ViewPager mViewPager;
    private TextView mPagePositionTextView;
    private TextView mPageStateTextView;
    private ImageView mPage0;
    private ImageView mPage1;
    private ImageView mPage2;
    private ImageView mPage3;
    private int mCurrentPosition;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mPagePositionTextView = findViewById(R.id.text_view_page_position);
        mPageStateTextView = findViewById(R.id.text_view_page_state);
        mPage0 = findViewById(R.id.image_view_page0);
        mPage1 = findViewById(R.id.image_view_page1);
        mPage2 = findViewById(R.id.image_view_page2);
        mPage3 = findViewById(R.id.image_view_page3);
        mPage0.setOnClickListener(this);
        mPage1.setOnClickListener(this);
        mPage2.setOnClickListener(this);
        mPage3.setOnClickListener(this);
        ImageView leftImageView = findViewById(R.id.image_button_left);
        ImageView rightImageView = findViewById(R.id.image_button_right);
        leftImageView.setOnClickListener(this);
        rightImageView.setOnClickListener(this);
        mViewPager = findViewById(R.id.view_pager);
        mViewPager.addOnPageChangeListener(new PageChangeListener());
        init();
    }
    // 初始化
    private void init(){
        ArrayList<View> pagerViews = new ArrayList<>();
        pagerViews.add(View.inflate(this, R.layout.view_pager_welcome0, null));
        pagerViews.add(View.inflate(this, R.layout.view_pager_welcome1, null));
        pagerViews.add(View.inflate(this, R.layout.view_pager_welcome2, null));
        pagerViews.add(View.inflate(this, R.layout.view_pager_welcome3, null));
        WelcomePagerAdapter welcomePagerAdapter = new WelcomePagerAdapter(pagerViews);
        mViewPager.setAdapter(welcomePagerAdapter);
    }
    //单击监听事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.image_button_left:
                if (mCurrentPosition > 0) { mCurrentPosition--; }
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
            case R.id.image_button_right:
                if (mCurrentPosition < 3) { mCurrentPosition++; }
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
            case R.id.image_view_page0:
                mCurrentPosition = 0;
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
            case R.id.image_view_page1:
                mCurrentPosition = 1;
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
            case R.id.image_view_page2:
                mCurrentPosition = 2;
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
            case R.id.image_view_page3:
                mCurrentPosition = 3;
                mViewPager.setCurrentItem(mCurrentPosition, true);
                break;
        }
    }
    //页面改变监听器
    public class PageChangeListener implements ViewPager.OnPageChangeListener {
        //页面选择事件
        public void onPageSelected(int position) {
            //翻页时当前page，改变当前状态圆点图片。
            mCurrentPosition = position;
            switch (position) {
                case 0:
                    mPage0.setImageResource(R.mipmap.img_page_now);
                    mPage1.setImageResource(R.mipmap.img_page);
                    mPage2.setImageResource(R.mipmap.img_page);
                    mPage3.setImageResource(R.mipmap.img_page);
                    break;
                case 1:
                    mPage1.setImageResource(R.mipmap.img_page_now);
                    mPage0.setImageResource(R.mipmap.img_page);
                    mPage2.setImageResource(R.mipmap.img_page);
                    mPage3.setImageResource(R.mipmap.img_page);
                    break;
                case 2:
                    mPage2.setImageResource(R.mipmap.img_page_now);
                    mPage0.setImageResource(R.mipmap.img_page);
                    mPage1.setImageResource(R.mipmap.img_page);
                    mPage3.setImageResource(R.mipmap.img_page);
                    break;
                case 3:
                    mPage3.setImageResource(R.mipmap.img_page_now);
                    mPage0.setImageResource(R.mipmap.img_page);
                    mPage1.setImageResource(R.mipmap.img_page);
                    mPage2.setImageResource(R.mipmap.img_page);
                    break;
            }
        }
        //页面滚动事件
        @SuppressLint("SetTextI18n")
        public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
            mPagePositionTextView.setText("页面索引号:" + position + "  偏移百分比:" + positionOffset + "  偏移像素:" + positionOffsetPixels);
        }
        //页面滚动状态改变事件
        public void onPageScrollStateChanged(int state) {
            switch (state) {
                case ViewPager.SCROLL_STATE_IDLE:
                    mPageStateTextView.setText("空闲状态");
                    break;
                case ViewPager.SCROLL_STATE_DRAGGING:
                    mPageStateTextView.setText("拖动状态");
                    break;
                case ViewPager.SCROLL_STATE_SETTLING:
                    mPageStateTextView.setText("结束状态");
                    break;
            }
        }
    }
}
