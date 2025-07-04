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
    public partial class hotel : Form
    {
        public hotel()
        {
            InitializeComponent();
        }

        private void 宾馆信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            hotel_info hotel_info = new hotel_info();//用户窗体实例化
            this.Hide();//跳转到下一个窗口时把登录窗口隐藏
            hotel_info.ShowDialog();
            this.Show();//关掉后再显示出来
        }

        private void 客房信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            room_info room_info = new room_info();//用户窗体实例化
            this.Hide();//跳转到下一个窗口时把登录窗口隐藏
            room_info.ShowDialog();
            this.Show();//关掉后再显示出来
        }

        private void 客户信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            customer_info customer_info = new customer_info();//用户窗体实例化
            this.Hide();//跳转到下一个窗口时把登录窗口隐藏
            customer_info.ShowDialog();
            this.Show();//关掉后再显示出来
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
