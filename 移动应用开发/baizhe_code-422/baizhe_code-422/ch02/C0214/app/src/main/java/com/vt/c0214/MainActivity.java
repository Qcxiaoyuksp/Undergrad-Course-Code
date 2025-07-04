package com.vt.c0214;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.media.RingtoneManager;
import android.os.Bundle;
import android.view.View;
import android.widget.RemoteViews;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Context mContext;
    private NotificationManager mNotificationManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext = MainActivity.this;
        mNotificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        findViewById(R.id.btn_show_notification).setOnClickListener(this);
        findViewById(R.id.btn_show_custom_notification).setOnClickListener(this);
        findViewById(R.id.btn_close_notification).setOnClickListener(this);
    }
    // 点击事件监听器
    @SuppressLint("NonConstantResourceId")
    @Override
    public void onClick(View v) {
        String NOTIFY_TAG = "通知";
        String CHANNL_ID1 = "2401";
        String CHANNL_ID2 = "2402";
        Notification.Builder mNotificationBuilder;
        switch (v.getId()) {
            case R.id.btn_show_notification:
                //兼容Android 8.0(API 26)以后的版本
                //if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    String CHANNL_NAME11 = "通知";
                    NotificationChannel notificationChannel = new NotificationChannel(CHANNL_ID1, CHANNL_NAME11, NotificationManager.IMPORTANCE_HIGH);
                    notificationChannel.setShowBadge(true);
                    notificationChannel.enableVibration(true);
                    notificationChannel.enableLights(true);
                    notificationChannel.setSound(RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION), Notification.AUDIO_ATTRIBUTES_DEFAULT);
                    notificationChannel.setVibrationPattern(new long[]{100, 200, 300, 400, 500, 400, 300, 200, 400});
                    mNotificationManager.createNotificationChannel(notificationChannel);
                    mNotificationBuilder = new Notification.Builder(mContext, CHANNL_ID1);
                //} else {
//                    mNotificationBuilder = new Notification.Builder(mContext);
                //}
                //设置通知参数
                mNotificationBuilder.setContentTitle("通知标题：会议通知")
                        .setContentText("通知内容：周五下午1：30在会议室召开全体会议。")
                        .setTicker("收到一条会议信息")
                        .setSmallIcon(R.mipmap.notification_small)
                        .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.mipmap.notification_icon))
                        .setBadgeIconType(Notification.BADGE_ICON_SMALL)
                        .setNumber(11)
                        .setSubText("重要提醒")
                        .setAutoCancel(true);
                Notification mNotification = mNotificationBuilder.build();
                //发出通知
                mNotificationManager.notify(NOTIFY_TAG, Integer.parseInt(CHANNL_ID1), mNotification);
                break;
            case R.id.btn_show_custom_notification:
                // 兼容Android 8.0(API 26)以后的版本
                //if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    String CHANNL_NAME22 = "对话";
                    //NotificationChannel
                    notificationChannel = new NotificationChannel(CHANNL_ID2, CHANNL_NAME22, NotificationManager.IMPORTANCE_HIGH);
                    notificationChannel.setShowBadge(true);
                    notificationChannel.setVibrationPattern(new long[]{100, 200, 300, 400, 500, 400, 300, 200, 400});
                    mNotificationManager.createNotificationChannel(notificationChannel);
                    mNotificationBuilder = new Notification.Builder(mContext, CHANNL_ID2);
                //}
/*
                else {
                    mNotificationBuilder = new Notification.Builder(mContext);
                }
*/
                //设置自定义视图
                PendingIntent pendingIntent = PendingIntent.getActivity(mContext, 1, new Intent(mContext, MainActivity.class), PendingIntent.FLAG_UPDATE_CURRENT);
                RemoteViews remoteView = new RemoteViews(getPackageName(), R.layout.notification_custom);
                remoteView.setImageViewResource(R.id.user_face, R.mipmap.img_user_face);
                remoteView.setOnClickPendingIntent(R.id.btn_reply, pendingIntent);
                //设置通知参数
                mNotificationBuilder.setContentTitle("通知标题：会议通知")
                        .setContentText("通知内容：周五下午1：30在会议室召开全体会议。")
                        .setTicker("收到一条会议信息")
                        .setSmallIcon(R.mipmap.notification_small)
                        .setLargeIcon(BitmapFactory.decodeResource(getResources(), R.mipmap.notification_icon))
                        .setNumber(10)
                        .setVisibility(Notification.VISIBILITY_PUBLIC)
                        .setCustomContentView(remoteView);
                mNotification = mNotificationBuilder.build();
                //发出通知
                mNotificationManager.notify(NOTIFY_TAG, Integer.parseInt(CHANNL_ID2), mNotification);
                break;
            case R.id.btn_close_notification:
                //除了可以根据ID来取消Notification外,还可以调用cancelAll();关闭该应用的所有通知
                mNotificationManager.cancel(NOTIFY_TAG, Integer.parseInt(CHANNL_ID1));
                mNotificationManager.cancel(NOTIFY_TAG, Integer.parseInt(CHANNL_ID2));
                mNotificationManager.deleteNotificationChannel(CHANNL_ID1);
                mNotificationManager.deleteNotificationChannel(CHANNL_ID2);
                break;
        }
    }
}
