package com.vt.c0806;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;

import androidx.core.app.ActivityCompat;

public class Permissions {
    // 权限请求码
    public static final int REQUEST_PERMISSIONS = 1;
    // 是否已经获取权限
    public static boolean hasPermissionsGranted(Context context, String[] permissions) {
        for (String permission : permissions) {
            // 只要有一个拒绝的申请权限就返回false
            if (ActivityCompat.checkSelfPermission(context, permission) != PackageManager.PERMISSION_GRANTED) {
                return false;
            }
        }
        return true;
    }
    // 请求权限
    public static void requestPermissions(final Context context, String[] permissions) {
        // 如果已经拒绝了权限申请，弹出对话框提示手动开启权限，否则显示权限请求的系统对话框。
        if (shouldShowRequestPermissionRationale(context, permissions)) {
            String msg = "";
            for (int i = 0; i < permissions.length; i++) {
                if (i == 0) {
                    msg = permissions[i];
                } else {
                    msg = msg + "\n" + permissions[i];
                }
            }
            // 自定义对话框
            AlertDialog.Builder adBuilder = new AlertDialog.Builder(context);
            adBuilder.setIcon(R.mipmap.ic_launcher);
            adBuilder.setTitle("需要手动开启以下权限");
            adBuilder.setMessage(msg);
            // 单击确认按钮事件
            adBuilder.setPositiveButton("打开应用设置", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    // 打开应用设置
                    Intent intent = new Intent();
                    intent.setAction("android.settings.APPLICATION_DETAILS_SETTINGS");
                    intent.setData(Uri.fromParts("package", context.getPackageName(), null));
                    context.startActivity(intent);
                    dialog.dismiss();
                }
            });
            adBuilder.show();
        } else {
            // 显示权限请求的系统对话框
            ActivityCompat.requestPermissions((Activity) context, permissions, REQUEST_PERMISSIONS);
        }
    }
    // 获取是否拒绝过权限请求
    public static boolean shouldShowRequestPermissionRationale(Context context, String[] permissions) {
        for (String permission : permissions) {
            // 如果有拒绝的申请权限返回true
            if (ActivityCompat.shouldShowRequestPermissionRationale((Activity) context, permission)) {
                return true;
            }
        }
        return false;
    }
}
