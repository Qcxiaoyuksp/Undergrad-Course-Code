//对数据库进行链接和操纵

using System.Data.SqlClient;

namespace BookMS
{
    class Dao
    {
        SqlConnection sc;
        public SqlConnection connect()
        {
            string str = @"Data Source =zhangqingchen;Initial Catalog =BookDB; Integrated Security =SSPI";//数据库连接字符串
            // 服务器名称 数据库名称
            sc = new SqlConnection(str);//创建数据库连接对象
            sc.Open();//打开数据库
            return sc;//返回数据库连接对象
        }

        //根据SQL语句操作数据库
        public SqlCommand command(string sql)
        {
            SqlCommand cmd = new SqlCommand(sql, connect());
            return cmd;
        }

        //更新操作
        public int Execute(string sql)
        {
            return command(sql).ExecuteNonQuery();
        }

        //读取操作
        public SqlDataReader read(string sql)
        {
            return command(sql).ExecuteReader();
        }

        //关闭数据库连接
        public void DaoClose()
        {
            sc.Close();
        }
    }
}
