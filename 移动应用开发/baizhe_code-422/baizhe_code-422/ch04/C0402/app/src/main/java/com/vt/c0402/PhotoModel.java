package com.vt.c0402;

public class PhotoModel {
    public int photoResId;//图片资源id
    public int hits;//图片点击次数
    public PhotoModel(int photoResId, int hits) {
        this.photoResId = photoResId;
        this.hits = hits;
    }
}
