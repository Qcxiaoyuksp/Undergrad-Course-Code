package com.example.accounting.db;




import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import com.example.accounting.utils.FloatUtils;

import java.util.ArrayList;
import java.util.List;

/*
* 负责管理数据库的类
*   主要对于表当中的内容进行操作，增删改查
* */
public class DBManager {

    private static SQLiteDatabase db;

    /*2.2 初始化数据库对象*/
    public static void initDB(Context context) {
        DBOpenHelper helper = new DBOpenHelper(context);  //得到帮助类对象
        db = helper.getWritableDatabase();      //得到数据库对象
    }

    /**
     * 2.2
     * 读取数据库当中的数据，写入内存集合里
     * kind :表示收入或者支出
     */
    public static List<TypeBean> getTypeList(int kind) {
        List<TypeBean> list = new ArrayList<>();
        //读取typetb表当中的数据
        String sql = "select * from typetb where kind = " + kind;
        Cursor cursor = db.rawQuery(sql, null);
//        循环读取游标内容，存储到对象当中
        while (cursor.moveToNext()) {
            String typename = cursor.getString(cursor.getColumnIndexOrThrow("typename"));
            int imageId = cursor.getInt(cursor.getColumnIndexOrThrow("imageId"));
            int sImageId = cursor.getInt(cursor.getColumnIndexOrThrow("sImageId"));
            int kind1 = cursor.getInt(cursor.getColumnIndexOrThrow("kind"));
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            TypeBean typeBean = new TypeBean(id, typename, imageId, sImageId, kind);
            list.add(typeBean);
        }
        return list;
    }


    /*
     * 2.2
     * 向记账表当中插入一条元素
     * */
    public static void insertItemToAccounttb(AccountBean bean) {
        ContentValues values = new ContentValues();
        values.put("typename", bean.getTypename());
        values.put("sImageId", bean.getsImageId());
        values.put("beizhu", bean.getBeizhu());
        values.put("money", bean.getMoney());
        values.put("time", bean.getTime());
        values.put("year", bean.getYear());
        values.put("month", bean.getMonth());
        values.put("day", bean.getDay());
        values.put("kind", bean.getKind());
        db.insert("accounttb", null, values);
    }

    /*
     * 获取记账表当中某一天的所有支出或者收入情况
     * */
//    1.1数据库编写
    public static List<AccountBean>getAccountListOneDayFromAccounttb(int year,int month,int day){
        List<AccountBean>list = new ArrayList<>();
        String sql = "select * from accounttb where year=? and month=? and day=? order by id desc";
        Cursor cursor = db.rawQuery(sql, new String[]{year + "", month + "", day + ""});
        //遍历符合要求的每一行数据
        while (cursor.moveToNext()) {
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            String typename = cursor.getString(cursor.getColumnIndexOrThrow("typename"));
            String beizhu = cursor.getString(cursor.getColumnIndexOrThrow("beizhu"));
            String time = cursor.getString(cursor.getColumnIndexOrThrow("time"));
            int sImageId = cursor.getInt(cursor.getColumnIndexOrThrow("sImageId"));
            int kind = cursor.getInt(cursor.getColumnIndexOrThrow("kind"));
            float money = cursor.getFloat(cursor.getColumnIndexOrThrow("money"));
            AccountBean accountBean = new AccountBean(id, typename, sImageId, beizhu, money, time, year, month, day, kind);
            list.add(accountBean);
        }
      return list;
    }

    /**
     * 4 查询记账的表当中有几个年份信息
     * */
    public static List<Integer>getYearListFromAccounttb(){
        List<Integer>list = new ArrayList<>();
        String sql = "select distinct(year) from accounttb order by year asc";
        Cursor cursor = db.rawQuery(sql, null);
        while (cursor.moveToNext()) {
            int year = cursor.getInt(cursor.getColumnIndexOrThrow("year"));
            list.add(year);
        }
        return list;
    }
//1.1数据库编写
        /*
         * 获取记账表当中某一月的所有支出或者收入情况
         * */
        public static List<AccountBean>getAccountListOneMonthFromAccounttb(int year,int month){
            List<AccountBean>list = new ArrayList<>();
            String sql = "select * from accounttb where year=? and month=? order by id desc";
            Cursor cursor = db.rawQuery(sql, new String[]{year + "", month + ""});
            //遍历符合要求的每一行数据
            while (cursor.moveToNext()) {
                int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
                String typename = cursor.getString(cursor.getColumnIndexOrThrow("typename"));
                String beizhu = cursor.getString(cursor.getColumnIndexOrThrow("beizhu"));
                String time = cursor.getString(cursor.getColumnIndexOrThrow("time"));
                int sImageId = cursor.getInt(cursor.getColumnIndexOrThrow("sImageId"));
                int kind = cursor.getInt(cursor.getColumnIndexOrThrow("kind"));
                float money = cursor.getFloat(cursor.getColumnIndexOrThrow("money"));
                int day = cursor.getInt(cursor.getColumnIndexOrThrow("day"));
                AccountBean accountBean = new AccountBean(id, typename, sImageId, beizhu, money, time, year, month, day, kind);
                list.add(accountBean);
            }
            return list;
        }
    /**
     * 1.2 获取某一天的支出或者收入的总金额   kind-> 支出：0   收入：1
     */
    public static float getSumMoneyOneDay(int year, int month, int day, int kind){
        float total = 0.0f;
        String sql = "select sum(money) from accounttb where year=? and month=? and day=? and kind=?";
        Cursor cursor = db.rawQuery(sql, new String[]{year + "", month + "", day + "", kind + ""});
        //遍历
        if (cursor.moveToFirst()) {
            float money = cursor.getFloat(cursor.getColumnIndexOrThrow("sum(money)"));
            total = money;
        }
        return total;
    }
    /**
     * 6.1 统计某一月的支出或者收入的总金额   收入-1 支出-0
     */
    public static int getCountItemOneMonth(int year,int month,int kind){
        int total=0;
        String sql="select count(money) from accounttb where year=? and month=? and kind=?";
        Cursor cursor=db.rawQuery(sql,new String[]{year+"",month+"",kind+""});
        if(cursor.moveToFirst()){
           int count=cursor.getInt(cursor.getColumnIndexOrThrow("count(money)"));
            total=count;
        }
        return total;
    }

    /**
     * 1.2 获取某一月的支出或者收入的总金额   kind-> 支出：0   收入：1
     */
    public static float getSumMoneyOneMonth(int year, int month, int kind){
        float total = 0.0f;
        String sql = "select sum(money) from accounttb where year=? and month=? and kind=?";
        Cursor cursor = db.rawQuery(sql, new String[]{year + "", month + "", kind + ""});
        //遍历
        if (cursor.moveToFirst()) {
            float money = cursor.getFloat(cursor.getColumnIndexOrThrow("sum(money)"));
            total = money;
        }
        return total;
    }

    /**
     * 1.2 获取某一年的支出或者收入的总金额   kind-> 支出：0   收入：1
     */
    public static float getSumMoneyOneYear(int year, int kind){
        float total = 0.0f;
        String sql = "select sum(money) from accounttb where year=? and kind=?";
        Cursor cursor = db.rawQuery(sql, new String[]{year + "", kind + ""});
        //遍历
        if (cursor.moveToFirst()) {
            float money = cursor.getFloat(cursor.getColumnIndexOrThrow("sum(money)"));
            total = money;
        }
        return total;
    }

    /**
     * 1.2 根据传入的id，删除accounttb表当中的一条数据
     */
    public static int deleteItemFromAccounttbById(int id){
        int i = db.delete("accounttb", "id=?", new String[]{id + ""});
        return i;
    }

    /**
     * 3 根据备注搜索  --搜索界面
     *
     *
     */
    public static List<AccountBean>getAccountListByReamrkFromAccountb(String beizhu){
        List<AccountBean> list=new ArrayList<>();
        String sql="select * from accounttb where beizhu like '%"+beizhu+"%'";
        Cursor cursor=db.rawQuery(sql,null);
        while (cursor.moveToNext()){
            int id= cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            String typename=cursor.getString(cursor.getColumnIndexOrThrow("typename"));
            String bz=cursor.getString(cursor.getColumnIndexOrThrow("beizhu"));
            String time= cursor.getString(cursor.getColumnIndexOrThrow("time"));
            int simageId= cursor.getInt(cursor.getColumnIndexOrThrow("sImageId"));
            int kind=cursor.getInt(cursor.getColumnIndexOrThrow("kind"));
            float money=cursor.getFloat(cursor.getColumnIndexOrThrow("money"));
            int year=cursor.getInt(cursor.getColumnIndexOrThrow("year"));
            int month=cursor.getInt(cursor.getColumnIndexOrThrow("month"));
            int day=cursor.getInt(cursor.getColumnIndexOrThrow("day"));

            AccountBean accountBean=new AccountBean(id,typename,simageId,bz,money,time,year,month,day,kind);
            list.add(accountBean);
        }
        return list;
    }

    /*   5  */
    /*删除accounttb表格当中所有数据*/

    public static void  deleteAllAccount(){
        String sql = "delete from accounttb";
        db.execSQL(sql);
    }

    /**
     * 查询指定年份和月份的收入或者支出每一种类型的总钱数
     * */
    /*   5  */
    public static List<ChartItemBean>getChartListFromAccounttb(int year,int month,int kind){
        List<ChartItemBean>list = new ArrayList<>();
        float sumMoneyOneMonth = getSumMoneyOneMonth(year, month, kind);  //求出支出或者收入总钱数
        String sql = "select typename,sImageId,sum(money)as total from accounttb where year=? and month=? and kind=? group by typename " +
                "order by total desc";
        Cursor cursor = db.rawQuery(sql, new String[]{year + "", month + "", kind + ""});
        while (cursor.moveToNext()) {
            int sImageId = cursor.getInt(cursor.getColumnIndexOrThrow("sImageId"));
            String typename = cursor.getString(cursor.getColumnIndexOrThrow("typename"));
            float total = cursor.getFloat(cursor.getColumnIndexOrThrow("total"));
            //计算所占百分比  total /sumMonth
            float ratio = FloatUtils.div(total,sumMoneyOneMonth);
            ChartItemBean bean = new ChartItemBean(sImageId, typename, ratio, total);
            list.add(bean);
        }
        return list;
    }
    /**
     * 6.2 zkq
     * 获取这个月当中某一天收入支出最大的金额，金额是多少
     * */
    public static float getMaxMoneyOneDayInMonth(int year,int month,int kind){
        String sql = "select sum(money) from accounttb where year=? and month=? and kind=? group by day order by sum(money) desc";
        Cursor cursor = db.rawQuery(sql,new String[]{year+"",month+"",kind+""});
        if (cursor.moveToFirst()) {
            float money = cursor.getFloat(cursor.getColumnIndexOrThrow("sum(money)"));
            return money;
        }
        return 0;
    }

    /*根据指定月份每一日收入或者支出总钱数的集合*/
    /* 6.2 zkq */
    public static List<BarChartItemBean> getSumMoneyOneDayInMonth (int year,int month,int kind){
        String sql = "select day,sum(money) from accounttb where year=? and month=? and kind=? group by day";
        Cursor cursor = db.rawQuery(sql,new String[]{year+"",month+"",kind+""});
        List<BarChartItemBean>list = new ArrayList<>();
        while (cursor.moveToNext()){
            int day = cursor.getInt(cursor.getColumnIndexOrThrow("day"));
            float smoney = cursor.getFloat(cursor.getColumnIndexOrThrow("sum(money)"));
            BarChartItemBean itemBean = new BarChartItemBean(year,month,day,smoney);
            list.add(itemBean);
        }
        return list;
    }

}