/******************************************************************************
  Author:ZC    Version :1.2          Date:2017/02/10
  Description:    developing version. 
  History:
    <author>  <time>   <version>   <description>
    ZC        2017/2/7     1.0      initialization.
    ZC        2017/2/8     1.1      create random expression
    ZC        2017/2/10     1.2     solve the problem：divide by zero error.
*****************************************************************************/
#include<iostream>
#include<string>
#include<stack>
#include<cstdlib>
#include<ctime>
#include<cctype>

using namespace std;

/*随机生成运算符相关，对于小学生，要减少除法出现的概率*/
char *rand_Oper_List = "+-*/+-*+*/-+*-+/*-+-*-+*/-+*-*+-*/+-*+*+-*-+*-+/*/+-/*-++-*/-*+-+*";
const int operListLen = strlen(rand_Oper_List);

/*随机数、随机种子相关*/
static unsigned int long seed = (unsigned int)time(NULL);/*用时间定义初始种子*/
unsigned int RandomeSeed(void)/*每次随机后让种子变成一个新的*/
{
	seed = seed * 11035152465 + 12345;
	return (unsigned int)(seed / 65536) % 32768;
}
/*解释下为什么。如果只有时间作为种子，那么如果程序在一秒之内跑完，会导致所有计算题都是一样的*/

/*数据结构 栈*/
/*还没写*/


/*Expression，表达式类。类声明部分。*/
class Expression
{
private:
	string expression;
public:
	int RandomNum();
	char RandomOperator();

	Expression();
	string & AddOperator(const char oper);
	string RandomPart();
	string & AddPart(const string & part);
	int PartValue(const string & p);
	int ExpressionValue(const Expression & e);

	friend ostream & operator<<(ostream & os, const Expression &e);//重载<<运算符
};

/*类方法部分*/

Expression::Expression()
{
	expression = "";
}

/*随机生成一个数字，范围0~10*/
int Expression::RandomNum()
{
	srand(RandomeSeed());
	int randNum;
	randNum = rand() % 11;
	return randNum;
}

/*随机生成一个操作符并返回，返回值类型char*/
char Expression::RandomOperator()
{
	int randOperIndex;
	srand(RandomeSeed());
	randOperIndex = rand() % operListLen;
	return rand_Oper_List[randOperIndex];
}

/*把操作符oper连接在expression后*/
string & Expression::AddOperator(const char oper)
{
	expression += oper;
	return expression;
}

/*part：随机生成一个操作数、或一个形如（a+b）的部分，并返回。返回值是string类型。*/
string Expression::RandomPart()
{
	int randChoice;/*如果为0，part为一个数；如果为1，part为形如（a+b）的式子*/
	srand(RandomeSeed());
	randChoice = rand() % 2;

	string part;

	if (randChoice == 0)
	{
		int randNum;
		randNum = RandomNum();
		if (randNum == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum + 48);/*这里用的是string类构造函数：string(char c);*/
		}
	}

	else if (randChoice == 1)
	{
		int randNum1;
		randNum1 = RandomNum();

		part += "(";
		if (randNum1 == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum1 + 48);
		}

		char oper = RandomOperator();
		part += oper;

		int randNum2;
		randNum2 = RandomNum();

		if (oper == '/') //如果出现了触发，要确保第二个数不为0
		{
			while (randNum2 == 0)
				randNum2 = RandomNum();
		}

		if (randNum2 == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum2 + 48);
		}

		part += ")";
	}

	return part;
}

string & Expression::AddPart(const string & part)
{
	expression += part;
	return expression;
}

int Expression::PartValue(const string & p)
{
	int val;
	if (p[0] == '(')//part是形如（a+b）的
	{
		int num1 = p[1];
		char oper = p[2];
		int num2 = p[3];

		switch (oper)
		{
		case'+':
			val = num1 + num2;
			break;
		case'-':
			val = num1 - num2;
			break;
		case'*':
			val = num1*num2;
			break;
		case'/':
			val = num1 / num2;
			break;
		default:
			break;
		}
	}

	else //part是一个数
	{
		val = p[0] - '0';
	}

	return val;
}

ostream & operator<<(ostream & os, const Expression & e)
{
	os << e.expression;
	return os;
}

/*以下是非成员函数*/

int GetInt(void)/*输入检测*/
{
	int input;
	char ch;
	cout << "请输入一个范围在1~100之间的正整数，代表你想做的题目的数量（0代表退出）：";
	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << "你的输入：";
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << " 不符合要求\n";
		cout << "请输入一个范围在1~100之间的正整数（0代表退出）：";
	}
	while (input <= 0 || input > 100)
	{
		if (input < 0)
		{
			cout << "你输入的数字太小。（你还想不想做题？）" << endl;
			input = GetInt();
		}
		if (input > 100)
		{
			cout << "你输入的数字太大。（有必要做那么多吗？）" << endl;
			input = GetInt();
		}
		if (input == 0)
		{
			cout << "拜拜!~" << endl;
			return 0;
		}
	}
	return input;
}

/*用于测试函数func1、func2、func3和输入函数*/
int main()
{
	int n;
	n = GetInt();

	int i = 1;
	int answer;
	for (; i <= n; i++)
	{
		Expression expression;

		string randPart = expression.RandomPart();
		expression.AddPart(randPart);

		for (int j = 0; j < 3; j++)/*这里的3可以改成随机长度，例如2~4*/
		{
			char oper;
			oper = expression.RandomOperator();
			expression.AddOperator(oper);

			randPart = expression.RandomPart();
			if (oper == '/')	//如果出现了除号，那要确保除数不为零
			{
				int val = expression.PartValue(randPart);
				while (val == 0)
				{
					randPart = expression.RandomPart();
					val = expression.PartValue(randPart);
				}
			}
			expression.AddPart(randPart);
		}

		cout << "第" << i << "题:" << expression << endl;
		cout << "\t请输入你的答案：";
		cin >> answer;
		/*
		判定过程还没写
		*/
		cout << "恭喜你，回答正确\n" << endl;
	}
	cout << "\n结果统计：您做对了XX题，做错了XX题，正确率XX" << endl;

	cout << "拜拜！~" << endl;
	return 0;
}

//*接受一个string参数，代表中缀表达式。返回一个string，其内容是这个中缀表达式所对应的逆波兰式*/
/*string & Expression::ReversePolishNotation(string & InfixExp)
{

}
/*还没写*/

/*怎么把int数值 连到string参数后 的例子*/
//int main()
//{
//	string s;
//	int a = 9;
//	s += (char)(a + 48);
//	cout << s << endl;
//	return 0;
//}

/*string 的遍历方法*/
//int main()
//{
//	string s = "123456789";
//	int iSize = s.length();
//	
//
//	int i = 0;
//	for (i = 0; i < iSize; i++)
//	{
//		cout << s[i];
//	}
//	return 0;
//}

/*判断结果是不是整数*/
/*对于小学生来说，结果不是整数的题，就放弃，重出一题*/
//double x;  用浮点数存结果
//scanf("%f", &x);
//if ((int)x == x)
//printf("%f是整数", x);
