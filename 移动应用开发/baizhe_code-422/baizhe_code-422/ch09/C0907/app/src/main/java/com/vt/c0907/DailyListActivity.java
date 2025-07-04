package com.vt.c0907;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.ListView;
import android.widget.Toast;
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;
import androidx.appcompat.app.AppCompatActivity;

public class DailyListActivity extends AppCompatActivity implements PullDownListView.OnRefreshListioner {
    public static final String DOMAIN = "http://www.weiju2014.com/teachol/android/";
    private String url = DOMAIN + "DailyList.php";
    private static final int MSG_NETERROR = 0;
    private static final int MSG_FRESH_SUCCESS = 1;
    private static final int MSG_MORE_SUCCESS = 2;
    private static final int MSG_NONDATA = 3;
    private static final int MSG_UPDATE = 4;
    private Context mContext = this;
    private DailyModel mDailyModel = new DailyModel();
    private PullDownListView mPullDownView;
    private ListView mListView;
    private PullDownListViewAdapterDailyList adapter;
    private int mMaxAount = 500;//设置了最大数据值
    private int mListCount = 30;//设置显示数据数量
    private int mNumList;//加载数量
    private int mAddCount = 1;//加载次数
    private boolean init = true;//是否已经初始化
    private boolean loading;//是否正在加载数据
    private boolean bgRun;//是否后台运行

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_daily_list);
        this.setTitle("动态列表");

        mPullDownView = findViewById(R.id.sreach_list);
        mPullDownView.setRefreshListioner(this);
        if (init) {
            adapter = new PullDownListViewAdapterDailyList(DOMAIN,mContext, mDailyModel, R.layout.pull_down_list_view_item_daily_list);
            mPullDownView.isloading = false;
            loading = false;
            mPullDownView.scrollToUpdate(false);
        }
        mListView = mPullDownView.mListView;
        mListView.setAdapter(adapter);
    }

    @Override
    public void onResume() {
        super.onResume();
        if (init) {
            init = false;
        } else {
            mPullDownView.onRefreshComplete();// 这里表示刷新处理完成后把上面的加载刷新界面隐藏
            bgRun = false;
        }
    }

    @Override
    public void onPause() {
        super.onPause();
        bgRun = true;
    }
    // 刷新
    @Override
    public void onRefresh() {
        if (!loading) {
            mPullDownView.isloading = true;
            loading = true;
            loader(mListCount, 0);
        }
    }
    // 加载更多
    @Override
    public void onLoadMore() {
        loaderMore(mListCount, mAddCount * mListCount);
    }
    // 加载启动进程
    public void loader(int n, int start) {
        LoaderThread loaderThread = new LoaderThread();
        loaderThread.n = n;
        loaderThread.start = start;
        loaderThread.start();
    }
    // 加载进程
    public class LoaderThread extends Thread {
        private int n;
        private int start;

        @Override
        public void run() {
            mNumList = addLists(n, start, true);
            mAddCount = 1;
        }
    }
    // 加载更多
    public void loaderMore(int n, int start) {
        LoaderMoreThread loaderMoreThread = new LoaderMoreThread();
        loaderMoreThread.n = n;
        loaderMoreThread.start = start;
        loaderMoreThread.start();
    }
    // 启动加载更多进程
    public class LoaderMoreThread extends Thread {
        private int n;
        private int start;

        @Override
        public void run() {
            mNumList = addLists(n, start, false);
            mAddCount++;
        }
    }
    // 获取加载数据
    private int addLists(int n, int start, boolean fresh) {
        int num = 0;
        try {
            String res = Http.get(url, "?num=" + n + "&start=" + start);
            JSONTokener jsonParser = new JSONTokener(res.trim());
            JSONObject person = (JSONObject) jsonParser.nextValue();
            Log.e("json", person.getString("state"));
            if (person.getString("state").equals("ok")) {
                JSONArray jsonObject = new JSONArray(person.getString("dailyList"));
                num = jsonObject.length();
                if (fresh) {
                    mDailyModel.ides.clear();
                    mDailyModel.names.clear();
                    mDailyModel.contents.clear();
                    mDailyModel.images.clear();
                    mDailyModel.createTimes.clear();
                    mAddCount = 1;
                }
                for (int i = 0; i < jsonObject.length(); i++) {
                    JSONObject jo = (JSONObject) jsonObject.opt(i);
                    mDailyModel.ides.add(jo.getString("Id"));
                    mDailyModel.names.add(jo.getString("Name"));
                    mDailyModel.contents.add(jo.getString("Content"));
                    mDailyModel.images.add(jo.getString("Image"));
                    mDailyModel.createTimes.add(jo.getString("CreateTime"));
                }
                if (fresh) {
                    mHandler.obtainMessage(MSG_FRESH_SUCCESS).sendToTarget();
                } else {
                    mHandler.obtainMessage(MSG_MORE_SUCCESS).sendToTarget();
                }
            } else {
                mHandler.obtainMessage(MSG_NONDATA).sendToTarget();
            }
        } catch (Exception e) {
            e.printStackTrace();
            mHandler.obtainMessage(MSG_NETERROR).sendToTarget();
        }
        return num;
    }
    // 更新UI
    private Handler mHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_NETERROR: // 网络连接失败
                    Toast.makeText(mContext, "网络连接失败", Toast.LENGTH_LONG).show();
                    mPullDownView.onRefreshComplete();
                    break;
                case MSG_FRESH_SUCCESS: // 加载
                    if (!bgRun) {
                        mPullDownView.onRefreshComplete();// 这里表示刷新处理完成后把上面的加载刷新界面隐藏
                        if (mNumList == 0 || mNumList < mListCount) {
                            mPullDownView.setMore(false);
                        } else {
                            mPullDownView.setMore(true);// 这里设置true表示还有更多加载，设置为false底部将不显示更多
                        }
                        adapter.notifyDataSetChanged();
                    }
                    break;
                case MSG_MORE_SUCCESS:
                    mPullDownView.onLoadMoreComplete();// 这里表示加载更多处理完成后把下面的加载更多界面（隐藏或者设置字样更多）
                    if (mDailyModel.ides.size() < mMaxAount)// 判断当前list中已添加的数据是否小于最大值maxAount，是那么久显示更多否则不显示
                        mPullDownView.setMore(true);// 这里设置true表示还有更多加载，设置为false底部将不显示更多
                    else
                        mPullDownView.setMore(false);
                    if (!bgRun) {
                        adapter.notifyDataSetChanged();
                    }
                    break;
                case MSG_NONDATA: // 没有
                    mPullDownView.onRefreshComplete();
                    break;
                case MSG_UPDATE: // 更新
                    adapter.notifyDataSetChanged();
                    break;
            }
            mPullDownView.isloading = false;
            loading = false;
        }
    };
}
