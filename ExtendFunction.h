#pragma once
/******************************************************
文件名： ExtendFunction.h
作者：HXP  润色修改：ZC  日期：2016/02/15
描述: 其他的外部函数。
主要功能包括：语言选择、输入检测、题目生成以及显示、答案判定
*******************************************************/
#include"Expression.h"

/*中英文语言选择，1为中文，2为英文*/
int LanguageChoice()
{
	int input;
	char ch;

	cout << "您想使用什么语言？  /  Which language do you want to use? " << endl;
	cout << "中文请输入： 1" << endl;
	cout << "Please input 2 for English. " << endl;
	cout << "请输入您的选择： /  Please input your choice: ";

	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << "你的输入  /  Your input：";
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << endl;
		cout << "您的输入有误  /  Your input is undesirable.\n";
		cout << "中文请输入： 1" << endl;
		cout << "Please input 2 for English. " << endl;
		cout << "请输入您的选择： /  Please input your choice: ";
	}
	while (input != 1 && input != 2)
	{
		cout << "您的输入有误，请重新输入  /  The language you choose is undesirable" << endl;
		cout << "中文请输入： 1" << endl;
		cout << "Please input 2 for English. " << endl;
		cout << "请输入您的选择： /  Please input again: ";
		while (scanf_s("%d", &input) != 1)//输入的不是%d
		{
			cout << "你的输入  /  Your input：";
			while ((ch = getchar()) != '\n')
				putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
			cout << endl;
			cout << "您的输入有误  /  Your input is undesirable.\n";
			cout << "中文请输入： 1" << endl;
			cout << "Please input 2 for English. " << endl;
			cout << "请输入您的选择： /  Please input your choice: ";
		}
	}
	return input;
}

/*输入检测*/
/*下面为中英文的输入检测*/
int ChineseGetInt()
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
			input = ChineseGetInt();
		}
		if (input > 100)
		{
			cout << "你输入的数字太大。（有必要做那么多吗？）" << endl;
			input = ChineseGetInt();
		}
		if (input == 0)
		{
			cout << "拜拜!~" << endl;
			return 0;
		}
	}
	return input;
}

int EnglishGetInt()
{
	int input;
	char ch;
	cout << "The number of questions：Please input a number between 1 and 100 : ";
	while (scanf_s("%d", &input) != 1)//输入的不是%d
	{
		cout << "Your input：";
		while ((ch = getchar()) != '\n')
			putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
		cout << " Your number is undesirable.\n";
		cout << "Please input a positive number between 1 and 100 （0 means exit）：";
	}
	while (input <= 0 || input > 100)
	{
		if (input < 0)
		{
			cout << "The number you input is too small.（Do you want to exit？）" << endl;
			input = EnglishGetInt();
		}
		if (input > 100)
		{
			cout << "The number you input is too big.（Too many questions may make you boring .）" << endl;
			input = EnglishGetInt();
		}
		if (input == 0)
		{
			cout << "Goodbye!~" << endl;
			return 0;
		}
	}
	return input;
}

/*封装，根据版本不同进入不同的函数*/
int GetInt(int languageChoice)
{
	int n;
	if (languageChoice == 1)
	{
		n = ChineseGetInt();
	}
	else if (languageChoice == 2)
	{
		n = EnglishGetInt();
	}
	return n;
}

/*返回值是一个表达式类，里面的内容是题目*/
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

/*答案判定模块*/
bool Judge(int answer, Expression & e, int languageChoice)
{
	int val = e.ExpressionValue();//正确答案

	if (answer == val)
	{
		if (languageChoice == 1)
		{
			cout << "恭喜你，回答正确！" << endl << endl;
		}
		else if (languageChoice == 2)
		{
			cout << "Congratulation! Your answer is right!" << endl << endl;
		}
		return true;
	}
	else
	{
		if (languageChoice == 1)
		{
			cout << "答案错误！正确答案是：" << val << endl << endl;
		}
		else if (languageChoice == 2)
		{
			cout << "Your answer is wrong! The right answer is " << val << endl << endl;
		}
		return false;
	}
}