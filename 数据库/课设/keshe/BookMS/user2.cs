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
    public partial class user2 : Form
    {
        public user2()
        {
            InitializeComponent();
            Table();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void user2_Load(object sender, EventArgs e)
        {

        }

        //从数据库读取数据显示在表格控件中
        public void Table()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql = "select * from t_book";
            IDataReader dc = dao.read(sql);//逐行读取数据库的查询的结果
            while (dc.Read())//dc.Read():读取一行数据,读完会返回一个false
            {
                dataGridView1.Rows.Add(dc[0].ToString(), dc[1].ToString(), dc[2].ToString(), dc[3].ToString(), dc[4].ToString());
            }
            dc.Close();
            dao.DaoClose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string id = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();//获取书号
            int number = int.Parse(dataGridView1.SelectedRows[0].Cells[4].Value.ToString());//库存
            if (number < 1)
            {
                MessageBox.Show("库存不足，请联系管理员购入");

            }
            else
            {
                string sql = $"insert into t_lend ([uid],bid,[datetime]) values('{Data.UID}','id',GETDATE());Update t_book set number=number-1 where id = '{id}'";
                Dao dao = new Dao();
                if (dao.Execute(sql) > 1)//执行了两条sql，大于1才是都成功
                {
                    MessageBox.Show($"用户{Data.UName}借出了图书{id}");
                    Table();
                 }
                else
                {
                    MessageBox.Show("借出失败"+sql);
                }
            }
        }
    }
}
