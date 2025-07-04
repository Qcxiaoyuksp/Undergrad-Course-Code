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
    public partial class user3 : Form
    {
        public user3()
        {
            InitializeComponent();
            Table();
        }

        private void user3_Load(object sender, EventArgs e)
        {

        }

        //从数据库读取数据显示在表格控件中
        public void Table()
        {
            dataGridView1.Rows.Clear();//清空控件中的旧数据
            Dao dao = new Dao();//实例化操作
            string sql =$"select [no],id,name,author,[datetime] from t_lend,t_book where t_lend.bid=t_book.id and [uid]='{Data.UID}'";
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
            string no = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
            string id = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
            string sql = $"delete from t_lend where [no]={no}; update t_book set number = number+1 where id='{id}'";
            Dao dao = new Dao();
            if (dao.Execute(sql) > 1)
            {
                MessageBox.Show("归还成功");
                Table();
            }
            else
            {
                MessageBox.Show("借出失败" + sql);
            }
        }
    }
}
