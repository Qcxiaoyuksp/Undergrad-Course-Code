
namespace HotelMS
{
    partial class hotel
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.宾馆信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.客房信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.客户信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.宾馆信息ToolStripMenuItem,
            this.客房信息ToolStripMenuItem,
            this.客户信息ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 30);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 宾馆信息ToolStripMenuItem
            // 
            this.宾馆信息ToolStripMenuItem.Name = "宾馆信息ToolStripMenuItem";
            this.宾馆信息ToolStripMenuItem.Size = new System.Drawing.Size(83, 26);
            this.宾馆信息ToolStripMenuItem.Text = "宾馆管理";
            this.宾馆信息ToolStripMenuItem.Click += new System.EventHandler(this.宾馆信息ToolStripMenuItem_Click);
            // 
            // 客房信息ToolStripMenuItem
            // 
            this.客房信息ToolStripMenuItem.Name = "客房信息ToolStripMenuItem";
            this.客房信息ToolStripMenuItem.Size = new System.Drawing.Size(83, 26);
            this.客房信息ToolStripMenuItem.Text = "客房管理";
            this.客房信息ToolStripMenuItem.Click += new System.EventHandler(this.客房信息ToolStripMenuItem_Click);
            // 
            // 客户信息ToolStripMenuItem
            // 
            this.客户信息ToolStripMenuItem.Name = "客户信息ToolStripMenuItem";
            this.客户信息ToolStripMenuItem.Size = new System.Drawing.Size(83, 26);
            this.客户信息ToolStripMenuItem.Text = "客户管理";
            this.客户信息ToolStripMenuItem.Click += new System.EventHandler(this.客户信息ToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("华文新魏", 33F);
            this.label1.Location = new System.Drawing.Point(170, 71);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(464, 56);
            this.label1.TabIndex = 7;
            this.label1.Text = "宾馆客房管理系统";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::HotelMS.Properties.Resources.OIP__1_;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(800, 450);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            // 
            // hotel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.pictureBox1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "hotel";
            this.Text = "hotel";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 宾馆信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 客房信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 客户信息ToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}