namespace 四则运算GUI
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox_answer = new System.Windows.Forms.TextBox();
            this.Lbl_Expression = new System.Windows.Forms.Label();
            this.Btn_CreateProblem = new System.Windows.Forms.Button();
            this.Btn_Judge = new System.Windows.Forms.Button();
            this.Btn_Clear = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.Lbl_Right = new System.Windows.Forms.Label();
            this.Lbl_Wrong = new System.Windows.Forms.Label();
            this.Lbl_NumWrong = new System.Windows.Forms.Label();
            this.Lbl_NumRight = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBox_answer
            // 
            this.textBox_answer.Font = new System.Drawing.Font("宋体", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox_answer.Location = new System.Drawing.Point(254, 81);
            this.textBox_answer.Name = "textBox_answer";
            this.textBox_answer.Size = new System.Drawing.Size(100, 34);
            this.textBox_answer.TabIndex = 1;
            // 
            // Lbl_Expression
            // 
            this.Lbl_Expression.AutoSize = true;
            this.Lbl_Expression.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Lbl_Expression.Location = new System.Drawing.Point(50, 41);
            this.Lbl_Expression.Name = "Lbl_Expression";
            this.Lbl_Expression.Size = new System.Drawing.Size(0, 19);
            this.Lbl_Expression.TabIndex = 2;
            // 
            // Btn_CreateProblem
            // 
            this.Btn_CreateProblem.Font = new System.Drawing.Font("宋体", 9F);
            this.Btn_CreateProblem.Location = new System.Drawing.Point(54, 136);
            this.Btn_CreateProblem.Name = "Btn_CreateProblem";
            this.Btn_CreateProblem.Size = new System.Drawing.Size(78, 53);
            this.Btn_CreateProblem.TabIndex = 3;
            this.Btn_CreateProblem.Text = "出题";
            this.Btn_CreateProblem.UseVisualStyleBackColor = true;
            this.Btn_CreateProblem.Click += new System.EventHandler(this.Btn_CreateProblem_Click);
            // 
            // Btn_Judge
            // 
            this.Btn_Judge.Location = new System.Drawing.Point(177, 136);
            this.Btn_Judge.Name = "Btn_Judge";
            this.Btn_Judge.Size = new System.Drawing.Size(75, 53);
            this.Btn_Judge.TabIndex = 4;
            this.Btn_Judge.Text = "判定";
            this.Btn_Judge.UseVisualStyleBackColor = true;
            this.Btn_Judge.Click += new System.EventHandler(this.Btn_Judge_Click);
            // 
            // Btn_Clear
            // 
            this.Btn_Clear.Location = new System.Drawing.Point(296, 136);
            this.Btn_Clear.Name = "Btn_Clear";
            this.Btn_Clear.Size = new System.Drawing.Size(75, 53);
            this.Btn_Clear.TabIndex = 5;
            this.Btn_Clear.Text = "清空";
            this.Btn_Clear.UseVisualStyleBackColor = true;
            this.Btn_Clear.Click += new System.EventHandler(this.Btn_Clear_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new System.Drawing.Point(52, 221);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(319, 139);
            this.listBox1.TabIndex = 6;
            // 
            // Lbl_Right
            // 
            this.Lbl_Right.AutoSize = true;
            this.Lbl_Right.Location = new System.Drawing.Point(96, 388);
            this.Lbl_Right.Name = "Lbl_Right";
            this.Lbl_Right.Size = new System.Drawing.Size(67, 15);
            this.Lbl_Right.TabIndex = 7;
            this.Lbl_Right.Text = "共做对：";
            // 
            // Lbl_Wrong
            // 
            this.Lbl_Wrong.AutoSize = true;
            this.Lbl_Wrong.Location = new System.Drawing.Point(235, 388);
            this.Lbl_Wrong.Name = "Lbl_Wrong";
            this.Lbl_Wrong.Size = new System.Drawing.Size(67, 15);
            this.Lbl_Wrong.TabIndex = 8;
            this.Lbl_Wrong.Text = "共做错：";
            // 
            // Lbl_NumWrong
            // 
            this.Lbl_NumWrong.AutoSize = true;
            this.Lbl_NumWrong.Location = new System.Drawing.Point(297, 388);
            this.Lbl_NumWrong.Name = "Lbl_NumWrong";
            this.Lbl_NumWrong.Size = new System.Drawing.Size(0, 15);
            this.Lbl_NumWrong.TabIndex = 9;
            // 
            // Lbl_NumRight
            // 
            this.Lbl_NumRight.AutoSize = true;
            this.Lbl_NumRight.Location = new System.Drawing.Point(157, 388);
            this.Lbl_NumRight.Name = "Lbl_NumRight";
            this.Lbl_NumRight.Size = new System.Drawing.Size(0, 15);
            this.Lbl_NumRight.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(96, 91);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 15);
            this.label1.TabIndex = 11;
            this.label1.Text = "请点击出题按钮：";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(441, 434);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Lbl_NumRight);
            this.Controls.Add(this.Lbl_NumWrong);
            this.Controls.Add(this.Lbl_Wrong);
            this.Controls.Add(this.Lbl_Right);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.Btn_Clear);
            this.Controls.Add(this.Btn_Judge);
            this.Controls.Add(this.Btn_CreateProblem);
            this.Controls.Add(this.Lbl_Expression);
            this.Controls.Add(this.textBox_answer);
            this.Name = "Form1";
            this.Text = "简易四则运算练习器";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox textBox_answer;
        private System.Windows.Forms.Label Lbl_Expression;
        private System.Windows.Forms.Button Btn_CreateProblem;
        private System.Windows.Forms.Button Btn_Judge;
        private System.Windows.Forms.Button Btn_Clear;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label Lbl_Right;
        private System.Windows.Forms.Label Lbl_Wrong;
        private System.Windows.Forms.Label Lbl_NumWrong;
        private System.Windows.Forms.Label Lbl_NumRight;
        private System.Windows.Forms.Label label1;
    }
}

