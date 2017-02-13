#include<iostream>
#include<string>
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

// stack.h
//#include "stack.h"
/*数据结构栈，stack类声明*/
class Stack
{
private:
	int *Data;
	int posi;
public:
	Stack();
	~Stack();
	bool empty() const;
	int top() const;
	bool push(const int & item);
	bool pop();
	int size();
};

/*stack类方法*/
Stack::Stack()
{
	Data = new int[50];
}

Stack::~Stack()
{
	delete[] Data;
}
bool Stack::empty()const
{
	return posi == 0;
}

int Stack::top()const
{
	if (empty())
	{
		return false;
	}
	else
	{
		return Data[posi - 1];
	}
}

bool Stack::push(const int & item)
{
	if (posi < 50)
	{
		Data[posi++] = item;
		return true;
	}
	else
	{
		return false;
	}
}

bool Stack::pop()
{
	if (posi > 0)
	{
		int temp;
		temp = Data[--posi];
		return true;
	}
	else
	{
		return false;
	}
}

int Stack::size()
{
	return posi;
}

//在表达式的计算值不符合要求时，是FALSE
#define FALSE -9999

/*Expression，表达式类。类声明部分: Expression.h。*/
//#include "Expression.h"
class Expression
{
private:
	string expression;
	string reversePolishNotation;
	int value;

public:
	Expression();
	~Expression();

	int RandomNum();
	char RandomOperator();

	string & AddOperator(const char oper);
	string RandomPart();
	string & AddPart(const string & part);

	int PartValue(const string & part);
	Expression CreateInfixExpression();
	Expression ReversePolishNotation();
	int ExpressionValue();

	friend ostream & operator<<(ostream & os, const Expression &e);//重载<<运算符
};

/*表达式类，类方法部分 Expression.cpp*/

/*构造函数*/
Expression::Expression()
{
	expression = "";
	string reversePolishNotation = "";
	value = FALSE;
}

Expression::~Expression()
{

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

/*参数是一个string类型，代表一个part，作用是将这个part连接到私有成员expression后面*/
string & Expression::AddPart(const string & part)
{
	expression += part;
	return expression;
}

/*参数是一个string类型，代表一个part，返回值是这个part的计算值*/
int Expression::PartValue(const string & part)
{
	int val = FALSE;
	char oper;
	int num1;
	int num2;

	//要防止(7*1)+(5-6)*(9*8)/10+9
	if (part[0] == '(')//part是形如（a+b）的  但有可能出现(10+5) (5+10) (10+10)
	{
		if (part.length() == 7) //形如 (10+10)
		{
			oper = part[3];
			num1 = num2 = 10;
		}
		else if (part.length() == 6) //形如 (10+a)
		{
			if (part[1] == '1'&&part[2] == '0')//形如 (10+a)
			{
				num1 = 10;
				oper = part[3];
				num2 = part[4] - '0';
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
		case'+':
			val = num1 + num2;
			break;
		case'-':
			val = num1 - num2;
			break;
		case'*':
			val = num1 * num2;
			break;
		case'/':
			//如果出现除法，两种情况要返回FLASE。第一个：除数为0，第二个：不能整除
			if (num1%num2 != 0 || num2 == 0)
			{
				return FALSE;
			}
			else
			{
				val = num1 / num2;
			}
		default:
			break;
		}
	}

	else //part是一个数
	{
		if (part[0] == '1'&&part[1]=='0')
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
Expression Expression::CreateInfixExpression()
{
	srand(RandomeSeed());
	int rank;
	rank = rand() % 3 + 2; //rank为2~4，意思是长度可变的中缀式子

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
		char oper;
		oper = RandomOperator();
		AddOperator(oper);

		randPart = RandomPart();
		val2 = PartValue(randPart);
		if (oper == '/')	//如果出现了除号，那要确保除数不为零
		{
			while (val2 == 0 || val1%val2 != 0)
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
		if (oper == '/' )//  要防止： 8/(7-3)/4
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
	return *this;
}

/*参数是一个string类型，代表一个中缀表达式，返回值是string类型，是其对应的逆波兰式*/
Expression Expression::ReversePolishNotation()
{
	Stack s1, s2;

	int i;
	char ch;

	int size = expression.length();
	for (i = 0; i < size; i++)
	{
		switch (expression[i])
		{
		case'(':
			s1.push(expression[i]);
			break;
		case')':
			while (s1.top() != '(')
			{
				ch = s1.top();
				s1.pop();
				s2.push(ch);
			}
			ch = s1.top();
			s1.pop();
			break;

		case'+':
		case'-':
			for (ch = s1.top(); !s1.empty(); ch = s1.top())
			{
				if (ch == '(')
				{
					break;
				}
				else
				{
					ch = s1.top();
					s1.pop();
					s2.push(ch);
				}
			}
			s1.push(expression[i]);
			break;

		case'*':
		case'/':
			for (ch = s1.top(); !s1.empty() && ch != '+'&&ch != '-'; ch = s1.top())
			{
				if (ch == '(')
					break;
				else
				{
					ch = s1.top();
					s1.pop();
					s2.push(ch);
				}
			}
			s1.push(expression[i]);
			break;

		case'1':
			if (expression[i + 1] == '0')//说明是数字十;
			{
				//在string中，用'#'代表数值10。在计算函数中，遇到#就用10带入计算
				s2.push('#');
				i++;
				break;
			}
		default://其他数字
			s2.push(expression[i]);
		}
	}
	while (!s1.empty())
	{
		ch = s1.top();
		s1.pop();
		s2.push(ch);
	}

	string temp;
	for (; !s2.empty(); )
	{
		ch = s2.top();
		s2.pop();
		temp += ch;
	}
	int j = temp.length() - 1;
	for (; j >= 0; j--)
	{
		reversePolishNotation += temp[j];
	}
	return *this;
}

/*根据逆波兰式，求出表达式的值。结果如果是整数，则返回整数。如果不是整数，返回FALSE。*/
int Expression::ExpressionValue()
{
	Stack s;
	int size = reversePolishNotation.length();

	int num1, num2;//因为有用#代表10，就先用int存
	int i;

	for (i = 0; i < size; i++)
	{
		switch (reversePolishNotation[i])
		{
		case'+':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num1 + num2);
			break;

		case'-':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num2 - num1);
			break;

		case'*':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num1 * num2);
			break;

		case'/':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			//只有做除法时可能出现答案为非整数的情况
			if (num2%num1 == 0)
			{
				s.push(num2 / num1);
			}
			else
			{
				return FALSE;
			}
			break;

		case'#'://数值10
			s.push(10);
			break;

		default://其他数值
			s.push(reversePolishNotation[i] - '0');
			break;
		}
	}
	value = s.top();
	return value;
}

/*重载输出运算符*/
ostream & operator<<(ostream & os, const Expression & e)
{
	os << e.expression;
	return os;
}

/*以下是非成员函数*/

/*输入检测*/
int GetInt(void)
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
	int i;
	int answer;//用户输入
	int versionchoice;//1的话 中文 2 英文
					  /*
					  if(v==1)
					  ChineseDisplay();
					  else if(v==2)
					  EnglishDisplay();
					  */

	int n;
	n = GetInt();
	/*CreateProblems，返回值是答案咯，int answer = 接受*/
	/*下面的需要封装*/
	int val;//正确答案
	for (i = 1; i <= n; i++)
	{
		Expression expression;
		expression.CreateInfixExpression();
		expression.ReversePolishNotation();
		val = expression.ExpressionValue();

		while (val == FALSE)
		{
			Expression expression;

			expression.CreateInfixExpression();
			expression.ReversePolishNotation();
			val = expression.ExpressionValue();
		}
		//确保不会出现答案为非整数的题目
		cout << "第" << i << "题:" << expression << endl;
		/*封装结束*/

		/*下面是Judge()*/
		
		cout << "\t请输入你的答案：";
		cin >> answer;

		if (answer == val)
		{
			cout << "恭喜你，回答正确！" << endl << endl;
		}
		else
		{
			cout << "错误正确！正确答案是：" << val << endl << endl;
		}
		expression.~Expression();
	}
	cout << "\n结果统计：您做对了XX题，做错了XX题，正确率XX" << endl;
	cout << "拜拜！~" << endl;
	return 0;
}