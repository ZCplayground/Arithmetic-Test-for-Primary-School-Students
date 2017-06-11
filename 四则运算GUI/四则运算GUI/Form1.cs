using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 四则运算GUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        static int numright = 0, numwrong = 0;
        Expression expression;

        private void Btn_Judge_Click(object sender, EventArgs e)
        {
            string ans = textBox_answer.Text;
            if (ans == "") return;//如果用户没有填写答案就返回

            string exp = Lbl_Expression.Text;
            if (exp == "") return;//如果用户还没有点击出题也返回

            int answer = int.Parse(ans);
            int result = expression.CalculateValue();
            string display = Lbl_Expression.Text;
            string displayright = "恭喜你，回答正确！";
            string displaywrong = "真可惜，回答错误！";
            if (answer == result)
            {
                display += "=" + answer.ToString() + " √ ";
                numright++;

                listBox1.Items.Add(display);
                listBox1.Items.Add(displayright);
            }
            else
            {
                display += "╳ 正确答案是: " + result.ToString();
                numwrong++;


                listBox1.Items.Add(display);
                listBox1.Items.Add(displaywrong);
            }

            Lbl_NumRight.Text = numright.ToString();
            Lbl_NumWrong.Text = numwrong.ToString();

            Btn_CreateProblem_Click(sender, e);
        }

        private void Btn_Clear_Click(object sender, EventArgs e)
        {
            label1.Text = "请点击出题按钮：";

            Lbl_Expression.Text = "";
            textBox_answer.Text = "";
            listBox1.Items.Clear();
            numright = 0;
            numwrong = 0;
            Lbl_NumRight.Text = numright.ToString();
            Lbl_NumWrong.Text = numwrong.ToString();

        }

        private void Btn_CreateProblem_Click(object sender, EventArgs e)
        {
            label1.Text = "请输入答案：";

            Lbl_NumRight.Text = numright.ToString();
            Lbl_NumWrong.Text = numwrong.ToString();

            expression = new Expression();
            int val = Expression.FALSE;//正确答案

            do
            {
                expression.CreateInfixExpression();
                expression.ReversePolishNotation();
                val = expression.CalculateValue();
            }
            while (val == Expression.FALSE);

            Lbl_Expression.Text = expression.display(); 
        }
    }
}
