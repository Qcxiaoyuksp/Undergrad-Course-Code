using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BookMS
{
    public partial class login : Form
    {
        public login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text!=" " || textBox2.Text!=" ")
            {
                Login();
            }
            else
            {
                MessageBox.Show("输入有空项，请重新输入！");
            }
        }
        //登陆方法，验证是否允许登陆，若允许返回真
        public void Login()
        {
            //用户
            if (radioButtonUser.Checked == true)
            {
                Dao dao = new Dao();
                //下面三句话是一个意思 读取sql语句
                string sql = "select * from t_user where id = '" + textBox1.Text + "' and psw = '" + textBox2.Text + "'";
                //string sql2 = String.Format("select * from t_user where id='{0}' and psw = '{1}'", textBox1.Text, textBox2.Text);
                //string sql3 = $"select * from t_user where id = '{textBox1.Text}' and psw = '{textBox2.Text}'";
                //MessageBox.Show(sql);
                IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
                if (dc.Read()) //读取一行数据
                {
                    Data.UID = dc["id"].ToString();
                    Data.UName = dc["name"].ToString();

                    MessageBox.Show("登录成功");
                    //return true;
                    user1 user = new user1();//用户窗体实例化
                    this.Hide();//跳转到下一个窗口时把登录窗口隐藏
                    user.ShowDialog();
                    this.Show();//关掉后再显示出来
                }
                else
                {
                    MessageBox.Show("登录失败");
                    //return false;
                }
                dao.DaoClose();
            }
            //管理员
            if(radioButtonAdmin.Checked == true)
            {
                Dao dao = new Dao();
                //下面三句话是一个意思 读取sql语句
                string sql = "select * from t_admin where id = '" + textBox1.Text + "' and psw = '" + textBox2.Text + "'";
                //string sql2 = String.Format("select * from t_user where id='{0}' and psw = '{1}'", textBox1.Text, textBox2.Text);
                //string sql3 = $"select * from t_user where id = '{textBox1.Text}' and psw = '{textBox2.Text}'";
                //MessageBox.Show(sql);
                IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
                if (dc.Read()) //读取一行数据
                {
                    MessageBox.Show("登录成功");
                    //return true;
                    admin1 admin = new admin1();//用户窗体实例化
                    this.Hide();//跳转到下一个窗口时把登录窗口隐藏
                    admin.ShowDialog();
                    this.Show();//关掉后再显示出来
                }
                else
                {
                    MessageBox.Show("登录失败");
                    //return false;
                }
                dao.DaoClose();
            }
            //MessageBox.Show("单选框请先选中");
            //return false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
