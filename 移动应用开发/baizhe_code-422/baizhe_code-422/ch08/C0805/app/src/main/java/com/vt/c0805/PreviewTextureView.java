package com.vt.c0805;

import android.content.Context;
import android.util.AttributeSet;
import android.view.TextureView;

public class PreviewTextureView extends TextureView {
    private int mWidth = 0;
    private int mHeight = 0;
    // 构造方法
    public PreviewTextureView(Context context) {
        this(context, null);
    }
    public PreviewTextureView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }
    public PreviewTextureView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }
    // 设置尺寸
    public void setAspectRatio(int width, int height) {
        if (width < 0 || height < 0) {
            throw new IllegalArgumentException("无效尺寸");
        }
        mWidth = width;
        mHeight = height;
        // 调用onMeasure、onLayout、onDraw方法
        requestLayout();
    }
    // 重写onMeasure
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        // 提取测量的尺寸
        int width = MeasureSpec.getSize(widthMeasureSpec);
        int height = MeasureSpec.getSize(heightMeasureSpec);
        // 设置控件显示的尺寸
        if (0 == mWidth || 0 == mHeight) {
            setMeasuredDimension(width, height);
        } else {
            // 重新计算显示的尺寸
            if (width < height * mWidth / mHeight) {
                setMeasuredDimension(width, width * mHeight / mWidth);
            } else {
                setMeasuredDimension(height * mWidth / mHeight, height);
            }
        }
    }
}
