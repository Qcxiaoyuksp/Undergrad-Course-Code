package com.vt.c0906;

import androidx.appcompat.app.AppCompatActivity;
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

public class DailyListActivity extends AppCompatActivity {
    public static final String DOMAIN = "http://www.weiju2014.com/teachol/android/";
    private String url = DOMAIN + "DailyList.php";
    private static final int MSG_NETERROR = 0;
    private static final int MSG_SUCCESS = 1;
    private static final int MSG_NONDATA = 2;
    private Context mContext = this;
    private ListView mListView;
    private DailyListViewAdapter mAdapter;
    private DailyModel mDailyModel = new DailyModel();
    private int mMaxAount = 20;//设置动态最大显示数量
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_daily_list);
        this.setTitle("动态列表");
        mContext = this;
        mAdapter = new DailyListViewAdapter(DOMAIN,mContext, mDailyModel, R.layout.list_view_item_daily_list);
        mListView = findViewById(R.id.list_view);
        mListView.setAdapter(mAdapter);
        loader(mMaxAount,0);
    }
    // 加载启动线程
    public void loader(int n, int start) {
        LoaderThread loaderThread = new LoaderThread();
        loaderThread.n = n;
        loaderThread.start = start;
        loaderThread.start();
    }
    // 加载线程
    public class LoaderThread extends Thread {
        private int n;
        private int start;
        @Override
        public void run() {
            addLists(n, start);
        }
    }
    // 获取加载数据
    private int addLists(int n, int start) {
        int num = 0;
        try {
            String res = Http.get(url, "?&num=" + n + "&start=" + start);//获取动态列表数据
            // 解析JSON数据
            JSONTokener jsonParser = new JSONTokener(res.trim());
            JSONObject person = (JSONObject) jsonParser.nextValue();
            Log.e("json", person.getString("state"));
            if (person.getString("state").equals("ok")) {
                JSONArray jsonObject = new JSONArray(person.getString("dailyList"));
                num = jsonObject.length();
                for (int i = 0; i < jsonObject.length(); i++) {
                    JSONObject jo = (JSONObject) jsonObject.opt(i);
                    mDailyModel.ides.add(jo.getString("Id"));
                    mDailyModel.names.add(jo.getString("Name"));
                    mDailyModel.contents.add(jo.getString("Content"));
                    mDailyModel.images.add(jo.getString("Image"));
                    mDailyModel.createTimes.add(jo.getString("CreateTime"));
                }
                mHandler.obtainMessage(MSG_SUCCESS).sendToTarget();
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
                case MSG_NETERROR://网络连接失败
                    Toast.makeText(mContext, "网络连接失败", Toast.LENGTH_LONG).show();
                    break;
                case MSG_SUCCESS://加载
                    mAdapter.notifyDataSetChanged();
                    break;
                case MSG_NONDATA://没有
                    break;
            }
        }
    };
}
