namespace Student
{
    partial class frmEdit
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
            this.cb_sex = new System.Windows.Forms.ComboBox();
            this.tb_age = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tb_name = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.dg_result = new System.Windows.Forms.DataGridView();
            this.btn_update = new System.Windows.Forms.Button();
            this.tb_stuid = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_delete = new System.Windows.Forms.Button();
            this.tb_rowid = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).BeginInit();
            this.SuspendLayout();
            // 
            // cb_sex
            // 
            this.cb_sex.FormattingEnabled = true;
            this.cb_sex.Items.AddRange(new object[] {
            "男",
            "女"});
            this.cb_sex.Location = new System.Drawing.Point(86, 72);
            this.cb_sex.Name = "cb_sex";
            this.cb_sex.Size = new System.Drawing.Size(116, 20);
            this.cb_sex.TabIndex = 24;
            // 
            // tb_age
            // 
            this.tb_age.Location = new System.Drawing.Point(279, 72);
            this.tb_age.Name = "tb_age";
            this.tb_age.Size = new System.Drawing.Size(117, 21);
            this.tb_age.TabIndex = 23;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(232, 75);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 22;
            this.label4.Text = "年龄：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(38, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 21;
            this.label3.Text = "性别：";
            // 
            // tb_name
            // 
            this.tb_name.Location = new System.Drawing.Point(279, 40);
            this.tb_name.Name = "tb_name";
            this.tb_name.Size = new System.Drawing.Size(117, 21);
            this.tb_name.TabIndex = 20;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(232, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 19;
            this.label2.Text = "姓名：";
            // 
            // dg_result
            // 
            this.dg_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_result.Location = new System.Drawing.Point(12, 106);
            this.dg_result.MultiSelect = false;
            this.dg_result.Name = "dg_result";
            this.dg_result.RowTemplate.Height = 23;
            this.dg_result.Size = new System.Drawing.Size(608, 232);
            this.dg_result.TabIndex = 18;
            this.dg_result.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dg_result_CellMouseClick);
            // 
            // btn_update
            // 
            this.btn_update.Location = new System.Drawing.Point(420, 70);
            this.btn_update.Name = "btn_update";
            this.btn_update.Size = new System.Drawing.Size(75, 23);
            this.btn_update.TabIndex = 17;
            this.btn_update.Text = "更新";
            this.btn_update.UseVisualStyleBackColor = true;
            this.btn_update.Click += new System.EventHandler(this.btn_update_Click);
            // 
            // tb_stuid
            // 
            this.tb_stuid.Location = new System.Drawing.Point(85, 37);
            this.tb_stuid.Name = "tb_stuid";
            this.tb_stuid.Size = new System.Drawing.Size(117, 21);
            this.tb_stuid.TabIndex = 16;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(38, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 15;
            this.label1.Text = "学号：";
            // 
            // btn_delete
            // 
            this.btn_delete.Location = new System.Drawing.Point(515, 69);
            this.btn_delete.Name = "btn_delete";
            this.btn_delete.Size = new System.Drawing.Size(75, 23);
            this.btn_delete.TabIndex = 25;
            this.btn_delete.Text = "删除";
            this.btn_delete.UseVisualStyleBackColor = true;
            this.btn_delete.Click += new System.EventHandler(this.btn_delete_Click);
            // 
            // tb_rowid
            // 
            this.tb_rowid.Location = new System.Drawing.Point(86, 5);
            this.tb_rowid.Name = "tb_rowid";
            this.tb_rowid.ReadOnly = true;
            this.tb_rowid.Size = new System.Drawing.Size(116, 21);
            this.tb_rowid.TabIndex = 27;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(39, 8);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 26;
            this.label5.Text = "Rowid：";
            // 
            // frmEdit
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(629, 349);
            this.Controls.Add(this.tb_rowid);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.btn_delete);
            this.Controls.Add(this.cb_sex);
            this.Controls.Add(this.tb_age);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tb_name);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.dg_result);
            this.Controls.Add(this.btn_update);
            this.Controls.Add(this.tb_stuid);
            this.Controls.Add(this.label1);
            this.Name = "frmEdit";
            this.Text = "修改删除";
            this.Load += new System.EventHandler(this.frmEdit_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cb_sex;
        private System.Windows.Forms.TextBox tb_age;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tb_name;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.DataGridView dg_result;
        private System.Windows.Forms.Button btn_update;
        private System.Windows.Forms.TextBox tb_stuid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_delete;
        private System.Windows.Forms.TextBox tb_rowid;
        private System.Windows.Forms.Label label5;
    }
}