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
    public partial class room_info_update : Form
    {
        string ID = "";
        public room_info_update()
        {
            InitializeComponent();
        }

        public room_info_update(string room_id,string hotel_id,string room_number,string room_type,string price,string status)
        {
            InitializeComponent();
            ID = textBox1.Text = room_id;
            textBox2.Text = hotel_id;
            textBox3.Text = room_number;
            textBox4.Text = room_type;
            textBox5.Text = price;
            textBox6.Text = status;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string sql = $"update room_info set room_id='{textBox1.Text}',[hotel_id]='{textBox2.Text}',room_number='{textBox3.Text}',room_type='{textBox4.Text}',[price]='{textBox5.Text}',status='{textBox6.Text}'where room_id='{ID}'";
            Dao dao = new Dao();
            if (dao.Execute(sql) > 0)
            {
                MessageBox.Show("修改成功");
                this.Close();
            }
        }
    }
}
