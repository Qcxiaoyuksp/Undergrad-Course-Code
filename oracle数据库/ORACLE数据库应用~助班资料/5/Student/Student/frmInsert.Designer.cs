namespace Student
{
    partial class frmInsert
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dg_result = new System.Windows.Forms.DataGridView();
            this.btn_insert = new System.Windows.Forms.Button();
            this.tb_stuid = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tb_name = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tb_age = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cb_sex = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).BeginInit();
            this.SuspendLayout();
            // 
            // dg_result
            // 
            this.dg_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_result.Location = new System.Drawing.Point(2, 103);
            this.dg_result.Name = "dg_result";
            this.dg_result.RowTemplate.Height = 23;
            this.dg_result.Size = new System.Drawing.Size(608, 232);
            this.dg_result.TabIndex = 7;
            // 
            // btn_insert
            // 
            this.btn_insert.Location = new System.Drawing.Point(424, 61);
            this.btn_insert.Name = "btn_insert";
            this.btn_insert.Size = new System.Drawing.Size(75, 23);
            this.btn_insert.TabIndex = 6;
            this.btn_insert.Text = "添加";
            this.btn_insert.UseVisualStyleBackColor = true;
            this.btn_insert.Click += new System.EventHandler(this.btn_insert_Click);
            // 
            // tb_stuid
            // 
            this.tb_stuid.Location = new System.Drawing.Point(75, 12);
            this.tb_stuid.Name = "tb_stuid";
            this.tb_stuid.Size = new System.Drawing.Size(100, 21);
            this.tb_stuid.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "学号：";
            // 
            // tb_name
            // 
            this.tb_name.Location = new System.Drawing.Point(285, 15);
            this.tb_name.Name = "tb_name";
            this.tb_name.Size = new System.Drawing.Size(100, 21);
            this.tb_name.TabIndex = 9;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(238, 18);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "姓名：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(28, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "性别：";
            // 
            // tb_age
            // 
            this.tb_age.Location = new System.Drawing.Point(285, 63);
            this.tb_age.Name = "tb_age";
            this.tb_age.Size = new System.Drawing.Size(100, 21);
            this.tb_age.TabIndex = 13;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(238, 66);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "年龄：";
            // 
            // cb_sex
            // 
            this.cb_sex.FormattingEnabled = true;
            this.cb_sex.Items.AddRange(new object[] {
            "男",
            "女"});
            this.cb_sex.Location = new System.Drawing.Point(76, 63);
            this.cb_sex.Name = "cb_sex";
            this.cb_sex.Size = new System.Drawing.Size(99, 20);
            this.cb_sex.TabIndex = 14;
            // 
            // frmInsert
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(612, 349);
            this.Controls.Add(this.cb_sex);
            this.Controls.Add(this.tb_age);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tb_name);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.dg_result);
            this.Controls.Add(this.btn_insert);
            this.Controls.Add(this.tb_stuid);
            this.Controls.Add(this.label1);
            this.Name = "frmInsert";
            this.Text = "添加";
            this.Load += new System.EventHandler(this.frmInsert_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dg_result;
        private System.Windows.Forms.Button btn_insert;
        private System.Windows.Forms.TextBox tb_stuid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tb_name;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tb_age;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cb_sex;
    }
}