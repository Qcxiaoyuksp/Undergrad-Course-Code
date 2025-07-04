using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.OracleClient;

namespace Student
{
    public partial class frmQuery : Form
    {
        public frmQuery()
        {
            InitializeComponent();
        }

        private void frmQuery_Load(object sender, EventArgs e)
        {
            string sql = "select * from t_student_info";
            //OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            //conn.Open();
            //OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            //DataTable dt = new DataTable();
            //da.Fill(dt);

            dg_result.DataSource = OracleDB.QueryData(sql);// dt;
            //conn.Close();
        }

        private void btn_query1_Click(object sender, EventArgs e)
        {
            string sql = "select * from t_student_info where stu_id='" + tb_stuid.Text + "'";
            //OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            //conn.Open();
            //OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            //DataTable dt = new DataTable();
            //da.Fill(dt);

            dg_result.DataSource = OracleDB.QueryData(sql); //dt;
            //conn.Close();
        }


    }
}
