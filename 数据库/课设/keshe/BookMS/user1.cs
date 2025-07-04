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
    public partial class user1 : Form
    {
        public user1()
        {
            InitializeComponent();
            label1.Text = $"欢迎{Data.UName}登陆";
        }

        private void 图书查看和借阅ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            user2 user = new user2();//实例化（显示）查看图书和借阅的界面
            user.ShowDialog();
        }

        private void 我的信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            user3 user = new user3();
            user.ShowDialog();
        }

        private void 帮助ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("HELP");
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
