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
    public partial class frmEdit : Form
    {
        public frmEdit()
        {
            InitializeComponent();
        }

        private void frmEdit_Load(object sender, EventArgs e)
        {
            string sql = "select t.rowid,t.* from t_student_info t";
            OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            conn.Open();
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            dg_result.DataSource = dt;
            conn.Close();
        }
        
        private void dg_result_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int row = dg_result.CurrentCell.RowIndex;
            tb_rowid.Text =  dg_result.Rows[row].Cells[0].Value.ToString();
            tb_stuid.Text = dg_result.Rows[row].Cells[1].Value.ToString();
            tb_name.Text = dg_result.Rows[row].Cells[2].Value.ToString();
            cb_sex.Text = dg_result.Rows[row].Cells[3].Value.ToString();
            tb_age.Text = dg_result.Rows[row].Cells[4].Value.ToString();
        }

        private void btn_update_Click(object sender, EventArgs e)
        {
            string sql = "update t_student_info set stu_id='" + tb_stuid.Text + "',stu_name='" + tb_name.Text + "',stu_sex='" + cb_sex.Text + "',stu_age=" + tb_age.Text + " where rowid='" + tb_rowid.Text + "'";
            OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            conn.Open();
            OracleCommand cmd = new OracleCommand(sql, conn);
            cmd.ExecuteNonQuery();
            
            
            sql = "select t.rowid,t.* from t_student_info t";            
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            dg_result.DataSource = dt;
            conn.Close();
        }

        private void btn_delete_Click(object sender, EventArgs e)
        {
            string sql = "delete from t_student_info where rowid='" + tb_rowid.Text + "'";
            OracleConnection conn = new OracleConnection("Data Source=sjzu;User ID=test;Password=test");
            conn.Open();
            OracleCommand cmd = new OracleCommand(sql, conn);
            cmd.ExecuteNonQuery();

            sql = "select t.rowid,t.* from t_student_info t";
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);

            DataTable dt = new DataTable();
            da.Fill(dt);

            dg_result.DataSource = dt;
            conn.Close();

            tb_rowid.Text = "";
            tb_stuid.Text = "";
            tb_name.Text = "";
            cb_sex.Text = "";
            tb_age.Text = "";
        }
    }
}
