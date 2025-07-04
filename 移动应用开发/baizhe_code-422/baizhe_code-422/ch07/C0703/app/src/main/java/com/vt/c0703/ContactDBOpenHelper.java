package com.vt.c0703;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class ContactDBOpenHelper extends SQLiteOpenHelper {
    public ContactDBOpenHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE contacts(id INTEGER PRIMARY KEY AUTOINCREMENT,name VARCHAR(16),phone VARCHAR(11))");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        if (newVersion > oldVersion) {
            db.execSQL("ALTER TABLE contacts ADD notes VARCHAR(20)");
        }
    }
}
