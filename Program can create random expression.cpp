
#include<cstdlib>
#include<ctime>
#include<string>
#include<iostream>
#include<stack>
#include<cctype>

using namespace std;

/*随机生成运算符相关，对于小学生，要减少除法出现的概率*/
char *rand_Oper_List = "+-*/+-*+*/-+*-+/*-+-*-+*/-+*-*+-*/+-*+*+-*-+*-+/*/+-/*-++-*/-*+-+*";

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

/*Expression，表达式类。类声明*/
class Expression
{
private:
	string expression;
public:
	int RandomNum();
	string & RandomOperator();
	string & RandomParts();
	//string & ReversePolishNotation(string & InfixExp);
	friend ostream & operator<<(ostream & os, const Expression &e);//<<运算符重载
};

/*类方法*/
/*随机生成一个数字，范围0~10*/
int Expression::RandomNum()
{
	srand(RandomeSeed());
	int randNum;
	randNum = rand() % 11;
	return randNum;
}

/*随机生成一个操作符，并连接到expression后*/
string & Expression::RandomOperator() 
{
	int randOperIndex;
	srand(RandomeSeed());
	randOperIndex = rand() % (strlen(rand_Oper_List));

	expression += rand_Oper_List[randOperIndex];
	return expression;
}

/*part：随机生成一个操作数、或一个形如（a+b）的部分。连到expression后*/
string & Expression::RandomParts()
{
	int randChoice;/*如果为0，part为一个数；如果为1，part为（a+b）*/
	srand(RandomeSeed());
	randChoice = rand() % 2;

	if (randChoice == 0)
	{
		int randNum;
		randNum = RandomNum();
		if (randNum == 10)
		{
			expression += "10";
		}
		else
		{
			expression += (char)(randNum + 48);/*这里用的是string类构造函数：string(char c);*/
		}
	}

	else if (randChoice == 1)
	{
		int randNum1, randNum2;
		

		randNum1 = RandomNum();
		randNum2 = RandomNum();

		expression += "(";
		if (randNum1 == 10)
		{
			expression += "10";
		}
		else
		{
			expression += (char)(randNum1 + 48);
		}
//		expression += oper;
		RandomOperator();
		if (randNum2 == 10)
		{
			expression += "10";
		}
		else
		{
			expression += (char)(randNum2 + 48);
		}
		expression += ")";
	}
	return expression;
}

ostream & operator<<(ostream & os, const Expression &e)
{
	os << e.expression << endl;
	return os;
}

int GetInt(void)/*输入检测*/
{
	int input;
	char ch;
	printf("请输入一个范围在1~100之间的正整数，代表你想做的题目的数量（0代表退出）：");
	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		printf("你的输入：");
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		printf(" 不符合要求\n");
		printf("请输入一个范围在1~100之间的正整数（0代表退出）：");
	}

	return input;
}

/*用于测试函数func1、func2、func3和输入函数*/
int main()
{
	int n;
	n = GetInt();
	while (n <= 0 || n > 100)
	{
		if (n < 0)
		{
			printf("你输入的数字太小。（你还想不想做题？）\n");
			n = GetInt();
		}
		if (n > 0)
		{
			printf("你输入的数字太大。（有必要做那么多吗？）\n");
			n = GetInt();
		}
		if (n == 0)
		{
			printf("拜拜!\n");
			return 0;
		}
	}
	int i = 1;
	int answer;
	for (; i <= n; i++)
	{
		Expression expression;
		for (int j = 0; j < 3; j++)/*这里的3可以改成随机长度，例如2~4*/
		{
			expression.RandomParts();
			expression.RandomOperator();
		}
		expression.RandomParts();
		cout << "第" << i << "题:" << expression;
		cout << "请输入你的答案：";
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

//string & ReversePolishNotation(string & InfixExp)
//{
//	stack<int>s1, s2;
//	
//	s1.push('#');
//
//	
//}

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