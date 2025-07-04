using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.OracleClient;
using System.Data;

namespace Student
{
    public class OracleDB
    {
        static private string connString = "Data Source=cyxserver;User ID=C##TEST;Password=test";

        static private OracleConnection oracleConn = new OracleConnection(connString);

        static private void Open()
        {
            if (oracleConn == null)
                oracleConn = new OracleConnection(connString);
            if (oracleConn.State == ConnectionState.Closed)
                oracleConn.Open();
        }

        static public void ExecuteNonQuery(string sql)
        {
            Open();
            OracleCommand cmd = new OracleCommand(sql, oracleConn);
            cmd.ExecuteNonQuery();
        }

        static public DataTable QueryData(string sql)
        {
            Open();
            OracleDataAdapter da = new OracleDataAdapter(sql, oracleConn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            return dt;
        }

    }
}
