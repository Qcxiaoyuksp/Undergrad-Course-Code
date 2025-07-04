package com.vt.c0907;

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Scroller;
import android.widget.TextView;

public class PullDownListView extends FrameLayout implements GestureDetector.OnGestureListener {
    public static int MAX_LENGHT = 0;
    public static final int STATE_REFRESH = 1;
    public static final int SCROLL_TO_CLOSE = 2;
    public static final int SCROLL_TO_REFRESH = 3;
    public static final double SCALE = 0.9d;
    private static final int CLOSEDELAY = 300;
    private static final int REFRESHDELAY = 300;
    private Animation mAnimationDown;
    private Animation mAnimationUp;
    private ImageView mArrow;
    private View emptyHeaderView;
    private ProgressBar mProgressBar;
    private TextView more;
    private ProgressBar mProgressBar2;
    private int mState;
    private TextView mTitle;
    public ListView mListView;
    public LinearLayout foot;
    public LinearLayout footer_layout;
    public LinearLayout header;
    private GestureDetector mDetector;
    private FlingRunnable mFlinger;
    private int mPading;
    private int mDestPading;
    private int mLastTop;
    private LinearLayout mFirstChild;
    private FrameLayout mUpdateContent;
    private OnRefreshListioner mRefreshListioner;
    private boolean isAutoLoadMore = false;
    private boolean hasMore = true;
    private boolean isEnd = true;
    private boolean listviewDoScroll = false;
    private boolean isFirstLoading = false;
    private boolean mLongPressing;
    private boolean mPendingRemoved = false;//
    private String pulldowntorefresh = "下拉刷新";
    private String releasetorefresh = "松开刷新";
    private String loading = "正在加载。。。";
    private String moreListItem = "更多";
    private float lastY;
    private boolean useempty = true;
    public boolean isloading = false;
    private View view;

    class FlingRunnable implements Runnable {
        private int mLastFlingY;
        private Scroller mScroller;

        private void startCommon() {
            removeCallbacks(this);
        }

        public void run() {
            boolean noFinish = mScroller.computeScrollOffset();
            int curY = mScroller.getCurrY();
            int deltaY = curY - mLastFlingY;
            if (noFinish) {
                move(deltaY, true);
                mLastFlingY = curY;
                post(this);
            } else {
                removeCallbacks(this);
                if (mState == SCROLL_TO_CLOSE) {
                    mState = -1;
                }
            }
        }

        public void startUsingDistance(int distance, int duration) {
            if (distance == 0) distance--;
            startCommon();
            mLastFlingY = 0;
            mScroller.startScroll(0, 0, 0, distance, duration);
            post(this);
        }

        public FlingRunnable() {
            mScroller = new Scroller(getContext());
        }
    }
    //下拉刷新以及加载更多回调监听接口
    public interface OnRefreshListioner {
        void onRefresh();
        void onLoadMore();
    }
    // 构造方法
    public PullDownListView(Context context) {
        super(context);
        mDetector = new GestureDetector(context, this);
        mFlinger = new FlingRunnable();
        init();
        addRefreshBar();
    }
    // 构造方法
    @SuppressWarnings("deprecation")
    public PullDownListView(Context context, AttributeSet att) {
        super(context, att);
        useempty = att.getAttributeBooleanValue(null, "useempty", true);
        mDetector = new GestureDetector(this);
        mFlinger = new FlingRunnable();
        init();
        addRefreshBar();
    }
    //添加刷新头部的控件
    private void addRefreshBar() {
        // 向上滑动的动画
        mAnimationUp = AnimationUtils.loadAnimation(getContext(), R.anim.rotate_up);
        // 向下滑动的动画
        mAnimationDown = AnimationUtils.loadAnimation(getContext(), R.anim.rotate_down);
        // 刷新头部的view
        view = LayoutInflater.from(getContext()).inflate(R.layout.pull_down_list_view_refresh_bar, null);
        // 添加view在本控件中
        addView(view);
        // 设置刷新头部的控件
        mFirstChild = (LinearLayout) view;
        mUpdateContent = getChildAt(0).findViewById(R.id.iv_content);
        mArrow = new ImageView(getContext());

        LayoutParams layoutparams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
        mArrow.setScaleType(ImageView.ScaleType.FIT_CENTER);
        mArrow.setLayoutParams(layoutparams);
        mArrow.setImageResource(R.mipmap.pull_down_list_view_arrow_down);
        mUpdateContent.addView(mArrow);

        LayoutParams layoutparams1 = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
        layoutparams1.gravity = Gravity.CENTER;
        mProgressBar = new ProgressBar(getContext(), null, android.R.attr.progressBarStyleSmallInverse);
        mProgressBar.setIndeterminate(false);
        int i = getResources().getDimensionPixelSize(R.dimen.updatebar_padding);
        mProgressBar.setPadding(i, i, i, i);
        mProgressBar.setLayoutParams(layoutparams1);
        mUpdateContent.addView(mProgressBar);
        mTitle = findViewById(R.id.tv_title);
    }

    protected void onFinishInflate() {
        super.onFinishInflate();
        mListView = (ListView) getChildAt(1);
        footer_layout = (LinearLayout) LayoutInflater.from(getContext()).inflate(R.layout.pull_down_list_view_empty, null);
        foot = (LinearLayout) LayoutInflater.from(getContext()).inflate(R.layout.pull_down_list_view_ref, null);
        more = foot.findViewById(R.id.ref);
        mProgressBar2 = foot.findViewById(R.id.refbar);
        mProgressBar2.setVisibility(View.GONE);
        if (useempty) {
            header = (LinearLayout) LayoutInflater.from(getContext()).inflate(R.layout.pull_down_list_view_empty, null);
            mListView.addHeaderView(header);
        }
        mListView.addFooterView(footer_layout);
        foot.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                if (!isAutoLoadMore)
                    onLoadMore();
            }
        });
        mListView.setOnScrollListener(new AbsListView.OnScrollListener() {
            public void onScrollStateChanged(AbsListView view, int scrollState) {
                if (isEnd && scrollState == SCROLL_STATE_IDLE && hasMore
                        && isAutoLoadMore) {
                    onLoadMore();
                }
            }

            public void onScroll(AbsListView view, int f, int v, int t) {
                if (isAutoLoadMore) {
                    if (f + v >= t - 1)
                        isEnd = true;
                    else
                        isEnd = false;
                }
            }
        });
    }
    //添加空的定部view
    public void addEmptyHeaderView() {
        header.removeAllViews();
        if (emptyHeaderView != null)
            header.addView(emptyHeaderView);
    }
    //移除顶部空view
    public void removeEmptyHeaderView() {
        if (emptyHeaderView != null) header.removeView(emptyHeaderView);
    }
    //初始化设置及变量
    @SuppressWarnings("deprecation")
    private void init() {
        MAX_LENGHT = getResources().getDimensionPixelSize(
                R.dimen.updatebar_height);
        setDrawingCacheEnabled(false);
        setBackgroundDrawable(null);
        setClipChildren(false);
        mDetector.setIsLongpressEnabled(false);
        mPading = -MAX_LENGHT;
        mLastTop = -MAX_LENGHT;
    }
    //移动view
    private boolean move(float deltaY, boolean auto) {
        // move 方法执行
        if (deltaY > 0 && mFirstChild.getTop() == -MAX_LENGHT) {
            mPading = -MAX_LENGHT;
            return false;
        }
        if (auto) {
            // move 方法执行
            if (mFirstChild.getTop() - deltaY < mDestPading) {
                deltaY = mFirstChild.getTop() - mDestPading;
            }
            mFirstChild.offsetTopAndBottom((int) -deltaY);
            mListView.offsetTopAndBottom((int) -deltaY);
            mPading = mFirstChild.getTop();
            if (mDestPading == 0 && mFirstChild.getTop() == 0
                    && mState == SCROLL_TO_REFRESH) {
                // onRefresh 刷新方法执行
                onRefresh();
            } else if (mDestPading == -MAX_LENGHT) {
            }
            invalidate();
            updateView();
            return true;
        } else {
            if (mState != STATE_REFRESH
                    || (mState == STATE_REFRESH && deltaY > 0)) {
                mFirstChild.offsetTopAndBottom((int) -deltaY);
                mListView.offsetTopAndBottom((int) -deltaY);
                mPading = mFirstChild.getTop();
            } else if (mState == STATE_REFRESH && deltaY < 0
                    && mFirstChild.getTop() <= 0) {
                if (mFirstChild.getTop() - deltaY > 0) {
                    deltaY = mFirstChild.getTop();
                }
                mFirstChild.offsetTopAndBottom((int) -deltaY);
                mListView.offsetTopAndBottom((int) -deltaY);
                mPading = mFirstChild.getTop();
            }
        }
        if (deltaY > 0 && mFirstChild.getTop() <= -MAX_LENGHT) {
            mPading = -MAX_LENGHT;
            deltaY = -MAX_LENGHT - mFirstChild.getTop();
            mFirstChild.offsetTopAndBottom((int) deltaY);
            mListView.offsetTopAndBottom((int) deltaY);
            mPading = mFirstChild.getTop();
            updateView();
            invalidate();
            return false;
        }
        updateView();
        invalidate();
        return true;
    }
    // 更新视图
    private void updateView() {
        String s = "";
        if (mState != STATE_REFRESH) {
            if (mFirstChild.getTop() < 0) {
                mArrow.setVisibility(View.VISIBLE);
                mProgressBar.setVisibility(View.INVISIBLE);
                mTitle.setText(pulldowntorefresh);
                if (mLastTop >= 0 && mState != SCROLL_TO_CLOSE) {
                    mArrow.startAnimation(mAnimationUp);// 向上移动动画
                }
            } else if (mFirstChild.getTop() > 0) {
                mTitle.setText(releasetorefresh + s);
                mProgressBar.setVisibility(View.INVISIBLE);
                mArrow.setVisibility(View.VISIBLE);
                if (mLastTop <= 0) {
                    mArrow.startAnimation(mAnimationDown);// 向下移动动画
                }
            }
        }
        mLastTop = mFirstChild.getTop();
    }
    // release 方法执行
    private boolean release() {
        if (listviewDoScroll) {
            listviewDoScroll = false;
            return true;
        }
        if (mFirstChild.getTop() > 0) {
            isloading = true;
            scrollToUpdate(false);
        } else {
            isloading = false;
            scrollToClose();
        }
        invalidate();
        return false;
    }
    // 滚动关闭
    private void scrollToClose() {
        mDestPading = -MAX_LENGHT;
        mFlinger.startUsingDistance(MAX_LENGHT, CLOSEDELAY);
    }
    // scrollToUpdate 方法执行
    public void scrollToUpdate(boolean load) {
        mState = SCROLL_TO_REFRESH;
        mDestPading = 0;
        if (load) {
            mFlinger.startUsingDistance(50, REFRESHDELAY);
        } else
            mFlinger.startUsingDistance(mFirstChild.getTop(), REFRESHDELAY);
    }
    // 刷新
    private void onRefresh() {
        Log.e("PullDown", "onRefresh");
        mState = STATE_REFRESH;
        mTitle.setText(loading);
        mProgressBar.setVisibility(View.VISIBLE);
        mArrow.setVisibility(View.INVISIBLE);
        if (mRefreshListioner != null) {
            mRefreshListioner.onRefresh();
        }
    }
    // 刷新完毕
    public void onRefreshComplete() {
        Log.e("PullDown", "onRefreshComplete");
        mState = SCROLL_TO_CLOSE;
        mArrow.setImageResource(R.mipmap.pull_down_list_view_arrow_down);
        mProgressBar2.setVisibility(View.INVISIBLE);
        updateCommon();
        scrollToClose();
    }
    // 设置是否显示更多
    public void setMore(boolean hasMore) {
        if (hasMore) {
            mListView.setFooterDividersEnabled(true);
            footer_layout.removeAllViews();
            footer_layout.addView(foot);
        } else {
            mListView.setFooterDividersEnabled(false);
            footer_layout.removeAllViews();
        }
    }
    // 更新
    private void updateCommon() {
        if (mListView.getCount() == (mListView.getHeaderViewsCount() + mListView.getFooterViewsCount())) {
            Log.e("更新", "数据为空");
            if (useempty)
                addEmptyHeaderView();
        } else {
            removeEmptyHeaderView();
            mListView.setFooterDividersEnabled(false);
            footer_layout.removeAllViews();
        }
    }
    // 加载更多
    public void onLoadMore() {
        // onLoadMore 方法执行
        foot.setEnabled(false);
        mState = STATE_REFRESH;
        mProgressBar2.setVisibility(View.VISIBLE);
        more.setText(loading);
        if (mRefreshListioner != null) {
            mRefreshListioner.onLoadMore();
        }
    }
    // 加载更多完成
    public void onLoadMoreComplete() {
        mState = -1;
        mProgressBar2.setVisibility(View.INVISIBLE);
        more.setText(moreListItem);
        updateCommon();
        if (isFirstLoading)
            isFirstLoading = false;
        foot.setEnabled(true);
    }

    public boolean dispatchTouchEvent(MotionEvent e) {
        Log.e("listview", "dispatchTouchEvent");
        if (isFirstLoading) {
            return false;
        }
        int action;
        float y = e.getY();
        action = e.getAction();
        if (isloading && action == MotionEvent.ACTION_DOWN) {
            return false;
        }
        if (mLongPressing && action != MotionEvent.ACTION_DOWN) {
            return false;
        }

        if (e.getAction() == MotionEvent.ACTION_DOWN) {
            mLongPressing = true;
        }
        boolean handled;
        handled = mDetector.onTouchEvent(e);
        switch (action) {
            case MotionEvent.ACTION_UP:
                boolean f1 = mListView.getTop() <= e.getY()
                        && e.getY() <= mListView.getBottom();
                if (!handled && mFirstChild.getTop() == -MAX_LENGHT && f1
                        || mState == STATE_REFRESH) {
                    super.dispatchTouchEvent(e);
                } else {
                    // 执行释放方法
                    handled = release();
                }
                break;
            case MotionEvent.ACTION_CANCEL:
                handled = release();
                super.dispatchTouchEvent(e);
                break;
            case MotionEvent.ACTION_DOWN:
                mLongPressing = false;
                // 长按的时间间隔
                mPendingRemoved = false;
                super.dispatchTouchEvent(e);
                break;
            case MotionEvent.ACTION_MOVE:
                float deltaY = lastY - y;
                lastY = y;
                if (!mPendingRemoved) {
                    mPendingRemoved = true;
                }
                if (!handled && mFirstChild.getTop() == -MAX_LENGHT) {
                    try {
                        return super.dispatchTouchEvent(e);
                    } catch (Exception e2) {
                        e2.printStackTrace();
                        return true;
                    }
                } else if (handled && mListView.getTop() > 0 && deltaY < 0) {// deltaY小于0，向�?
                    e.setAction(MotionEvent.ACTION_CANCEL);
                    super.dispatchTouchEvent(e);
                }
                break;
            default:
                break;
        }
        return true;
    }

    public boolean onDown(MotionEvent e) {
        return false;
    }

    public boolean onFling(MotionEvent motionevent, MotionEvent e, float f,
                           float f1) {
        return false;
    }

    protected void onLayout(boolean flag, int i, int j, int k, int l) {
        int top = mPading;
        int w = getMeasuredWidth();
        mFirstChild.layout(0, top, w, top + MAX_LENGHT);

        int h = getMeasuredHeight() + mPading + MAX_LENGHT;
        mListView.layout(0, top + MAX_LENGHT, w, h);
    }

    public void onLongPress(MotionEvent e) { }

    public boolean onScroll(MotionEvent curdown, MotionEvent cur, float deltaX, float deltaY) {
        deltaY = (float) ((double) deltaY * SCALE);
        boolean handled;
        boolean flag = false;
        if (mListView.getCount() == 0) {
            flag = true;
        } else {
            View c = mListView.getChildAt(0);
            if (mListView.getFirstVisiblePosition() == 0 && c != null
                    && c.getTop() == 0) {
                flag = true;
            }
        }
        if (deltaY < 0F && flag || getChildAt(0).getTop() > -MAX_LENGHT) { // deltaY
            // <
            // 0
            // 向下
            handled = move(deltaY, false);
        } else
            handled = false;
        return handled;
    }

    public void onShowPress(MotionEvent motionevent) {
    }

    public boolean onSingleTapUp(MotionEvent motionevent) {
        return false;
    }

    public void setRefreshListioner(OnRefreshListioner RefreshListioner) {
        mRefreshListioner = RefreshListioner;
    }
}