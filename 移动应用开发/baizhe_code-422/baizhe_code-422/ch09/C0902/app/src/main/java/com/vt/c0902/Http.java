package com.vt.c0902;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class Http {
    private static final String EXCEPTION_FAILURE = "请求URL失败";
    public static File downloadFile(String path, String cachePath) throws Exception {
        // 本地缓存文件
        File storageDir = new File(cachePath);//判断缓存文件夹是否存在
        if (!storageDir.exists()) {
            storageDir.mkdirs();
        }
        String[] temp = path.split("\\/");//拆分路径字符串
        String fileName = temp[temp.length - 1];//获取文件名
        File cacheFile = new File(storageDir, fileName);//缓存文件
        // 下载请求
        URL url = new URL(path);//将字符串格式的路径转为URL
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();//创建连接
        conn.setConnectTimeout(5000);//设置连接超时时间
        conn.setReadTimeout(5000);//设置下载超时时间
        conn.setRequestMethod("GET");//设置请求类型为Get类型
        if (conn.getResponseCode() != 200) {//判断请求Url是否成功
            throw new RuntimeException(EXCEPTION_FAILURE);
        }
        // 如果有本地缓存文件则不进行下载直接使用
        long contentLength = conn.getContentLengthLong();//文件数据大小
        if (cacheFile.exists()) {//判断是否缓存
            // 如果缓存文件与下载文件大小相等则直接返回缓存文件
            if(cacheFile.length() == contentLength)
                return cacheFile;
        }
        // 下载文件
        InputStream is = conn.getInputStream();//获取输入流
        FileOutputStream fileOutputStream = null;//文件输出流
        if (is != null) {
            fileOutputStream = new FileOutputStream(cacheFile);//指定文件保存路径，代码看下一步
            byte[] buf = new byte[1024];
            int ch;
            while ((ch = is.read(buf)) != -1) {
//                Thread.sleep(10);//下载过快时使用进程休眠便于观察下载进度
                fileOutputStream.write(buf, 0, ch);//将获取到的流写入文件中
            }
        }
        // 释放资源
        if (fileOutputStream != null) {
            fileOutputStream.flush();
            fileOutputStream.close();
        }
        conn.disconnect();
        return cacheFile;
    }
}
