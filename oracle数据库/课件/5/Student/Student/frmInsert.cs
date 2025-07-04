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
    public partial class frmInsert : Form
    {
        public frmInsert()
        {
            InitializeComponent();
        }

        private void frmInsert_Load(object sender, EventArgs e)
        {
            string sql = "select * from t_student_info";
            OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            conn.Open();
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            dg_result.DataSource = dt;
            conn.Close();
        }

        private void btn_insert_Click(object sender, EventArgs e)
        {
            string sql = "insert into t_student_info values('" + tb_stuid.Text+ "','" + tb_name.Text + "','" + cb_sex.Text + "'," + tb_age.Text + ")";
            OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            conn.Open();
            OracleCommand cmd = new OracleCommand(sql, conn);
            cmd.ExecuteNonQuery();

            sql = "select * from t_student_info";            
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);
            DataTable dt = new DataTable();
            da.Fill(dt);
            dg_result.DataSource = dt;

            conn.Close();
        }
    }
}
