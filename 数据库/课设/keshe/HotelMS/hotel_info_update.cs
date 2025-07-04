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
    public partial class hotel_info_update : Form
    {
        string ID = "";
        public hotel_info_update()
        {
            InitializeComponent();
        }

        public hotel_info_update(string hotel_id,string hotel_name,string address,string contact)
        {
            InitializeComponent();
            ID = textBox1.Text = hotel_id;
            textBox2.Text = hotel_name;
            textBox3.Text = address;
            textBox4.Text = contact;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string sql = $"update hotel_info set hotel_id='{textBox1.Text}',[hotel_name]='{textBox2.Text}',address='{textBox3.Text}',contact='{textBox4.Text}'where hotel_id='{ID}'";
            Dao dao = new Dao();
            if (dao.Execute(sql) > 0)
            {
                MessageBox.Show("修改成功");
                this.Close();
            }
        }
    }
}
