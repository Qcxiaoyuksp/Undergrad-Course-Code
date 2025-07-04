package com.vt.c0907;

import java.util.ArrayList;
import java.util.List;

public class DailyModel {
    public List<String> ides;//id
    public List<String> names;//昵称
    public List<String> contents;//动态内容
    public List<String> images;//图片
    public List<String> createTimes;//发布时间

    public DailyModel(){
        ides = new ArrayList<>();
        names = new ArrayList<>();
        contents = new ArrayList<>();
        images = new ArrayList<>();
        createTimes = new ArrayList<>();
    }
}