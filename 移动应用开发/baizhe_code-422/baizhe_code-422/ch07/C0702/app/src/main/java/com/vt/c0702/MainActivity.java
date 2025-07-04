package com.vt.c0702;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    public EditText mIdEditText;
    public EditText mNameEditText;
    public EditText mPhoneEditText;

    private Context mContext;
    private SQLiteDatabase mSQLiteDataBase;
    private ContactSQLiteOpenHelper mContactSQLiteOpenHelper;
    private String mDataBaseName = "contacts.db";
    private String mTableName = "contacts";
    private List<ContactModel> mContactModel;
    private ContactListAdapter mContactListAdapter;
    private ListView mContactListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.setTitle("自定义通讯录");
        mContext = this;
        mContactModel = new ArrayList<>();
        mContactListView = findViewById(R.id.list_view_contacts);
        mIdEditText = findViewById(R.id.edit_text_id);
        mNameEditText = findViewById(R.id.edit_text_name);
        mPhoneEditText = findViewById(R.id.edit_text_phone);
        findViewById(R.id.btn_list).setOnClickListener(this);
        findViewById(R.id.btn_insert).setOnClickListener(this);
        findViewById(R.id.btn_query).setOnClickListener(this);
        findViewById(R.id.btn_update).setOnClickListener(this);
        findViewById(R.id.btn_delete).setOnClickListener(this);
        init();
    }
    // 初始化
    private void init(){
        mContactSQLiteOpenHelper = new ContactSQLiteOpenHelper(mContext, mDataBaseName, null, 1);
        mSQLiteDataBase = mContactSQLiteOpenHelper.getWritableDatabase();
        mContactListAdapter = new ContactListAdapter(this, mContactModel);
        mContactListView.setAdapter(mContactListAdapter);
        listAllContacts();
    }
    // 显示所有联系人
    private void listAllContacts() {
        mContactModel.clear();
        Cursor cursor = mSQLiteDataBase.rawQuery("SELECT * FROM " + mTableName + " order by id desc", null);
        while (cursor.moveToNext()) {
            String id = cursor.getString(cursor.getColumnIndex("id"));
            String name = cursor.getString(cursor.getColumnIndex("name"));
            String phone = cursor.getString(cursor.getColumnIndex("phone"));
            mContactModel.add(new ContactModel(id, name, phone));
        }
        cursor.close();
        // 更新ListView
        mContactListAdapter.notifyDataSetChanged();
    }

    @Override
    public void onClick(View v) {
        String id = mIdEditText.getText().toString();
        String name = mNameEditText.getText().toString();
        String phone = mPhoneEditText.getText().toString();
        switch (v.getId()) {
            case R.id.btn_list://显示所有联系人
                listAllContacts();
                break;
            case R.id.btn_insert://添加联系人
                mSQLiteDataBase.execSQL("INSERT INTO " + mTableName + "(name,phone) values(?,?)", new String[]{name, phone});
                listAllContacts();
                break;
            case R.id.btn_query://查询联系人
                mContactModel.clear();
                Cursor cursor = mSQLiteDataBase.rawQuery("SELECT * FROM " + mTableName + " WHERE id = ? or name = ? or phone = ?", new String[]{id, name, phone});
                while (cursor.moveToNext()) {
                    String idQuery = cursor.getString(cursor.getColumnIndex("id"));
                    String nameQuery = cursor.getString(cursor.getColumnIndex("name"));
                    String phoneQuery = cursor.getString(cursor.getColumnIndex("phone"));
                    mContactModel.add(new ContactModel(idQuery, nameQuery, phoneQuery));
                }
                cursor.close();
                mContactListAdapter.notifyDataSetChanged();
                break;
            case R.id.btn_update://更新联系人
                mSQLiteDataBase.execSQL("UPDATE " + mTableName + " SET name = ?,phone = ? WHERE id = ?", new String[]{name, phone, id});
                listAllContacts();
                break;
            case R.id.btn_delete://删除联系人
                mSQLiteDataBase.execSQL("DELETE FROM " + mTableName + " WHERE id = ?", new String[]{id});
                listAllContacts();
                break;
        }
    }
}
