/******************************************************************************
文件名： main.cpp
作者：ZC  日期：2017/02/15
描述: 主函数，实现主体功能

作者：ZC  日期：2017/03/09
更新：用资源文件管理多语言版本，把语言写到资源中而不是代码中，故对原有代码进行重构

注：关于Resource[i]中的内容请注意头文件LanguageResource.h内的注释说明
*******************************************************************************/
#include "Expression.h"
#include "ExtendFunction.h"
#include "LanguageResource.h"

int main()
{
	int i;
	int n;//用户输入想做的题目数量
	int answer;//用户输入题目答案
	static int numRight = 0, numWrong = 0;//统计总题数、正确和错误题数
	double accuracy;//正确率

	cout << "Arithmetic Test For Primary School Students" << endl << endl;
	ShowLanguageList();

	char language[200];//用户输入语言
	gets_s(language);

	while (CheckLanguageSupport(language) == false)//输入语言检测
	{
		if (strcmp("e", language) == 0)
		{
			cout << endl << "The program is going to be finished. Goodbye!~" << endl;
			getchar();
			return 0;
		}
		cout << "Sorry. Your input is wrong or software does not support your language. " << endl;

		ShowLanguageList();
		gets_s(language);
	}

	char Langpath[255] = "";//根据用户的输入去形成一个路径
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, language);
	strcat_s(Langpath, ".txt");

	/*测试用例

	GetResource("LangResourses\\日本の.txt");
	for (i = 0; i < 13; i++)
	{
	cout << Resource[i] << endl;
	}
	*/

	GetResource(Langpath);
	n = GetInt();//输入检测
	if (n == 0)
	{
		cout << Resource[0] << endl;
		getchar();
		getchar();
		return 0;
	}

	for (i = 1; i <= n; i++)
	{
		Expression expression; //题目
		expression = CreateProblems();

		cout << "No." << i << "\t" << expression << endl;
		cout << "\t" << Resource[8];

		cin >> answer;

		bool result = Judge(answer, expression);
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

	accuracy = numRight*1.0 / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;

	getchar();
	getchar();
	return 0;
}