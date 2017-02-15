/******************************
文件名： main.cpp
作者：ZC  日期：2016/02/15
描述: 主函数，实现主体功能
*******************************/
#include "Expression.h"
#include "ExtendFunction.h"
int main()
{
	int i;
	int n;//用户输入想做的题目数量
	int answer;//用户输入题目答案
	int languageChoice;//用户选择版本，1 中文、2 英文
	static int numRight = 0, numWrong = 0;//统计总题数、正确和错误题数

	languageChoice = LanguageChoice();
	n = GetInt(languageChoice);

	for (i = 1; i <= n; i++)
	{
		Expression expression; //题目
		expression = CreateProblems();

		if (languageChoice == 1)
		{
			cout << "第" << i << "题: " << expression << endl;
			cout << "\t请输入你的答案：";
		}
		else if (languageChoice == 2)
		{
			cout << "No." << i << ": " << expression << endl;
			cout << "\tPlease input your answer：";
		}

		cin >> answer;
		bool result = Judge(answer, expression, languageChoice);
		if (result == true)
		{
			numRight++;
		}
		else if (result == false)
		{
			numWrong++;
		}

		expression.~Expression();
	}

	if (languageChoice == 1)
	{
		cout << "结果统计：您做对了" << numRight << "题，做错了" << numWrong << "题" << endl;
		cout << "程序即将结束，拜拜！~" << endl;
	}
	else if (languageChoice == 2)
	{
		cout << "The result： Right: " << numRight << ", Wrong:" << numWrong << "." << endl;
		cout << "The Program is going to finished, GoodBye！~" << endl;
	}
	getchar();
	getchar();
	return 0;
}