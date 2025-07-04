package com.example.accounting;

import android.app.Application;

import com.example.accounting.db.DBManager;


/* 2.2 表示全局应用的类*/
public class  UniteApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        // 初始化数据库
        DBManager.initDB(getApplicationContext());
    }
}
