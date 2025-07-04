package com.vt.c0703;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.text.TextUtils;

public class ContactContentProvider extends ContentProvider {
    private static final String AUTHORITIES = "com.vt.contact";
    private static final UriMatcher URI_MATCHER;
    private static final int CONTACTS_TABLE = 1;
    private static final int CONTACTS_TABLE_AND_ID = 2;
    private static ContactDBOpenHelper mContactDBOpenHelper;
    private static SQLiteDatabase mSQLiteDatabase;
    private static String mDataBaseName = "contacts.db";
    //static代码块,只会在类加载的时候执行一次,优化系统性能。
    static {
        URI_MATCHER = new UriMatcher(UriMatcher.NO_MATCH);
        URI_MATCHER.addURI(AUTHORITIES, "contacts", CONTACTS_TABLE);
        URI_MATCHER.addURI(AUTHORITIES, "contacts/#", CONTACTS_TABLE_AND_ID);
    }
    //创建时调用
    @Override
    public boolean onCreate() {
        //实例化ContactDBOpenHelper
        mContactDBOpenHelper = new ContactDBOpenHelper(this.getContext(), mDataBaseName, null, 1);
        //获取具有写入权限的SQLite数据库
        mSQLiteDatabase = mContactDBOpenHelper.getWritableDatabase();
        return true;
    }
    //插入
    @Override
    public Uri insert(Uri uri, ContentValues values) {
        String tableName = uri.getPathSegments().get(0);
        //插入联系人成功后将联系人的id保存在rowID
        long rowID = mSQLiteDatabase.insert(tableName, "", values);
        //rowID值大于0表示插入成功
        if (rowID > 0) {
            //将联系人id附加到URI
            uri = ContentUris.withAppendedId(uri, rowID);
            //向发送URI的ContentResolver对象改变的通知
            getContext().getContentResolver().notifyChange(uri, null);
        }
        return uri;
    }
    //更新
    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        int count = 0;
        //获取URI中附加的联系人id
        String id = uri.getPathSegments().get(1);
        //更新数据后将更新的行数赋值给count
        count = mSQLiteDatabase.update(uri.getPathSegments().get(0), values, "id= " + id + (!TextUtils.isEmpty(selection) ? " AND (" + selection + ')' : ""), selectionArgs);
        //向发送URI的ContentResolver对象改变的通知
        getContext().getContentResolver().notifyChange(uri, null);
        return count;
    }
    //删除
    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        int count = 0;
        String tableName = uri.getPathSegments().get(0);
        //判断URI匹配的常量值
        switch (URI_MATCHER.match(uri)) {
            case CONTACTS_TABLE:
                //根据name和phone判断删除联系人并将删除的联系人数据行数赋值给count
                count = mSQLiteDatabase.delete(tableName, selection, selectionArgs);
                break;
            case CONTACTS_TABLE_AND_ID:
                //获取要删除的联系人id
                String id = uri.getPathSegments().get(1);
                //根据id删除联系人
                count = mSQLiteDatabase.delete(tableName, "id = " + id , selectionArgs);
                break;
            default:
                throw new IllegalArgumentException("Unknown URI " + uri);
        }
        getContext().getContentResolver().notifyChange(uri, null);
        return count;
    }
    //查询
    @Override
    public Cursor query(Uri uri, String[] columns, String selection, String[] selectionArgs, String sortOrder) {
        //获取联系人的id
        String tableName = uri.getPathSegments().get(0);
        //将查询结果的指针赋值给cursor
        Cursor cursor = mSQLiteDatabase.query(tableName, columns, selection, selectionArgs, null, null, sortOrder);
        return cursor;
    }
    //通过URI获取MIME类型
    @Override
    public String getType(Uri uri) {
        int match = URI_MATCHER.match(uri);
        switch (match) {
            case CONTACTS_TABLE:
                //vnd.android.cursor.dir表示数据集合
                return "vnd.android.cursor.dir/contacts";
            case CONTACTS_TABLE_AND_ID:
                //vnd.android.cursor.item表示一组数据
                return "vnd.android.cursor.item/contacts";
            default:
                return null;
        }
    }
}
