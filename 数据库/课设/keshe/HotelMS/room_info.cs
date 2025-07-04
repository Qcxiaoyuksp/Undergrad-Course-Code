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
    public partial class room_info : Form
    {
        public room_info()
        {
            InitializeComponent();
        }

        private void room_info_Load(object sender, EventArgs e)
        {
            Table();
            label2.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString() + dataGridView1.SelectedRows[0].Cells[3].Value.ToString();//显示当前选中客房号码和房型
        }

        //从数据库读取数据显示在表格控件中
        public void Table()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = "select * from room_info";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString(), dc[5].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //客房ID查询
        public void TableID()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from room_info where room_id='{textBox1.Text}'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString(), dc[5].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //房号查询
        public void TableNumber()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from room_info where room_number='{textBox2.Text}'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString(), dc[5].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //房型查询
        public void TableType()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from room_info where room_type like '%{textBox3.Text}%'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString(), dc[5].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //宾馆ID查询
        public void TableID1()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from room_info where hotel_id='{textBox4.Text}'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString(), dc[5].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            room_info_insert room_info_insert = new room_info_insert();//用户窗体实例化
            //this.Hide();//跳转到下一个窗口时把登录窗口隐藏
            room_info_insert.ShowDialog();
            //this.Show();//关掉后再显示出来
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();//获取客房ID
                label2.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString() + dataGridView1.SelectedRows[0].Cells[3].Value.ToString();//显示当前选中客房号码和房型
                DialogResult dr = MessageBox.Show("确认删除吗？", "信息提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                if (dr == DialogResult.OK)
                {
                    //string sql = $"delete from customer_info where customer_id={id}";
                    string sql = $"DELETE FROM booking_info WHERE room_id = {id};DELETE FROM room_info WHERE room_id = {id}";
                    Dao dao = new Dao();
                    if (dao.Execute(sql) > 0)
                    {
                        MessageBox.Show("删除成功");
                        Table();
                    }
                    else
                    {
                        MessageBox.Show("删除失败" + sql);
                    }
                    dao.DaoClose();
                }
            }
            catch
            {
                MessageBox.Show("请先在表格中选中要删除的图书记录！", "信息提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void dataGridView1_Click(object sender, EventArgs e)
        {
            try
            {
                label2.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString() + dataGridView1.SelectedRows[0].Cells[3].Value.ToString();//显示当前选中客房号码和房型
            }
            catch
            {
                label2.Text = "";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                string room_id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                string hotel_id = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                string room_number = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
                string room_type = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
                string price = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
                string status = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();

                room_info_update room_info_update = new room_info_update(room_id, hotel_id, room_number, room_type, price, status);
                room_info_update.ShowDialog();

                //Table();//刷新数据
            }
            catch
            {
                MessageBox.Show("ERROR");
            }
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Table();
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            TableID();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            TableNumber();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            TableType();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            TableID1();
        }
    }
}
