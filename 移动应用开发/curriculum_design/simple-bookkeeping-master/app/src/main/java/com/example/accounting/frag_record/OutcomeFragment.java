package com.example.accounting.frag_record;

import androidx.fragment.app.Fragment;

import com.example.accounting.db.DBManager;
import com.example.accounting.R;
import com.example.accounting.db.TypeBean;
import java.util.List;
/**
 * 2.2A simple {@link Fragment} subclass.
 */
public class OutcomeFragment extends BaseRecordFragment {


    // 重写
    @Override
    public void loadDataToGV() {
        super.loadDataToGV();
        //获取数据库当中的数据源
        List<TypeBean> outlist = DBManager.getTypeList(0);
        typeList.addAll(outlist);
        adapter.notifyDataSetChanged();
        typeTv.setText("其他");
        typeIv.setImageResource(R.mipmap.ic_qita_fs);
    }
//2.2保存数据库
    @Override
    public void saveAccountToDB() {
        accountBean.setKind(0);
        DBManager.insertItemToAccounttb(accountBean);
    }
}