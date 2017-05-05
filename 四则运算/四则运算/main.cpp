/******************************************************************************
�ļ����� main.cpp
���ߣ�ZC  ���ڣ�2017/02/15
����: ��������ʵ�����幦��

���ߣ�ZC  ���ڣ�2017/03/09
���£�����Դ�ļ���������԰汾��������д����Դ�ж����Ǵ����У��ʶ�ԭ�д�������ع�

ע������Resource[i]�е�������ע��ͷ�ļ�LanguageResource.h�ڵ�ע��˵��

���ߣ�ZC  ���ڣ�2017/04/23 
���£����������scan�����������û���������ȡ������Ϣ��һ��Print����������������
*******************************************************************************/
#include "Expression.h"
#include "ExtendFunction.h"
#include "LanguageResource.h"
extern char *Resource[MAXLINE];

int ScanLanguage(char * language)//����scan�����������û���������ȡ������Ϣ
{
	while (CheckLanguageSupport(language) == false)//�������Լ��
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
	n = GetInt();//������
	if (n == 0)
	{
		cout << Resource[0] << endl;
		getchar();
		getchar();
		return 0;
	}
	return n;
}

void Print(int n, int numRight, int numWrong)//���ͳ�ƽ�����û�
{
	static double accuracy;//��ȷ��
	accuracy = (double)numRight / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;
}

int main()
{
	cout << "Arithmetic Test For Primary School Students" << endl << endl;
	ShowLanguageList();
	char language[200];//�û���������
	gets_s(language);
	int validLangChoice = ScanLanguage(language);
	while (1) {
		if (validLangChoice==-1)//�˳�����
		{
			return 0;
		}
		else if (validLangChoice == -2)//��������
		{
			gets_s(language);
			validLangChoice = ScanLanguage(language);
		}
		else if (validLangChoice == 1)//������ȷ
		{
			break;
		}
	}

	char Langpath[255] = "";//�����û�������ȥ�γ�һ��·��
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, language);
	strcat_s(Langpath, ".txt");

	GetResource(Langpath);

	int n;//�û�������������Ŀ����
	n = ScanNumofProblems();

	int i;
	bool result;//���ڲ��Դ���ȷ���

	int answer;//�û�������Ŀ��
	static int numRight = 0, numWrong = 0;//ͳ������������ȷ�ʹ�������

	for (i = 1; i <= n; i++)
	{
		Expression expression; //��Ŀ
		expression = CreateProblems();

		cout << "No." << i << "\t" << expression << endl;
		cout << "\t" << Resource[8];

		answer = GetAnswer();

		result = Judge(answer, expression);

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

	Print(n, numRight, numWrong);

	for (i = 0; i < 13; i++)
	{
		free(Resource[i]);
	}
	system("pause");
	return 0;
}