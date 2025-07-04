package com.vt.c0902;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ProgressBar;

import androidx.annotation.NonNull;

public class ImageLoadView extends FrameLayout {
    private Context mContext;
    private ImageView mImageView;
    private ProgressBar mProgressBar;

    public ImageLoadView(@NonNull Context context) {
        this(context, null);
    }
    public ImageLoadView(Context context, @NonNull AttributeSet attrs) {
        this(context, attrs, 0);
    }
    public ImageLoadView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mContext = context;
        init(context,attrs);
    }
    private void init(Context context, AttributeSet attrs){
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.view_image_load, this);
        mImageView =  findViewById(R.id.image_view);
        mProgressBar = findViewById(R.id.progress_bar);
    }
    public void setImageURL(String url){
        ImageLoader imageLoader = new ImageLoader();
        imageLoader.displayImage(mImageView, url,mContext.getExternalCacheDir().getAbsolutePath() + "/image",mProgressBar);
    }

    public void setImageResource(int id){
        mImageView.setImageResource(id);
    }
}
