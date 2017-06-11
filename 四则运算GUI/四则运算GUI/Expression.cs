using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 四则运算GUI
{
    class Expression
    {
        public const int FALSE = -9999;//在表达式的计算值不符合要求时，是FALSE

        Random rnd = new Random();

        string expression;
        string reversePolishNotation;
        int value;

        /*构造函数*/
        public Expression()
        {
            expression = "";
            reversePolishNotation = "";
            value = FALSE;
        }

        /*随机生成一个数字，范围0~10*/
        private int RandomNum()
        {
            int randNum = rnd.Next(11);
            return randNum;
        }

        /*随机生成一个操作符并返回*/
        private char RandomOperator()
        {
            int randOperIndex = rnd.Next(4);
            char randOper;
            switch (randOperIndex)
            {
                case 0: randOper = '+'; break;
                case 1: randOper = '-'; break;
                case 2: randOper = '*'; break;
                case 3: randOper = '/'; break;
                default: randOper = '-'; break;
            }
            return randOper;
        }

        /*把操作符oper连接在expression后*/
        private string AddOperator(char oper)
        {
            expression += oper;
            return expression;
        }

        /*part：随机生成一个操作数、或一个形如（a+b）的部分，并返回。返回值是string类型。*/
        private string RandomPart()
        {
            int randChoice;/*如果为0，part为一个数；如果为1，part为形如（a+b）的式子*/
            randChoice = rnd.Next(2);

            string part = null;

            if (randChoice == 0)
            {
                int randNum = RandomNum();
                if (randNum == 10)
                {
                    part += "10";
                }
                else
                {
                    part += randNum.ToString();
                }
            }
            else if (randChoice == 1)
            {
                int randNum = RandomNum();

                part += "(";
                if (randNum == 10)
                {
                    part += "10";
                }
                else
                {
                    part += randNum.ToString();
                }

                char oper = RandomOperator();
                part += oper;

                randNum = RandomNum();

                if (oper == '/') //如果出现了除法，要确保第二个数不为0
                {
                    while (randNum == 0)
                        randNum = RandomNum();
                }

                if (randNum == 10)
                {
                    part += "10";
                }
                else
                {
                    part += randNum.ToString();
                }
                part += ")";
            }
            return part;
        }

        /*参数是一个string类型，代表一个part，作用是将这个part连接到私有成员expression后面*/
        private string AddPart(string part)
        {
            expression += part;
            return expression;
        }

        /*参数是一个string类型，代表一个part，返回值是这个part的计算值*/
        private int PartValue(string part)
        {
            int val = FALSE;
            char oper;
            int num1;
            int num2;

            //要防止(7*1)+(5-6)*(9*8)/10+9
            if (part[0] == '(')//part是形如（a+b）的  但有可能出现(10+5) (5+10) (10+10)
            {
                if (part.Length == 7) //形如 (10+10)
                {
                    oper = part[3];
                    num1 = num2 = 10;
                }
                else if (part.Length == 6) //形如 (10+a)
                {
                    if (part[1] == '1' && part[2] == '0')//形如 (10+a)
                    {
                        num1 = 10;
                        oper = part[3];
                        num2 = part[4] - '0';//Ascll码字符转换int数值 
                    }
                    else //或(a+10)
                    {
                        num1 = part[1] - '0';
                        oper = part[2];
                        num2 = 10;
                    }
                }
                else //形如 (a+b)
                {
                    oper = part[2];
                    num1 = part[1] - '0';
                    num2 = part[3] - '0';
                }

                switch (oper)
                {
                    case '+':
                        val = num1 + num2;
                        break;
                    case '-':
                        val = num1 - num2;
                        break;
                    case '*':
                        val = num1 * num2;
                        break;
                    case '/':
                        //如果出现除法，两种情况要返回FLASE。第一个：除数为0，第二个：不能整除
                        if (num1 % num2 != 0 || num2 == 0)
                        {
                            return FALSE;
                        }
                        else
                        {
                            val = num1 / num2;
                        }
                        break;
                    default:
                        break;
                }
            }

            else //part是一个数
            {
                //if (part[0] == '1'&&part[1] == '0')
                if (part.Length == 2)
                {
                    val = 10;
                }
                else
                {
                    val = part[0] - '0';
                }
            }

            return val;
        }

        /*随机生成一个中缀表达式*/
        public Expression CreateInfixExpression()
        {
            int rank;
            rank = rnd.Next(3) + 2;//rank为2~4，意思是长度可变的中缀式子

            int val1, val2;//val1代表前面的，val2代表后面的，防止出现前面除以后面不整除

            string randPart = RandomPart();
            val1 = PartValue(randPart);
            while (val1 == FALSE)//防止了（7/5）   
            {
                randPart = RandomPart();
                val1 = PartValue(randPart);
            }
            AddPart(randPart);

            int i;
            for (i = 0; i < rank; i++)
            {
                char oper = RandomOperator();
                AddOperator(oper);

                randPart = RandomPart();
                val2 = PartValue(randPart);
                if (oper == '/')    //如果出现了除号，那要确保除数不为零
                {
                    while (val2 == 0 || val1 % val2 != 0)
                    {
                        randPart = RandomPart();
                        val2 = PartValue(randPart);
                    }
                }
                else
                {
                    while (val2 == FALSE)
                    {
                        randPart = RandomPart();
                        val2 = PartValue(randPart);
                    }
                }

                //扩展val1 = val2;
                if (oper == '/')//  要防止： 8/(7-3)/4
                {
                    val1 = val1 / val2;
                }
                else if (oper == '*')
                {
                    val1 = val1 * val2;
                }
                else
                {
                    val1 = val2;
                }
                AddPart(randPart);
            }
            return this;
        }

        /*根据类成员expression的中缀表达式，生成其对应的逆波兰式，放到成员reversePolishNotation中*/
        public void ReversePolishNotation()
        {
            Stack<char> s1 = new Stack<char>();
            Stack<char> s2 = new Stack<char>();

            int i;
            char ch;
            int size = expression.Length;

            for (i = 0; i < size; i++)
            {
                switch (expression[i])
                {
                    case '(':
                        s1.Push(expression[i]);
                        break;
                    case ')':
                        while (s1.Peek() != '(')
                        {
                            ch = s1.Peek();
                            s1.Pop();
                            s2.Push(ch);
                        }
                        ch = s1.Peek();
                        s1.Pop();
                        break;

                    case '+':
                    case '-':
                        if (s1.Count != 0)
                        {
                            for (ch = s1.Peek(); s1.Count != 0; ch = s1.Peek())
                            {
                                if (ch == '(')
                                    break;
                                else
                                {
                                    ch = s1.Peek();
                                    s1.Pop();
                                    s2.Push(ch);
                                }
                                if (s1.Count == 0) break;
                            }
                        }
                        s1.Push(expression[i]);
                        break;

                    case '*':
                    case '/':
                        if (s1.Count != 0)
                        {
                            for (ch = s1.Peek(); s1.Count != 0 && ch != '+' && ch != '-'; ch = s1.Peek())
                            {
                                if (ch == '(')
                                    break;
                                else
                                {
                                    ch = s1.Peek();
                                    s1.Pop();
                                    s2.Push(ch);
                                }
                                if (s1.Count == 0) break;
                            }
                        }
                        s1.Push(expression[i]);
                        break;

                    case '1':
                        //if(expression[i+1]=='0')//如果1是表达式的最后一个数字会有异常
                        if (i < expression.Length - 1 && expression[i + 1] == '0')
                        {
                            s2.Push('#');
                            i++;
                        }
                        else
                        {
                            goto default;
                        }
                        break;
                    default://数字
                        s2.Push(expression[i]);
                        break;
                }
            }
            while (s1.Count != 0)
            {
                ch = s1.Peek();
                s1.Pop();
                s2.Push(ch);
            }
            string temp = null;
            for (; s2.Count != 0;)
            {
                ch = s2.Peek();
                s2.Pop();
                temp += ch;
            }
            int j = temp.Length - 1;
            for (; j >= 0; j--)
            {
                reversePolishNotation += temp[j];
            }
        }

        /*根据逆波兰式，求出表达式的值，放到私有成员value中。结果如果是整数，则返回整数。如果不是整数，返回FALSE。*/
        public int CalculateValue()
        {
            Stack<int> s = new Stack<int>();
            int size = reversePolishNotation.Length;

            int num1, num2;//因为有用#代表10，就先用int存
            int i;

            for (i = 0; i < size; i++)
            {
                switch (reversePolishNotation[i])
                {
                    case '+':
                        num1 = s.Peek();
                        s.Pop();
                        num2 = s.Peek();
                        s.Pop();
                        s.Push(num1 + num2);
                        break;

                    case '-':
                        num1 = s.Peek();
                        s.Pop();
                        num2 = s.Peek();
                        s.Pop();
                        s.Push(num2 - num1);
                        break;

                    case '*':
                        num1 = s.Peek();
                        s.Pop();
                        num2 = s.Peek();
                        s.Pop();
                        s.Push(num1 * num2);
                        break;

                    case '/':
                        num1 = s.Peek();
                        s.Pop();
                        num2 = s.Peek();
                        s.Pop();
                        //只有做除法时可能出现答案为非整数的情况
                        if (num2 % num1 == 0)
                        {
                            s.Push(num2 / num1);
                        }
                        else
                        {
                            return FALSE;
                        }
                        break;

                    case '#'://数值10
                        s.Push(10);
                        break;

                    default://其他数值
                        s.Push(reversePolishNotation[i] - '0');
                        break;
                }
            }
            value = s.Peek();
            return value;
        }
        
        public string display()
        {
            return expression;
        }
    }
}
