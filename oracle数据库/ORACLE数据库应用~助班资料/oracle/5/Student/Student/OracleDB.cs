using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.OracleClient;
using System.Data;
using System.Configuration;

namespace Student
{
    public class OracleDB
    {
        //static private string connString = "Data Source=sjzu;User ID=test;Password=test";
        static private string connString = ConfigurationManager.AppSettings["connString"];

        

        static private OracleConnection oracleConn = new OracleConnection(connString);        

        static public void ExecuteNonQuery(string sql)
        {
            OracleCommand cmd = new OracleCommand(sql, oracleConn);
            cmd.ExecuteNonQuery();
            
        }

        static public DataTable QueryData(string sql)
        {
            OracleDataAdapter da = new OracleDataAdapter(sql, oracleConn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            return dt;
        }

    }
}
