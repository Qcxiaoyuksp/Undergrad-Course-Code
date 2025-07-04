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
    public partial class customer_info_update : Form
    {
        string ID = "";
        public customer_info_update()
        {
            InitializeComponent();
        }

        public customer_info_update(string customer_id,string customer_name,string contact)
        {
            InitializeComponent();
            ID = textBox1.Text = customer_id;
            textBox2.Text = customer_name;
            textBox3.Text = contact;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string sql = $"update customer_info set customer_id='{textBox1.Text}',[customer_name]='{textBox2.Text}',contact='{textBox3.Text}'where customer_id='{ID}'";
            Dao dao = new Dao();
            if (dao.Execute(sql) > 0)
            {
                MessageBox.Show("修改成功");
                this.Close();
            }
        }
    }
}
