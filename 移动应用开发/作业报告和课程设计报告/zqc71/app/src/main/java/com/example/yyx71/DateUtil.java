package com.example.yyx71;

import android.icu.text.SimpleDateFormat;

import java.util.Date;

public class DateUtil {
    //这里列举了3个比较常用的时间展现格式，这个自由度很高，可以根据自己的需求来设计
    public static String getNowDateTime() {
        //年-月-日 时:分:秒
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return sdf.format(new Date());
    }

    public static String getNowTime() {
        //时：分：秒
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        return sdf.format(new Date());
    }

    public static String getNowTimeDetail() {
        //时：分：秒.毫秒
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss.SSS");
        return sdf.format(new Date());
    }

}

