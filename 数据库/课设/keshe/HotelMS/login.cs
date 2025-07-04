using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HotelMS
{
    public partial class login : Form
    {
        public login()
        {
            InitializeComponent();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "")
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
            //管理员
            Dao dao = new Dao();
            string sql = $"select * from admin where id = '{textBox1.Text}' and psw = '{textBox2.Text}'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
                if (dc.Read()) //读取一行数据
                {
                    Data.UID = dc["id"].ToString();
                    //Data.UName = dc["name"].ToString();

                    MessageBox.Show("登录成功");
                    hotel hotel = new hotel();//用户窗体实例化
                    this.Hide();//跳转到下一个窗口时把登录窗口隐藏
                    hotel.ShowDialog();
                    this.Show();//关掉后再显示出来
                }
                else
                {
                    MessageBox.Show("登录失败");
                }
                dao.DaoClose();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
