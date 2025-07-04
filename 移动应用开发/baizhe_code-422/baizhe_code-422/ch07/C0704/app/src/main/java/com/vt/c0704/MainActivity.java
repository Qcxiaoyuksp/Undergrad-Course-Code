package com.vt.c0704;

import androidx.appcompat.app.AppCompatActivity;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private ContactListAdapter mContactListAdapter;
    private ListView mContactListView;
    private List<ContactModel> mContactModel;
    public EditText mIdEditText;
    public EditText mNameEditText;
    public EditText mPhoneEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //初始化
        this.setTitle("C0704:ContentResolver");
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
        //显示所有联系人
        listAllContacts();
    }
    //显示所有联系人
    private void listAllContacts() {
        mContactModel.clear();
        ContentResolver resolver = this.getContentResolver();
        Uri uri = Uri.parse("content://com.vt.contact/contacts");
        //查询contacts表的所有数据
        Cursor cursor = resolver.query(uri, null, null, null, "name desc");
        //遍历查询结果指针
        while (cursor.moveToNext()) {
            String idQuery = cursor.getString(cursor.getColumnIndex("id"));
            String nameQuery = cursor.getString(cursor.getColumnIndex("name"));
            String phoneQuery = cursor.getString(cursor.getColumnIndex("phone"));
            mContactModel.add(new ContactModel(idQuery, nameQuery, phoneQuery));
        }
        cursor.close();
        //更新ListView
        mContactListAdapter.notifyDataSetChanged();
    }
    //点击事件
    @Override
    public void onClick(View v) {
        String id = mIdEditText.getText().toString();
        String name = mNameEditText.getText().toString();
        String phone = mPhoneEditText.getText().toString();
        Uri uri;
        String selection;
        String[] selectionArgs;
        ArrayList<String> selectionList;
        ContentResolver resolver = this.getContentResolver();
        switch (v.getId()) {
            case R.id.btn_list://显示所有联系人
                listAllContacts();
                break;
            case R.id.btn_insert://添加联系人
                uri = Uri.parse("content://com.vt.contact/contacts");
                //将要插入的数据
                ContentValues values = new ContentValues();
                values.put("name", name);
                values.put("phone", phone);
                //插入数据
                Uri resUri = resolver.insert(uri, values);
                if (resUri == uri) {
                    Toast.makeText(this, "插入失败", Toast.LENGTH_SHORT).show();
                } else {
                    listAllContacts();
                    Toast.makeText(this, "插入成功", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.btn_query://查询联系人
                mContactModel.clear();
                uri = Uri.parse("content://com.vt.contact/contacts");
                //合成查询数据条件的变量值
                selection = (!TextUtils.isEmpty(id) ? "id=?" : "") + (!TextUtils.isEmpty(id) && !TextUtils.isEmpty(name) ? " AND " : "") + (!TextUtils.isEmpty(name) ? "name=?" : "") + ((!TextUtils.isEmpty(id) || !TextUtils.isEmpty(name)) && !TextUtils.isEmpty(phone) ? " AND " : "") + (!TextUtils.isEmpty(phone) ? "phone=?" : "");
                selectionList = new ArrayList<>();
                selectionArgs = new String[selectionList.size()];
                if (!id.equals("")) selectionList.add(id);
                if (!name.equals("")) selectionList.add(name);
                if (!phone.equals("")) selectionList.add(phone);
                selectionList.toArray(selectionArgs);
                //查询数据
                Cursor cursor = resolver.query(uri, null, selection, selectionArgs, "name desc");
                //遍历查询结果指针
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
                if (!id.equals("")) {
                    uri = Uri.parse("content://com.vt.contact/contacts/" + id);
                    //将要更新的数据
                    ContentValues values1 = new ContentValues();
                    values1.put("name", name);
                    values1.put("phone", phone);
                    //更新数据
                    int resUpdate = resolver.update(uri, values1, null, null);
                    if (resUpdate > 0) {
                        listAllContacts();
                        Toast.makeText(this, "更新成功", Toast.LENGTH_SHORT).show();
                    } else {
                        Log.d("aa", "更新失败");
                        Toast.makeText(this, "更新失败", Toast.LENGTH_SHORT).show();
                    }
                }
                break;
            case R.id.btn_delete://删除联系人
                int resDelete = 0;
                if (!id.equals("")) {
                    //根据id删除联系人
                    uri = Uri.parse("content://com.vt.contact/contacts/" + id);
                    resDelete = resolver.delete(uri, null, null);
                } else if (!name.equals("")) {
                    //根据姓名或者同时和电话号码删除联系人
                    uri = Uri.parse("content://com.vt.contact/contacts");
                    resDelete = resolver.delete(uri, "name=?" + (!TextUtils.isEmpty(phone) ? " AND phone=?" : ""), new String[]{name, phone});
                } else if (!phone.equals("")) {
                    //根据电话号码删除联系人
                    uri = Uri.parse("content://com.vt.contact/contacts");
                    resDelete = resolver.delete(uri, "phone=?", new String[]{phone});
                }
                if (resDelete > 0) {
                    listAllContacts();
                    Toast.makeText(this, "删除成功", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(this, "删除失败", Toast.LENGTH_SHORT).show();
                }
                break;
        }
    }
}
