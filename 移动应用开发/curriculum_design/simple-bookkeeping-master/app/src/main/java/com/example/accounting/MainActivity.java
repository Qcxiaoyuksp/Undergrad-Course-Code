package com.example.accounting;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.method.HideReturnsTransformationMethod;
import android.text.method.PasswordTransformationMethod;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.accounting.adapter.AccountAdapter;
import com.example.accounting.db.AccountBean;
import com.example.accounting.db.DBManager;
import com.example.accounting.utils.BudgetDialog;
import com.example.accounting.utils.MoreDialog;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    ListView todayLv;  //展示今日收支情况的ListView
    ImageView searchIv;
    Button editBtn;
    ImageButton moreBtn;
    //声明数据源
    List<AccountBean>mDatas;
    AccountAdapter adapter;
    int year,month,day;
    //头布局相关控件
    View headerView;
    TextView topOutTv,topInTv,topbudgetTv,topConTv;
    ImageView topShowIv;
    SharedPreferences preferences;



    /**
     *
     * 1.2 改
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initTime();
        initView();
        preferences = getSharedPreferences("budget", Context.MODE_PRIVATE);
        //给ListView(收支明细页面)添加头布局的方法
        addLVHeaderView();
        mDatas = new ArrayList<>();
        //设置适配器：加载每一行数据到列表当中
        adapter = new AccountAdapter(this, mDatas);
        todayLv.setAdapter(adapter);
    }

    /**
     * 1.1 初始化控件
     * 1.2 改
     */
    private void initView() {
        todayLv = findViewById(R.id.main_lv);
        editBtn = findViewById(R.id.main_btn_edit);
        moreBtn = findViewById(R.id.main_btn_more);
        searchIv = findViewById(R.id.main_iv_search);
        editBtn.setOnClickListener(this);
        moreBtn.setOnClickListener(this);
        searchIv.setOnClickListener(this);
        setLVLongClickListener();
    }

    /**
     * 1.1 设置ListView的长按事件
     * 1.2 改
     */
    private void setLVLongClickListener() {
        todayLv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                if (i == 0) {
                    //点击了头布局
                    return false;
                }
                int pos = i - 1;
                AccountBean clickBean = mDatas.get(pos);    //获取正在被点击的信息
                //弹出提示用户是否删除的对话框
                showDeleteItemDialog(clickBean);
                return false;
            }
        });
    }

    /**
     * 1.2 弹出是否删除某一条记录的对话框
     */
    private void showDeleteItemDialog(AccountBean clickBean) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("提示信息")
                .setMessage("您确定要删除这条记录吗")
                .setNegativeButton("取消",null)
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        //执行删除的操作
                        DBManager.deleteItemFromAccounttbById(clickBean.getId());
                        mDatas.remove(clickBean);   //实时刷新，移除集合中的对象
                        adapter.notifyDataSetChanged();     //提示适配器更新数据
                        setTopTvShow();     //改变头布局TextView显示的内容
                    }
                });
        builder.create().show();
    }

    /*1.1 获取今日的具体时间*/
    private void initTime() {
        Calendar calendar = Calendar.getInstance();
        year = calendar.get(Calendar.YEAR);
        month = calendar.get(Calendar.MONTH)+1;
        day = calendar.get(Calendar.DAY_OF_MONTH);
    }

    /**
     * 1.2 给ListView(收支明细页面)添加头布局的方法
     */
    private void addLVHeaderView(){
        //将布局转化成View对象
        headerView = getLayoutInflater().inflate(R.layout.item_mainlv_top, null);
        todayLv.addHeaderView(headerView);
        //查找头布局可用部件
        topOutTv = headerView.findViewById(R.id.item_mainlv_top_tv_out);
        topInTv = headerView.findViewById(R.id.item_mainlv_top_tv_in);
        topbudgetTv = headerView.findViewById(R.id.item_mainlv_top_tv_budget);
        topConTv = headerView.findViewById(R.id.item_mainlv_top_tv_day);
        topShowIv = headerView.findViewById(R.id.item_mainlv_top_iv_hide);
        //设置点击监听
        topbudgetTv.setOnClickListener(this);
        headerView.setOnClickListener(this);
        topShowIv.setOnClickListener(this);

    }

    // 1.1 当activity获取焦点时，会调用的方法
    //1.2 改
    @Override
    protected void onResume() {
        super.onResume();
        loadDBData();
        setTopTvShow();
    }

    /**
     * 1.2 设置头布局当中文本内容的显示
     */
    private void setTopTvShow() {
        //获取今日支出和收入总金额，显示在view中
        float incomeOneDay = DBManager.getSumMoneyOneDay(year, month, day, 1);
        float outcomeOneDay = DBManager.getSumMoneyOneDay(year, month, day, 0);
        String infoOneDay = "今日支出 ￥" + outcomeOneDay + " 收入 ￥" + incomeOneDay;
        topConTv.setText(infoOneDay);
        //获取本月收入和支出总金额
        float incomeOneMonth = DBManager.getSumMoneyOneMonth(year, month, 1);
        float outcomeOneMonth = DBManager.getSumMoneyOneMonth(year, month, 0);
        topInTv.setText("￥" + incomeOneMonth);
        topOutTv.setText("￥" + outcomeOneMonth);
        //设置显示预算剩余
        float money = preferences.getFloat("bmoney",0);

        if (money == 0) {
            topbudgetTv.setText("￥ 0");
        }else {
            float syMoney = money - outcomeOneMonth;
            topbudgetTv.setText("￥" + syMoney);
        }
    }

    //1.1 加载数据库数据
    private void loadDBData() {
        List<AccountBean> list = DBManager.getAccountListOneDayFromAccounttb(year, month, day);
        mDatas.clear();
        mDatas.addAll(list);
        adapter.notifyDataSetChanged();
    }

    /**
     * 1.1
     * 2.2
     * 1.2 改 设置点击事件
     * 3
     * @param view
     */
    @Override
    public void onClick(View view){
        switch (view.getId()){
            case R.id.main_iv_search:
                Intent it = new Intent(this, SearchActivity.class);  //跳转界面
                startActivity(it);
                break;
            case R.id.main_btn_edit:
                Intent it1 = new Intent(this, RecordActivity.class);  //跳转界面
                startActivity(it1);
                break;
            case R.id.main_btn_more:
                MoreDialog moreDialog = new MoreDialog(this);
                moreDialog.show();
                moreDialog.setDialogSize();
                break;
            case R.id.item_mainlv_top_tv_budget:
                showBudgetDialog();
                break;
            case R.id.item_mainlv_top_iv_hide:
                //切换明文和密文
                toggleShow();

                break;
        }
        if (view == headerView) {
            //点击头布局
            Intent intent=new Intent();
            intent.setClass(this, MonthChartActivity.class);
            startActivity(intent);
        }
    }

    /**
     * 1.2 显示预算设置对话框
     */
    private void showBudgetDialog() {
        BudgetDialog dialog = new BudgetDialog(this);
        dialog.show();
        dialog.setDialogSize();
        dialog.setOnEnsureListener(new BudgetDialog.OnEnsureListener() {
            @Override
            public void onEnsure(float money) {
                //将预算金额写入到SharedPreferences中，进行存储
                SharedPreferences.Editor editor = preferences.edit();
                editor.putFloat("bmoney",money);
                editor.commit();

                //计算剩余金额
                float outcomeOneMonth = DBManager.getSumMoneyOneMonth(year, month, 0);
                //预算剩余 = 预算 - 支出
                float syMoney = money - outcomeOneMonth;
                topbudgetTv.setText("￥" + syMoney);
            }
        });
    }

    boolean isShow = true;
    /**
     * 1.2 点击头布局眼睛时，如果原来是明文，就加密，如果是密文，就显示出来
     */
    private void toggleShow() {
        if (isShow) {
            //明文 ——> 密文
            //设置隐藏
            PasswordTransformationMethod passwordMethod = PasswordTransformationMethod.getInstance();
            topInTv.setTransformationMethod(passwordMethod);
            topOutTv.setTransformationMethod(passwordMethod);
            topbudgetTv.setTransformationMethod(passwordMethod);
            topShowIv.setImageResource(R.mipmap.ih_hide);
            //设置状态为隐藏
            isShow = false;
        }else{
            //密文 ——> 明文
            //设置隐藏
            HideReturnsTransformationMethod hideMethod = HideReturnsTransformationMethod.getInstance();
            topInTv.setTransformationMethod(hideMethod);
            topOutTv.setTransformationMethod(hideMethod);
            topbudgetTv.setTransformationMethod(hideMethod);
            topShowIv.setImageResource(R.mipmap.ih_show);
            //设置状态为显示
            isShow = true;
        }
    }
}