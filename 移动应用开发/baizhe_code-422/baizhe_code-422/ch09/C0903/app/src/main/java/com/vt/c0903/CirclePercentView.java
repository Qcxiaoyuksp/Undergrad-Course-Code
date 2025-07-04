package com.vt.c0903;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;
import java.text.DecimalFormat;

public class CirclePercentView extends View {
    public double mLoadedPercent = 0;//当前进度值
    private Paint mBackPaint;//背景画笔
    private Paint mFrontPaint;//前景画笔
    private Paint mTextPaint;//文字画笔
    private float mStrokeWidth = 50;//笔触宽度
    private float mHalfStrokeWidth = mStrokeWidth / 2;//半个笔触宽度
    private float mRadius = 200;//半径
    private RectF mRect;//矩形
    private int mMax = 100;//最大进度值
    private int mWidth;//视图宽度
    private int mHeight;//视图高度

    public CirclePercentView(Context context) {
        this(context, null);
    }

    public CirclePercentView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public CirclePercentView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }
    // 初始化
    private void init() {
        mBackPaint = new Paint();
        mBackPaint.setColor(Color.WHITE);
        mBackPaint.setAntiAlias(true);
        mBackPaint.setStyle(Paint.Style.STROKE);
        mBackPaint.setStrokeWidth(mStrokeWidth);

        mFrontPaint = new Paint();
        mFrontPaint.setColor(Color.RED);
        mFrontPaint.setAntiAlias(true);
        mFrontPaint.setStyle(Paint.Style.STROKE);
        mFrontPaint.setStrokeWidth(mStrokeWidth);

        mTextPaint = new Paint();
        mTextPaint.setColor(Color.BLACK);
        mTextPaint.setAntiAlias(true);
        mTextPaint.setTextSize(80);
        mTextPaint.setTextAlign(Paint.Align.CENTER);
    }
    // 重写测量大小的onMeasure方法
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        mWidth = getRealSize(widthMeasureSpec);
        mHeight = getRealSize(heightMeasureSpec);
        setMeasuredDimension(mWidth, mHeight);
    }
    // 计算进度视图尺寸
    public int getRealSize(int measureSpec) {
        int result = 1;
        int mode = MeasureSpec.getMode(measureSpec);
        int size = MeasureSpec.getSize(measureSpec);

        if (mode == MeasureSpec.AT_MOST || mode == MeasureSpec.UNSPECIFIED) {
            result = (int) (mRadius * 2 + mStrokeWidth);
        } else {
            result = size;
        }
        return result;
    }
    // 重写绘制View的onDraw方法
    @Override
    protected void onDraw(Canvas canvas) {
        initRect();
        // 百分比字符串保留两位小数
        DecimalFormat df = new DecimalFormat("#0.0");
        String percentString = df.format(mLoadedPercent) + "%";
        // 计算进度的角度
        float angle = (float) mLoadedPercent / (float) mMax * 360;
        canvas.drawCircle(mWidth / 2, mHeight / 2, mRadius, mBackPaint);
        canvas.drawArc(mRect, -90, angle, false, mFrontPaint);
        canvas.drawText(percentString, mWidth / 2 + mHalfStrokeWidth, mHeight / 2 + mHalfStrokeWidth, mTextPaint);
        invalidate();
    }
    // 初始化绘制弧线的区域
    private void initRect() {
        if (mRect == null) {
            mRect = new RectF();
            int viewSize = (int) (mRadius * 2);
            int left = (mWidth - viewSize) / 2;
            int top = (mHeight - viewSize) / 2;
            int right = left + viewSize;
            int bottom = top + viewSize;
            mRect.set(left, top, right, bottom);
        }
    }
}