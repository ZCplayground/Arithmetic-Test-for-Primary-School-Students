#include<iostream>
#include<fstream>‎

#define MAXLINE 30 //资源文件内的最大行数
#define MAXLEN 200 //每行的最大字符数

#include"Expression.h"

extern char *Resource[];
using namespace std;

//存储资源文件内容的指针数组


void ShowLanguageList()
{
	fstream file;//文件流
	file.open("LangResourses\\LanguageList.txt", ios::in);

	int num = 1;
	char language[20];
	cout << "You can choose one of these languages below:" << endl;
	while (file.getline(language, 20))
	{
		cout << num << ". " << language << endl;
		num++;
	}
	file.close();
	cout << "Please input your language name (or input e to exit): ";
}

bool CheckLanguageSupport(char * users_Lang)
{
	fstream file;

	char Langpath[255] = "";//根据用户的输入去形成一个路径
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, users_Lang);
	strcat_s(Langpath, ".txt");

	file.open(Langpath, ios::in);//根据这个路径打开这个资源

	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
	{
		return NULL;
	}
}

void GetResource(char * filepath)
{
	fstream File;
	File.open(filepath, ios::in);
	char one_Line[MAXLEN];

	/*将每行文件的内容放到Resource[i]中，这样可以通过下标i访问各种语句*/
	int i;
	for (i = 0; File.getline(one_Line, MAXLEN); i++)
	{
		Resource[i] = (char *)malloc(MAXLEN * sizeof(char));
		strcpy_s(Resource[i], MAXLEN * sizeof(char), one_Line);
	}
	File.close();
}

int GetInt()
{
	int input;
	char ch;

	cout << Resource[1];

	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << Resource[3] << endl;

		cout << Resource[1];
	}

	while ((ch = getchar()) != '\n' && ch != EOF);

	while (input <= 0 || input > 100)
	{
		if (input < 0)
		{
			cout << Resource[4] << endl;
			input = GetInt();
		}
		if (input > 100)
		{
			cout << Resource[5] << endl;
			input = GetInt();
		}
		if (input == 0)
		{
			return 0;
		}
	}
	return input;
}

int GetAnswer()
{
	int input;
	char ch;

	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << Resource[2];
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << Resource[3] << endl;

		cout << Resource[8];
	}

	while ((ch = getchar()) != '\n' && ch != EOF);

	return input;
}

Expression CreateProblems()
{
	int val = FALSE;//正确答案
	Expression expression;

	expression.CreateInfixExpression();
	expression.ReversePolishNotation();
	val = expression.ExpressionValue();

	while (val == FALSE)//确保不会出现答案为非整数的题目
	{
		Expression expression;

		expression.CreateInfixExpression();
		expression.ReversePolishNotation();
		val = expression.ExpressionValue();
	}
	return expression;
}

bool Judge(int answer, Expression & e)
{
	int val = e.ExpressionValue();//正确答案

	if (answer == val)
	{
		cout << Resource[6] << endl << endl;
		return true;
	}
	else
	{
		cout << Resource[7] << val << endl << endl;
		return false;
	}
}

int ScanLanguage(char * language)//两个scan函数用于与用户交互并获取输入信息
{
	while (CheckLanguageSupport(language) == false)//输入语言检测
	{
		if (strcmp("e", language) == 0)
		{
			cout << endl << "The program is going to be finished. Goodbye!~" << endl;
			getchar();
			return -1;
		}
		cout << "Sorry. Your input is wrong or software does not support your language. " << endl;

		ShowLanguageList();
		return -2;
	}
	return 1;
}

int ScanNumofProblems()
{
	int n;
	n = GetInt();//输入检测
	if (n == 0)
	{
		cout << Resource[0] << endl;
		getchar();
		getchar();
		return 0;
	}
	return n;
}

void Print(int n, int numRight, int numWrong)
{
	static double accuracy;//正确率
	accuracy = (double)numRight / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;
}

int ReadFile(char *filename)//filename是绝对路径
{
	int n;
	fstream f;
	f.open(filename, ios::in);
	f >> n;
	f.close();
	return n;
}

void WriteExpression(char *filename, Expression expression, int useranswer, int rightanswer, int i)
{
	fstream f;
	f.open(filename, ios::app);

	f << "No." << i << "\t" << expression << endl;
	f << Resource[13] << ": " << useranswer << endl;
	f << Resource[14] << ": " << rightanswer << endl << endl;

	f.close();
	return;
}

void WriteResult(char *filename, int n, int numRight, int numWrong)
{
	fstream f;
	f.open(filename, ios::app);

	static double accuracy;//正确率
	accuracy = (double)numRight / n * 100;

	f << Resource[9] << endl << endl;
	f << Resource[10] << numRight << endl;
	f << Resource[11] << numWrong << endl;
	f << Resource[12] << accuracy << "%" << endl;

	f.close();
	return;
}