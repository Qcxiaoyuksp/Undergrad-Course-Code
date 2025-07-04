package com.vt.c0402;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.os.Bundle;
import android.widget.ListView;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private Context mContext;
    private List<PhotoModel> mPhotoModel;
    private PhotoListAdapter mAdapter;
    private ListView photoListView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext = MainActivity.this;
        mPhotoModel = new ArrayList<>();
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic01, 203));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic02, 44));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic03, 311));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic04, 97));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic05, 462));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic06, 117));
        mPhotoModel.add(new PhotoModel(R.mipmap.img_pic07, 187));
        mPhotoModel.add(new PhotoModel(R.mipmap.pic08, 87));
        mAdapter = new PhotoListAdapter(mContext,mPhotoModel);
        photoListView = findViewById(R.id.list_view_photo);
        photoListView.setAdapter(mAdapter);
    }
}
