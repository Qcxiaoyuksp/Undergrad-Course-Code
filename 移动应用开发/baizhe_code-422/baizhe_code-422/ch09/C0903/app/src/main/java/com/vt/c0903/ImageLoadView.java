package com.vt.c0903;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.FrameLayout;
import android.widget.ImageView;

import androidx.annotation.NonNull;

public class ImageLoadView extends FrameLayout {
    private Context mContext;
    private ImageView mImageView;
    private CirclePercentView mCirclePercentView;

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
        mCirclePercentView = findViewById(R.id.circle_percent_view);
    }
    public void setImageURL(String url){
        ImageLoader imageLoader = new ImageLoader();
        imageLoader.displayImage(mImageView, url,mContext.getExternalCacheDir().getAbsolutePath() + "/image",mCirclePercentView);
    }

    public void setImageResource(int id){
        mImageView.setImageResource(id);
    }
}
