/************************************

Author:HXP      Date:02/13
Description:    start development

*************************************/




#include<stdlib.h>
#include<time.h>
#include<string>
#include<iostream>

using namespace std;   /*����0~10�������*/
int rand_num()
{
    srand((unsigned) time(NULL));
	int tempnum;	
	tempnum = rand()%11;
	return tempnum;
}


char rand_oper()    /*��������ַ��������*/
{
	srand((unsigned) time(NULL));
	int temp;
	char temp_oper;
	char all_oper[]={'+','-','*','/'};
	temp = rand()%4;
	temp_oper = all_oper[temp];
	return temp_oper;
}



string rand_NumOper ()
{	
	int num1,num2;
	char oper;
	oper = rand_oper();
	num1 = rand_num();
	num2 = rand_num();
	string str;
    if(num1==10)
	{
        str = "(10";
		if(num2==0)
			str+=')';
		else 
		{
			str+=oper;
			if(num2==10)
			{
				str+="10";
				str+=')';
			}
			else
			{
				str+=(char)(num2+48);
			    str+=')';
			}
		}
	}
	else
	{
		str = '(';
        str+=(char)(num1+48);
		if(num2==0)
			str+=')';
		else
		{
			str+=oper;
			if(num2==10)
			{
				str+="10";
				str+=')';
			}
			else
			{
				str+=(char)(num2+48);
			    str+=')';
			}
		}
	}
	return str;
}
string expression()    /*����һ������������ʽ*/
{
	string str1,str2,expression;
	char outoper;
	outoper = rand_oper();
	str1 = rand_NumOper();
	expression = rand_NumOper();
	expression += outoper;
	expression += str1;
	return expression;
}


/*��Ӣ������ѡ��*/ 
string LanguageChoice()
{
	string choice,input;
	cin>>input;
	if(input == "Chi")
	{
		choice = "Chi";
	}
	else if(input == "Eng")
	{
		choice = "Eng";
	}
	else
	{
		cout<<"�����������������ʱ��֧�֣�����������  /  The language you choose is undesirable , please input again : "<<endl;
		LanguageChoice(); 
	}
	return choice;
}



/*����Ϊ��Ӣ�ĵ�������*/ 
int ChineseGetInt()
{
	int input;
    char ch;
    cout << "������һ����Χ��1~100֮�������������������������Ŀ��������0�����˳�����";
    while (scanf("%d", &input) != 1)//����Ĳ���%d
    {
        cout << "������룺";
        while ((ch = getchar()) != '\n')
            putchar(ch);//����û��������ַ���������ʾ����ַ�������������ʾ��������Ҫ��
        cout << " ������Ҫ��\n";
        cout << "������һ����Χ��1~100֮�����������0�����˳�����";
    }
    while (input <= 0 || input > 100)
    {
        if (input < 0)
        {
            cout << "�����������̫С�����㻹�벻�����⣿��" << endl;
            input = ChineseGetInt();
        }
        if (input > 100)
        {
            cout << "�����������̫�󡣣��б�Ҫ����ô���𣿣�" << endl;
            input = ChineseGetInt();
        }
        if (input == 0)
        {
            cout << "�ݰ�!~" << endl;
            return 0;
        }
    }
    return input;
}


int EnglishGetInt()
{
	int input;
    char ch;
    cout << "The numble of questions��Please input a numble between 1 and 100 : ";
    while (scanf("%d", &input) != 1)//����Ĳ���%d
    {
        cout << "Your input��";
        while ((ch = getchar()) != '\n')
            putchar(ch);//����û��������ַ���������ʾ����ַ�������������ʾ��������Ҫ��
        cout << " Your numble is undesirable.\n";
        cout << "Please input a positive numble between 1 and 100 ��0 means exit����";
    }
    while (input <= 0 || input > 100)
    {
        if (input < 0)
        {
            cout << "The numble you input is too small.��Do you want to exit����" << endl;
            input = EnglishGetInt();
        }
        if (input > 100)
        {
            cout << "The numble you input is too big.��Too many questions may make you boring .��" << endl;
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



int main()
{
	int i,n;
	string versionChoice;     //Chi�Ļ� ���� Eng Ӣ��
    cout<< "����ʹ��ʲô���ԣ�  /  Which language do you want to use? "<<endl; 
    cout<< "���������룺Chi  /  Chinese Please input : Chi "<<endl;
    cout<< "Ӣ�������룺Eng  /  English Please input : Eng "<<endl;
    versionChoice = LanguageChoice();

	if(versionChoice == "Chi")
        {
        	n = ChineseGetInt();
		}
	else if(versionChoice == "Eng")
		{
			n = EnglishGetInt();
		}

	string Expression;
	string str;

	for(i=1;i<=n;i++)
	{
	    str = expression();
		cout << "��" << i << "��:" << str << endl;
		cout << "���������Ĵ�" << endl;
	}
	return 0;
}
