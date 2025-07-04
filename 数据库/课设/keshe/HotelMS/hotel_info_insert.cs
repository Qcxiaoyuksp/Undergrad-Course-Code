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
    public partial class hotel_info_insert : Form
    {
        public hotel_info_insert()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "" && textBox4.Text != "" )
            {
                Dao dao = new Dao();
                string sql = $"insert into hotel_info values('{textBox1.Text}','{textBox2.Text}','{textBox3.Text}','{textBox4.Text}')";
                int n = dao.Execute(sql);
                if (n > 0)
                {
                    MessageBox.Show("添加成功");
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox3.Text = "";
                    textBox4.Text = "";
                }
                else
                {
                    MessageBox.Show("添加失败");
                }
                
            }
            else
            {
                MessageBox.Show("输入不允许有空");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
        }
    }
}
