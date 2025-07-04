package com.vt.c0703;

import androidx.appcompat.app.AppCompatActivity;
import android.content.ContentResolver;
import android.content.Context;
import android.database.ContentObserver;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final Uri URI = Uri.parse("content://com.vt.contact/contacts");
    private static final String DATA_BASE_NAME = "contacts.db";
    private static final String TABLE_NAME = "contacts";
    //private Context mContext;
    private Context mContext;
    private SQLiteDatabase mSQLiteDataBase;
    private ContactDBOpenHelper mContactDBOpenHelper;
    private List<ContactModel> mContactModel;
    private ContactListAdapter mContactListAdapter;
    private ListView mContactListView;
    public EditText mIdEditText;
    public EditText mNameEditText;
    public EditText mPhoneEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //初始化
        this.setTitle("C0703:ContentProvider");
        mContext = this;
        mContactDBOpenHelper = new ContactDBOpenHelper(mContext, DATA_BASE_NAME, null, 1);
        mSQLiteDataBase = mContactDBOpenHelper.getWritableDatabase();
        mContactModel = new ArrayList<>();
        mContactListAdapter = new ContactListAdapter(this, mContactModel);
        mContactListView = findViewById(R.id.list_view_contacts);
        mContactListView.setAdapter(mContactListAdapter);
        mIdEditText = findViewById(R.id.edit_text_id);
        mNameEditText = findViewById(R.id.edit_text_name);
        mPhoneEditText = findViewById(R.id.edit_text_phone);
        //设置监听器
        findViewById(R.id.btn_list).setOnClickListener(this);
        findViewById(R.id.btn_insert).setOnClickListener(this);
        findViewById(R.id.btn_query).setOnClickListener(this);
        findViewById(R.id.btn_update).setOnClickListener(this);
        findViewById(R.id.btn_delete).setOnClickListener(this);
        init();
    }
    // 自定义ContentObserver类
    class ContactContentObserver extends ContentObserver {
        public ContactContentObserver(Handler handler) {
            super(handler);
        }
        //ContentProvider.notifyChange()方法后回调该方法
        @Override
        public void onChange(boolean selfChange) {
            super.onChange(selfChange);
            listAllContacts();
        }
    }
    // 初始化
    private void init(){
        //显示所有联系人
        listAllContacts();
        //注册观察者
        ContactContentObserver contactContentObserver = new ContactContentObserver(new Handler());
        ContentResolver contentResolver = this.getContentResolver();
        contentResolver.registerContentObserver(URI,true,contactContentObserver);
    }
    // 显示所有联系人
    private void listAllContacts() {
        mContactModel.clear();
        // 查询所有的联系人按照id降序排列
        Cursor cursor = mSQLiteDataBase.rawQuery("SELECT * FROM " + TABLE_NAME + " order by id desc", null);
        // 遍历查询结果指针
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
                mSQLiteDataBase.execSQL("INSERT INTO " + TABLE_NAME + "(name,phone) values(?,?)", new String[]{name, phone});
                listAllContacts();
                break;
            case R.id.btn_query://查询联系人
                mContactModel.clear();
                Cursor cursor = mSQLiteDataBase.rawQuery("SELECT * FROM " + TABLE_NAME + " WHERE id = ? or name = ? or phone = ?", new String[]{id, name, phone});
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
                mSQLiteDataBase.execSQL("UPDATE " + TABLE_NAME + " SET name = ?,phone = ? WHERE id = ?", new String[]{name, phone, id});
                listAllContacts();
                break;
            case R.id.btn_delete://删除联系人
                mSQLiteDataBase.execSQL("DELETE FROM " + TABLE_NAME + " WHERE id = ?", new String[]{id});
                listAllContacts();
                break;
        }
    }
}
