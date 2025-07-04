package com.vt.c0907;

import android.util.Log;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;
import java.util.UUID;

public class Http {
    private static final String TAG = "Http";
    public static final String FAILURE = "请求失败";
    private static final int CONNECT_TIME_OUT = 5 * 1000;//连接超时时间
    private static final int READ_TIME_OUT = 10 * 1000;//读取超时时间
    private static final String CHARSET = "UTF-8"; //设置编码
    // 下载文件
    public static File downloadFile(String path, String cachePath) throws Exception {
        // 判断缓存文件夹是否存在
        File storageDir = new File(cachePath);
        if (!storageDir.exists()) {
            storageDir.mkdirs();
        }
        // 获取缓存文件
        String[] temp = path.split("\\/");//拆分路径字符串
        String fileName = temp[temp.length - 1];//获取文件名
        File cacheFile = new File(storageDir, fileName);
        // 将字符串格式的路径转为URL
        URL url = new URL(path);
        // 创建连接
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setConnectTimeout(CONNECT_TIME_OUT);//设置连接超时时间
        conn.setReadTimeout(READ_TIME_OUT);//设置下载超时时间
        conn.setRequestMethod("GET");//设置请求类型为Get类型
        conn.setRequestProperty("Charset", CHARSET);//设置编码
        // 判断请求Url是否成功
        if (conn.getResponseCode() != 200) {
            throw new RuntimeException(FAILURE);
        }
        long contentLength = conn.getContentLengthLong();//文件数据大小
        // 判断是否缓存
        if (cacheFile.exists()) {
            // 如果缓存文件与下载文件大小相等则直接返回缓存文件
            if (cacheFile.length() == contentLength)
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
                fileOutputStream.write(buf, 0, ch);//将获取到的流写入文件中
            }
        }
        if (fileOutputStream != null) {
            fileOutputStream.flush();
            fileOutputStream.close();
        }
        conn.disconnect();
        return cacheFile;
    }
    // post请求
    public static String post(String requestURL, Map<String, File> files, Map<String, String> params) throws Exception {
        URL url = new URL(requestURL);
        String BOUNDARY = UUID.randomUUID().toString();//边界标识（随机生成）
        String PREFIX = "--";//前缀字符串
        String LINE_END = "\r\n";//换行字符串
        String CONTENT_TYPE = "multipart/form-data";//内容类型

        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setConnectTimeout(CONNECT_TIME_OUT);
        conn.setReadTimeout(READ_TIME_OUT);
        conn.setDoInput(true);  //允许输入流
        conn.setDoOutput(true); //允许输出流
        conn.setUseCaches(false);  //不允许使用缓存
        conn.setRequestMethod("POST");  //请求方式
        conn.setRequestProperty("Charset", CHARSET);//设置编码
        conn.setRequestProperty("connection", "keep-alive");
        conn.setRequestProperty("Content-Type", CONTENT_TYPE + ";boundary=" + BOUNDARY);

        OutputStream outputSteam = conn.getOutputStream();
        DataOutputStream dos = new DataOutputStream(outputSteam);
        StringBuffer sb = new StringBuffer();
        // 添加参数
        for (Map.Entry<String, String> entry : params.entrySet()) {
            sb.append(PREFIX);
            sb.append(BOUNDARY);
            sb.append(LINE_END);
            sb.append("Content-Disposition: form-data; name=\"" + entry.getKey() + "\"" + LINE_END);
            sb.append("Content-Type: text/plain; charset=" + CHARSET + LINE_END);
            sb.append("Content-Transfer-Encoding: 8bit" + LINE_END);
            sb.append(LINE_END);
            sb.append(entry.getValue());
            sb.append(LINE_END);
            dos.write(sb.toString().getBytes());
            Log.e(TAG, entry.getKey() + "：" + entry.getValue());
        }
        // 添加文件
        if (files != null) {
            for (Map.Entry<String, File> file : files.entrySet()) {
                sb.append(PREFIX);
                sb.append(BOUNDARY);
                sb.append(LINE_END);
                sb.append("Content-Disposition: form-data; name=\"uploadinput[]\"; filename=\"" + file.getKey() + "\"" + LINE_END);//uploadinput[]是服务器端用于接收图片文件的变量数组，filename是文件名。
                sb.append("Content-Type: multipart/form-data; charset=" + CHARSET + LINE_END);
                sb.append(LINE_END);
                dos.write(sb.toString().getBytes());
                Log.e(TAG, "file:" + file.getKey());
                // 写入图片文件数据
                InputStream is = new FileInputStream(file.getValue());
                byte[] buffer = new byte[1024];
                int len;
                while ((len = is.read(buffer)) != -1) {
                    dos.write(buffer, 0, len);
                }
                is.close();
                dos.write(LINE_END.getBytes());
            }
        }
        // 写入结束标志
        byte[] end_data = (PREFIX + BOUNDARY + PREFIX + LINE_END).getBytes();
        dos.write(end_data);
        // 发送数据流
        dos.flush();
        // 获取服务器端的响应码，200表示发送成功。
        if (conn.getResponseCode() == 200) {
            BufferedReader br = null;
            br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String state = br.readLine();//0成功 1失败
            Log.e(TAG, "response getInputStream:" + state);
            Log.e(TAG, "response Message:" + conn.getResponseMessage());
            return state;
        } else {
            throw new RuntimeException(FAILURE);
        }
    }
    // get请求
    public static String get(String requestUrl,String params) throws Exception{
        URL url = new URL(requestUrl + params);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setConnectTimeout(CONNECT_TIME_OUT);
        conn.setReadTimeout(READ_TIME_OUT);
        conn.setRequestMethod("GET");
        if (conn.getResponseCode() == 200) {
            BufferedReader br = null;
            br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String state = br.readLine();//0成功 1失败
            Log.e(TAG, "response getInputStream:" + state);
            Log.e(TAG, "response Message:" + conn.getResponseMessage());
            return state;
        } else {
            throw new RuntimeException(FAILURE);
        }
    }
}