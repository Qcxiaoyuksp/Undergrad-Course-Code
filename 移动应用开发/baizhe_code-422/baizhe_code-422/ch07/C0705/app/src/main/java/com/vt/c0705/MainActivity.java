package com.vt.c0705;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import android.Manifest;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.OperationApplicationException;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final int OPERATE_LIST = 0;
    private static final int OPERATE_QUERY = 1;
    private static final int OPERATE_INSERT = 2;
    private static final int OPERATE_UPDATE = 3;
    private static final int OPERATE_DELETE = 4;
    private static final Uri rawContactsUri = Uri.parse("content://com.android.contacts/raw_contacts");
    private static final Uri dataUri = Uri.parse("content://com.android.contacts/data");
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
        this.setTitle("C0705:访问和修改系统通讯录数据");
        //初始化
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
        //判断是否获取读取联系人权限
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
            //请求取读取联系人权限
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_CONTACTS}, OPERATE_LIST);
        } else {
            //显示所有联系人
            listContacts();
        }
    }
    //点击事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_list://显示所有联系人
                listContacts();
                break;
            case R.id.btn_query://查询联系人
                //判断是否获取读取联系人权限
                if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                    //请求取读取联系人权限
                    ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_CONTACTS}, OPERATE_QUERY);
                } else {
                    queryContact();
                }
                break;
            case R.id.btn_insert://添加联系人
                //判断是否获取写入联系人权限
                if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                    //请求取写入联系人权限
                    ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_CONTACTS}, OPERATE_INSERT);
                } else {
                    insertContact(true);
                }
                break;
            case R.id.btn_update://更新联系人
                //判断是否获取写入联系人权限
                if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                    //请求取写入联系人权限
                    ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_CONTACTS}, OPERATE_UPDATE);
                } else {
                    updateContact(true);
                }
                break;
            case R.id.btn_delete://删除联系人
                //判断是否获取写入联系人权限
                if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
                    //请求取写入联系人权限
                    ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_CONTACTS}, OPERATE_DELETE);
                } else {
                    deleteContact(true);
                }
                break;
        }
    }
    //权限请求的回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case OPERATE_LIST:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    listContacts();
                } else {
                    Toast.makeText(this, "您没有读取联系人的权限", Toast.LENGTH_SHORT).show();
                }
                break;
            case OPERATE_QUERY:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    queryContact();
                } else {
                    Toast.makeText(this, "您没有查询联系人的权限", Toast.LENGTH_SHORT).show();
                }
                break;
            case OPERATE_INSERT:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    insertContact(true);
                } else {
                    Toast.makeText(this, "您没有添加联系人的权限", Toast.LENGTH_SHORT).show();
                }
                break;
            case OPERATE_UPDATE:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    updateContact(true);
                } else {
                    Toast.makeText(this, "您没有修改联系人的权限", Toast.LENGTH_SHORT).show();
                }
                break;
            case OPERATE_DELETE:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    deleteContact(true);
                } else {
                    Toast.makeText(this, "您没有删除联系人的权限", Toast.LENGTH_SHORT).show();
                }
                break;
            default:
        }
    }
    //查询所有联系人
    private void listContacts() {
        mContactModel.clear();
        ContentResolver resolver = getContentResolver();
        //查询raw_contacts表内存储的联系人
        Cursor rawContactsCursor = resolver.query(rawContactsUri, null, null, null, null);
        //遍历查询结果
        while (rawContactsCursor.moveToNext()) {
            //获取raw_contacts表存储的联系人id和显示名字
            String rawContactId = rawContactsCursor.getString(rawContactsCursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone._ID));
            String displayname = rawContactsCursor.getString(rawContactsCursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME));
            //根据联系人id查询data表内存储的联系人电话号码
            Cursor dataCursor = resolver.query(dataUri, null, "raw_contact_id=? AND mimetype='vnd.android.cursor.item/phone_v2'", new String[]{rawContactId}, null);
            while (dataCursor.moveToNext()) {
                String phone = dataCursor.getString(dataCursor.getColumnIndex("data1"));
                mContactModel.add(new ContactModel(rawContactId, displayname, phone));
            }
        }
        rawContactsCursor.close();
        mContactListAdapter.notifyDataSetChanged();
    }
    //根据显示名字查询联系人
    private void queryContact() {
        String name = mNameEditText.getText().toString().trim();
        ContentResolver resolver = getContentResolver();
        //根据联系人的显示名字搜索
        Cursor rawContactsCursor = resolver.query(rawContactsUri, null, "display_name=?", new String[]{name}, null);
        //判断是否搜索到联系人
        if (rawContactsCursor.getCount() > 0) {
            mContactModel.clear();
            while (rawContactsCursor.moveToNext()) {
                //获取raw_contacts表存储的联系人id和显示名字
                String rawContactId = rawContactsCursor.getString(rawContactsCursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone._ID));
                String displayname = rawContactsCursor.getString(rawContactsCursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME));
                //根据联系人id查询data表内存储的联系人电话号码
                Cursor dataCursor = resolver.query(dataUri, null, "raw_contact_id=? AND mimetype='vnd.android.cursor.item/phone_v2'", new String[]{rawContactId}, null);
                while (dataCursor.moveToNext()) {
                    String phone = dataCursor.getString(dataCursor.getColumnIndex("data1"));
                    mContactModel.add(new ContactModel(rawContactId, displayname, phone));
                }
            }
            Toast.makeText(this, "已经查询到该联系人", Toast.LENGTH_SHORT).show();
            mContactListAdapter.notifyDataSetChanged();
        } else {
            Toast.makeText(this, "没有查询到该联系人", Toast.LENGTH_SHORT).show();
        }
        rawContactsCursor.close();
    }
    //添加联系人
    private void insertContact(boolean useContentProviderOperation) {
        String name = mNameEditText.getText().toString();
        String phone = mPhoneEditText.getText().toString();
        //是否使用ContentProviderOperation
        if (useContentProviderOperation) {
            //向raw_contacts表内插入联系人的操作
            ArrayList<ContentProviderOperation> operations = new ArrayList<>();
            ContentProviderOperation op1 = ContentProviderOperation.newInsert(rawContactsUri)
                    .withValue("account_name", null)
                    .build();
            operations.add(op1);
            //向data表内插入联系人的显示名字的操作
            ContentProviderOperation op2 = ContentProviderOperation.newInsert(dataUri)
                    .withValueBackReference("raw_contact_id", 0)
                    .withValue("mimetype", "vnd.android.cursor.item/name")
                    .withValue("data2", name)
                    .build();
            operations.add(op2);
            //向data表内插入联系人的电话号码的操作
            ContentProviderOperation op3 = ContentProviderOperation.newInsert(dataUri)
                    .withValueBackReference("raw_contact_id", 0)
                    .withValue("mimetype", "vnd.android.cursor.item/phone_v2")
                    .withValue("data1", phone)
                    .build();
            operations.add(op3);
            try {
                ContentResolver resolver = getContentResolver();
                ContentProviderResult[] contentProviderResult = resolver.applyBatch("com.android.contacts", operations);
                //判断是否添加成功
                if (contentProviderResult.length == operations.size()) {
                    Toast.makeText(this, "添加联系人成功", Toast.LENGTH_SHORT).show();
                    listContacts();
                } else {
                    Toast.makeText(this, "添加联系人失败", Toast.LENGTH_SHORT).show();
                }
            } catch (OperationApplicationException e) {
                e.printStackTrace();
                Toast.makeText(this, "添加联系人异常：" + e, Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                e.printStackTrace();
                Toast.makeText(this, "添加联系人异常：" + e, Toast.LENGTH_SHORT).show();
            }
        } else {
            ContentResolver resolver = getContentResolver();
            //向raw_contacts表内插入联系人
            ContentValues value1 = new ContentValues();
            value1.putNull("account_name");
            Uri resultUri = resolver.insert(rawContactsUri, value1);
            int rawContactsId = Integer.valueOf(resultUri.getPathSegments().get(1));
            //向data表内插入联系人的显示名字
            ContentValues value2 = new ContentValues();
            value2.put("raw_contact_id", rawContactsId);
            value2.put("mimetype", "vnd.android.cursor.item/name");
            value2.put("data2", name);
            Uri dataNameUri = resolver.insert(dataUri, value2);
            int dataNameId = Integer.valueOf(dataNameUri.getPathSegments().get(1));
            //向data表内插入联系人的电话号码的操作
            ContentValues value3 = new ContentValues();
            value3.put("raw_contact_id", rawContactsId);
            value3.put("mimetype", "vnd.android.cursor.item/phone_v2");
            value3.put("data1", phone);
            Uri dataPhoneUri = resolver.insert(dataUri, value3);
            int dataPhoneId = Integer.valueOf(dataPhoneUri.getPathSegments().get(1));
            //判断是否添加成功
            if (rawContactsId > 0 && dataNameId > 0 && dataPhoneId > 0) {
                Toast.makeText(this, "添加联系人成功", Toast.LENGTH_SHORT).show();
                listContacts();
            } else {
                Toast.makeText(this, "添加联系人失败或部分失败", Toast.LENGTH_SHORT).show();
            }
        }
    }
    //修改联系人
    private void updateContact(boolean useContentProviderOperation) {
        String id = mIdEditText.getText().toString().trim();
        String name = mNameEditText.getText().toString().trim();
        String phone = mPhoneEditText.getText().toString().trim();
        //是否使用ContentProviderOperation
        if(useContentProviderOperation){
            ArrayList<ContentProviderOperation> operations = new ArrayList<>();
            //根据联系人的id更新raw_contacts表的操作
            ContentProviderOperation op1 = ContentProviderOperation.newUpdate(rawContactsUri)
                    .withValue("display_name", name)
                    .withSelection("_id=?", new String[]{id})
                    .build();
            operations.add(op1);
            //根据联系人的id更新data表
            ContentProviderOperation op2 = ContentProviderOperation.newUpdate(dataUri)
                    .withValue("data1", phone)
                    .withSelection("raw_contact_id=? AND mimetype='vnd.android.cursor.item/phone_v2'", new String[]{id})
                    .build();
            operations.add(op2);
            try {
                ContentResolver resolver = getContentResolver();
                //批量执行操作，并将结果返回。
                ContentProviderResult[] contentProviderResult = resolver.applyBatch("com.android.contacts", operations);
                //判断是否添加成功
                if (contentProviderResult.length == operations.size()) {
                    Toast.makeText(this, "修改联系人成功", Toast.LENGTH_SHORT).show();
                    listContacts();
                } else {
                    Toast.makeText(this, "修改联系人失败", Toast.LENGTH_SHORT).show();
                }
            } catch (OperationApplicationException e) {
                e.printStackTrace();
                Toast.makeText(this, "修改联系人异常：" + e, Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                e.printStackTrace();
                Toast.makeText(this, "修改联系人异常：" + e, Toast.LENGTH_SHORT).show();
            }
        }else{
            ContentResolver resolver = getContentResolver();
            //raw_contacts表将要更新的数据
            ContentValues values1 = new ContentValues();
            values1.put("display_name", name);
            //根据联系人的id更新raw_contacts表
            int resUpdateName = resolver.update(rawContactsUri, values1, "_id=?", new String[]{id});
            //data表将要更新的数据
            ContentValues values2 = new ContentValues();
            values2.put("data1", phone);
            //根据联系人的id更新data表
            int resUpdatePhone = resolver.update(dataUri, values2, "raw_contact_id=? AND mimetype='vnd.android.cursor.item/phone_v2'", new String[]{id});
            if (resUpdateName > 0 && resUpdatePhone > 0) {
                Toast.makeText(this, "修改联系人成功", Toast.LENGTH_SHORT).show();
                listContacts();
            } else {
                Toast.makeText(this, "修改联系人失败或部分失败", Toast.LENGTH_SHORT).show();
            }
        }
    }
    //删除联系人
    private void deleteContact(boolean useContentProviderOperation) {
        String idDelete = mIdEditText.getText().toString();
        //是否使用ContentProviderOperation
        if(useContentProviderOperation){
            ArrayList<ContentProviderOperation> operations = new ArrayList<>();
            //删除raw_contacts表中的联系人数据的操作
            ContentProviderOperation op1 = ContentProviderOperation.newDelete(rawContactsUri)
                    .withSelection("_id=?", new String[]{idDelete})
                    .build();
            operations.add(op1);
            //删除data表中的联系人数据的操作
            ContentProviderOperation op2 = ContentProviderOperation.newDelete(dataUri)
                    .withSelection("raw_contact_id=?", new String[]{idDelete})
                    .build();
            operations.add(op2);
            try {
                ContentResolver resolver = getContentResolver();
                //批量执行操作，并将结果返回。
                ContentProviderResult[] contentProviderResult = resolver.applyBatch("com.android.contacts", operations);
                //判断是否添加成功
                if (contentProviderResult.length == operations.size()) {
                    Toast.makeText(this, "删除联系人成功", Toast.LENGTH_SHORT).show();
                    listContacts();
                } else {
                    Toast.makeText(this, "删除联系人失败", Toast.LENGTH_SHORT).show();
                }
            } catch (OperationApplicationException e) {
                e.printStackTrace();
                Toast.makeText(this, "删除联系人异常：" + e, Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                e.printStackTrace();
                Toast.makeText(this, "删除联系人异常：" + e, Toast.LENGTH_SHORT).show();
            }
        }else{
            ContentResolver resolver = getContentResolver();
            //删除raw_contacts表中的联系人数据，返回值大于0说明有被删除的数据。
            int rawContactsDeleteResult = resolver.delete(rawContactsUri, "_id=?", new String[]{idDelete});
            //删除data表中的联系人数据，返回值大于0说明有被删除的数据。
            int dataDeleteResult = resolver.delete(dataUri, "raw_contact_id=?", new String[]{idDelete});
            //判断是否删除成功
            if(rawContactsDeleteResult>0 && dataDeleteResult>0){
                Toast.makeText(this, "删除联系人成功", Toast.LENGTH_SHORT).show();
                listContacts();
            }else{
                Toast.makeText(this, "删除联系人失败或部分失败", Toast.LENGTH_SHORT).show();
            }
        }
    }
}