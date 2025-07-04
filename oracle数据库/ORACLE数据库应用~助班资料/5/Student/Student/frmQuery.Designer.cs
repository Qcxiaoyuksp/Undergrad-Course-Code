namespace Student
{
    partial class frmQuery
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
            this.label1 = new System.Windows.Forms.Label();
            this.tb_stuid = new System.Windows.Forms.TextBox();
            this.dg_result = new System.Windows.Forms.DataGridView();
            this.btn_query1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(32, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "学号：";
            // 
            // tb_stuid
            // 
            this.tb_stuid.Location = new System.Drawing.Point(79, 24);
            this.tb_stuid.Name = "tb_stuid";
            this.tb_stuid.Size = new System.Drawing.Size(100, 21);
            this.tb_stuid.TabIndex = 1;
            // 
            // dg_result
            // 
            this.dg_result.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg_result.Location = new System.Drawing.Point(6, 62);
            this.dg_result.Name = "dg_result";
            this.dg_result.RowTemplate.Height = 23;
            this.dg_result.Size = new System.Drawing.Size(608, 232);
            this.dg_result.TabIndex = 3;
            // 
            // btn_query1
            // 
            this.btn_query1.Location = new System.Drawing.Point(216, 24);
            this.btn_query1.Name = "btn_query1";
            this.btn_query1.Size = new System.Drawing.Size(75, 23);
            this.btn_query1.TabIndex = 4;
            this.btn_query1.Text = "查询";
            this.btn_query1.UseVisualStyleBackColor = true;
            this.btn_query1.Click += new System.EventHandler(this.btn_query1_Click);
            // 
            // frmQuery
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(621, 303);
            this.Controls.Add(this.btn_query1);
            this.Controls.Add(this.dg_result);
            this.Controls.Add(this.tb_stuid);
            this.Controls.Add(this.label1);
            this.Name = "frmQuery";
            this.Text = "查询";
            this.Load += new System.EventHandler(this.frmQuery_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dg_result)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tb_stuid;
        private System.Windows.Forms.Button btn_query;
        private System.Windows.Forms.DataGridView dg_result;
        private System.Windows.Forms.Button btn_query1;
    }
}