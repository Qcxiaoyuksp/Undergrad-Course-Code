package com.vt.c0801;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.FileProvider;
import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.ImageView;
import java.io.File;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final int REQUEST_CODE_TAKE_PHOTO_DEFAULT = 0;
    private static final int REQUEST_CODE_TAKE_PHOTO_CUSTOM = 1;
    private static final int REQUEST_CODE_SELECT = 2;
    private static final int REQUEST_CODE_CROP = 3;
    private Context mContext = this;
    private File mPhotoFile;
    // 需要请求的权限
    private static final String[] PERMISSIONS = {
            Manifest.permission.CAMERA,
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // 初始化
        this.setTitle("C0801:拍照、选取和显示图片");
        findViewById(R.id.button_take_photo_default).setOnClickListener(this);
        findViewById(R.id.button_take_photo_custom).setOnClickListener(this);
        findViewById(R.id.button_select_photo).setOnClickListener(this);
        // 判断是否已经取得权限
        if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
            // 请求权限
            Permissions.requestPermissions(mContext, PERMISSIONS);
        }
    }
    // 请求权限的回调
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case Permissions.REQUEST_PERMISSIONS:
                if (!Permissions.hasPermissionsGranted(mContext, PERMISSIONS)) {
                    Permissions.requestPermissions(mContext, PERMISSIONS);
                }
                break;
        }
    }
    // 点击事件
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button_take_photo_default: {
                takePhotoDefault();
                break;
            }
            case R.id.button_take_photo_custom: {
                takePhotoCustom();
                break;
            }
            case R.id.button_select_photo: {
                selectPhoto();
                break;
            }
        }
    }
    // 系统相机拍照，使用默认保存路径。
    private void takePhotoDefault() {
        // 调用系统相机拍照
        Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        startActivityForResult(intent, REQUEST_CODE_TAKE_PHOTO_DEFAULT);
    }
    // 系统相机拍照，照片保存到指定路径。
    private void takePhotoCustom() {
        // 创建文件
        mPhotoFile = Util.createFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "jpg");
        if (mPhotoFile != null) {
            // 获取"com.vt.c0801.fileprovider"授权路径下的mPhotoFile文件的Uri
            Uri photoURI = FileProvider.getUriForFile(this, "com.vt.c0801.fileprovider", mPhotoFile);
            // 调用系统相机拍照
            Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            intent.putExtra(MediaStore.EXTRA_OUTPUT, photoURI);// 设置保存文件的Uri地址
            startActivityForResult(intent, REQUEST_CODE_TAKE_PHOTO_CUSTOM);
        }
    }
    // 调用系统相册选择图片
    public void selectPhoto() {
        Intent intent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        intent.setType("image/*");
        startActivityForResult(intent, REQUEST_CODE_SELECT);
    }
    //  Activity回调
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
        if (requestCode == REQUEST_CODE_TAKE_PHOTO_DEFAULT && resultCode == RESULT_OK) {
            // 从data中取出传递回来缩略图的信息，图片质量差，适合传递小图片
            Bundle bundle = intent.getExtras();
            Bitmap bitmap = bundle.getParcelable("data");
            // 显示照片
            ((ImageView) findViewById(R.id.image_view)).setImageBitmap(bitmap);
        } else if (requestCode == REQUEST_CODE_TAKE_PHOTO_CUSTOM && resultCode == RESULT_OK) {
            // 显示照片
            ((ImageView) findViewById(R.id.image_view)).setImageURI(Uri.fromFile(mPhotoFile));
            // 扫描更新相册
            Util.showInAlbum(mContext, mPhotoFile.getAbsolutePath());
        } else if (requestCode == REQUEST_CODE_SELECT && resultCode == RESULT_OK) {
            // 新建保存裁剪照片的文件
            mPhotoFile = Util.createFile(mContext.getExternalMediaDirs()[0].getAbsolutePath(), mContext.getResources().getString(R.string.app_name), "jpg");
            // 裁剪照片
            Intent cropIntent = new Intent("com.android.camera.action.CROP");
            cropIntent.setDataAndType(intent.getData(), "image/*");
            cropIntent.putExtra("crop", "true");
            // 设置裁剪的比例
            cropIntent.putExtra("aspectX", 1);
            cropIntent.putExtra("aspectY", 1);
            // 设置裁剪后保存图片的尺寸
            cropIntent.putExtra("outputX", 500);
            cropIntent.putExtra("outputY", 500);
            // 设置保存图片的文件格式
            cropIntent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());
            // 设置保存图片的文件路径
            cropIntent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.parse("file://" + mPhotoFile.getAbsolutePath()));
            cropIntent.putExtra("return-data", false);
            startActivityForResult(cropIntent,REQUEST_CODE_CROP);
            // 扫描更新相册
            Util.showInAlbum(mContext, mPhotoFile.getAbsolutePath());
        }else if (requestCode == REQUEST_CODE_CROP && resultCode == RESULT_OK) {
            // 显示照片
            ((ImageView) findViewById(R.id.image_view)).setImageURI(Uri.fromFile(mPhotoFile));
        }
    }
}