package com.example.accounting;
//3

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.accounting.adapter.AccountAdapter;
import com.example.accounting.db.AccountBean;
import com.example.accounting.db.DBManager;

import java.util.ArrayList;
import java.util.List;

public class SearchActivity extends AppCompatActivity {
    ListView searchLv;
    EditText searchEt;
    TextView emptyTv;
    List<AccountBean> mDatas;
    AccountAdapter madapter;


    //3
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        init();
        mDatas=new ArrayList<>();
        madapter=new AccountAdapter(this,this.mDatas);
        searchLv.setAdapter(madapter);
        searchLv.setEmptyView(emptyTv);
    }


    //3
    private void init(){
        searchLv=findViewById(R.id.search_lv);
        searchEt=findViewById(R.id.search_et);
        emptyTv=findViewById(R.id.search_tv_empty);
    }

    //3
    public void onClick(View view){
        switch (view.getId()){
            case R.id.search_id_back:
                finish();
                break;
            case R.id.search_iv_sh:
                String msg=searchEt.getText().toString().trim();
                if(TextUtils.isEmpty(msg)){
                    Toast.makeText(this, "输入内容不能为空！", Toast.LENGTH_SHORT).show();
                    return;
                }
                List<AccountBean> list= DBManager.getAccountListByReamrkFromAccountb(msg);
                mDatas.clear();
                mDatas.addAll(list);
                madapter.notifyDataSetChanged();

                break;
        }
    }
}