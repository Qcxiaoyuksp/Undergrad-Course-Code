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
    public partial class frmLogin : Form
    {
        public int login_count = 0;

        public frmLogin()
        {
            InitializeComponent();
        }

        private void btn_login_Click(object sender, EventArgs e)
        {           
            OracleConnection conn = new OracleConnection("Data Source=orcl;User id=C##TEST;Password=test");
            conn.Open();
            string sql = "select * from t_user_info where username='" + tb_username.Text + "' and password='" + tb_password.Text + "'";
            OracleDataAdapter da = new OracleDataAdapter(sql, conn);
            DataTable dt = new DataTable();
            da.Fill(dt);
            if (dt.Rows.Count > 0)
            {
                this.Hide();  
                frmMain main = new frmMain();
                main.Show();                              
            }
            else
            {
                login_count++;
                if (login_count >= 3)
                {
                    MessageBox.Show("密码错误达到3次");
                    Application.Exit();
                }
                else
                {
                    MessageBox.Show("密码错误");
                }
            }
                
        }

        private void btn_cancel_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
