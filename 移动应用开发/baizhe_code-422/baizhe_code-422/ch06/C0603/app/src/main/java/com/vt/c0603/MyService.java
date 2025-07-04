package com.vt.c0603;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.widget.RemoteViews;

public class MyService extends Service {
    private final String CHANNL_ID = "1231";
    private final String CHANNL_NAME = "音乐";
    private NotificationManager mNotificationManager;
    private NotificationChannel mNotificationChannel;
    private Notification.Builder mNotificationBuilder;
    private Notification mNotification;
    @Override
    public IBinder onBind(Intent intent) {
        throw new UnsupportedOperationException("Not yet implemented");
    }
    public void onCreate() {
        super.onCreate();
        //自定义远程视图
        RemoteViews remoteView = new RemoteViews(getPackageName(), R.layout.notification_custom);
        remoteView.setImageViewResource(R.id.image_view_music, R.mipmap.ic_notification_music);
        remoteView.setImageViewResource(R.id.image_view_stop, R.mipmap.ic_notification_stop);
        //设置通知
        mNotificationChannel = new NotificationChannel(CHANNL_ID, CHANNL_NAME, NotificationManager.IMPORTANCE_DEFAULT);
        mNotificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        mNotificationManager.createNotificationChannel(mNotificationChannel);
        mNotificationBuilder = new Notification.Builder(this, CHANNL_ID);
        mNotificationBuilder.setSmallIcon(R.mipmap.ic_notification_small)
                .setCustomBigContentView(remoteView);
        mNotification = mNotificationBuilder.build();
        //前台启动通知
        startForeground(1, mNotification);
    }
}
