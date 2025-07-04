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
    public partial class admin2 : Form
    {
        public admin2()
        {
            InitializeComponent();
            
        }

        private void admin2_Load(object sender, EventArgs e)
        {
            Table();
            
            label2.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + dataGridView1.SelectedRows[0].Cells[1].Value.ToString();//获取书号和书名
            
        }

        //从数据库读取数据显示在表格控件中
        public void Table()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = "select * from t_book";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while(dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //根据书号显示数据
        public void TableID()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from t_book where id = '{textBox1.Text}'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //根据书名显示数据 模糊查询
        public void TableName()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = $"select * from t_book where name like '%{textBox2.Text}%'";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        //添加按钮
        private void button1_Click(object sender, EventArgs e)
        {
            admin2_1 admin = new admin2_1();//实例化（显示）添加图书的界面
            admin.ShowDialog();
        }

        //删除按钮
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();//获取书号
                label2.Text = id + dataGridView1.SelectedRows[0].Cells[2].Value.ToString();//显示当前选中图书的书号和书名
                DialogResult dr = MessageBox.Show("确认删除吗？", "信息提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                if (dr == DialogResult.OK)
                {
                    string sql = $"delete from t_book where id='{id}'";
                    Dao dao = new Dao();
                    if (dao.Execute(sql) > 0)
                    {
                        MessageBox.Show("删除成功");
                        Table();
                    }
                    else
                    {
                        MessageBox.Show("删除失败"+sql);
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
                label2.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + dataGridView1.SelectedRows[0].Cells[1].Value.ToString();//获取书号和书名
            }
            catch
            {
                label2.Text = "";
            }
            //label2.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString() + dataGridView1.SelectedRows[0].Cells[1].Value.ToString();//获取书号和书名
        }

        //修改图书
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                string id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                string name = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                string author = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
                string press = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
                string number = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();

                admin2_2 admin = new admin2_2(id,name,author,press,number);
                admin.ShowDialog();

                //Table();//刷新数据
            }
            catch
            {
                MessageBox.Show("ERROR");
            }
            
        }

        private void button5_Click(object sender, EventArgs e)
        {
            TableID();//id查询 
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Table();//刷新数据
            textBox1.Text = "";
            textBox2.Text = "";
        }

        private void button6_Click(object sender, EventArgs e)
        {
            TableName();//书名查询
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
