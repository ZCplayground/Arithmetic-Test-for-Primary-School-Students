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

char language[200];//�û���������
int n;//�û�������������Ŀ����
static int answer;//�û�������Ŀ��
static int numRight = 0, numWrong = 0;//ͳ������������ȷ�ʹ�������
static double accuracy;//��ȷ��
extern char *Resource[MAXLINE];

bool ScanLanguage()//����scan�����������û���������ȡ������Ϣ
{
	cout << "Arithmetic Test For Primary School Students" << endl << endl;
	ShowLanguageList();

	gets_s(language);

	while (CheckLanguageSupport(language) == false)//�������Լ��
	{
		if (strcmp("e", language) == 0)
		{
			cout << endl << "The program is going to be finished. Goodbye!~" << endl;
			getchar();
			return false;
		}
		cout << "Sorry. Your input is wrong or software does not support your language. " << endl;

		ShowLanguageList();
		gets_s(language);
	}
	return true;
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

void Print()//���ͳ�ƽ�����û�
{
	accuracy = (double)numRight / n * 100;

	cout << Resource[9] << endl << endl;
	cout << Resource[10] << numRight << endl;
	cout << Resource[11] << numWrong << endl;
	cout << Resource[12] << accuracy << "%" << endl;

	cout << endl << Resource[0] << endl;
}

int main()
{
	bool validLang = ScanLanguage();
	if (!validLang)
	{
		return 0;
	}

	char Langpath[255] = "";//�����û�������ȥ�γ�һ��·��
	strcat_s(Langpath, "LangResourses\\");
	strcat_s(Langpath, language);
	strcat_s(Langpath, ".txt");

	GetResource(Langpath);
	
	n = ScanNumofProblems();

	int i;
	bool result;//���ڲ��Դ���ȷ���

	for (i = 1; i <= n; i++)
	{
		Expression expression; //��Ŀ
		expression = CreateProblems();

		cout << "No." << i << "\t" << expression << endl;
		cout << "\t" << Resource[8];

		cin >> answer;

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

	Print();

	for (i = 0; i < 13; i++)
	{
		free(Resource[i]);
	}

	getchar();
	getchar();
	return 0;
}