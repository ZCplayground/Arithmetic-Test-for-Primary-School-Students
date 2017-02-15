/************************************

Author:HXP      Date:02/13
Description:    start development

*************************************/




#include<stdlib.h>
#include<time.h>
#include<string>
#include<iostream>

using namespace std;   /*生成0~10的随机数*/
int rand_num()
{
    srand((unsigned) time(NULL));
	int tempnum;	
	tempnum = rand()%11;
	return tempnum;
}


char rand_oper()    /*生成随机字符即运算符*/
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
string expression()    /*产生一个完整的运算式*/
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


/*中英文语言选择*/ 
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
		cout<<"您输入的语言类型暂时不支持，请重新输入  /  The language you choose is undesirable , please input again : "<<endl;
		LanguageChoice(); 
	}
	return choice;
}



/*下面为中英文的输入检测*/ 
int ChineseGetInt()
{
	int input;
    char ch;
    cout << "请输入一个范围在1~100之间的正整数，代表你想做的题目的数量（0代表退出）：";
    while (scanf("%d", &input) != 1)//输入的不是%d
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
    cout << "The numble of questions：Please input a numble between 1 and 100 : ";
    while (scanf("%d", &input) != 1)//输入的不是%d
    {
        cout << "Your input：";
        while ((ch = getchar()) != '\n')
            putchar(ch);//如果用户输入了字符串，就显示这个字符串，并且在显示“不符合要求”
        cout << " Your numble is undesirable.\n";
        cout << "Please input a positive numble between 1 and 100 （0 means exit）：";
    }
    while (input <= 0 || input > 100)
    {
        if (input < 0)
        {
            cout << "The numble you input is too small.（Do you want to exit？）" << endl;
            input = EnglishGetInt();
        }
        if (input > 100)
        {
            cout << "The numble you input is too big.（Too many questions may make you boring .）" << endl;
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
	string versionChoice;     //Chi的话 中文 Eng 英文
    cout<< "您想使用什么语言？  /  Which language do you want to use? "<<endl; 
    cout<< "中文请输入：Chi  /  Chinese Please input : Chi "<<endl;
    cout<< "英文请输入：Eng  /  English Please input : Eng "<<endl;
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
		cout << "第" << i << "题:" << str << endl;
		cout << "请输入您的答案" << endl;
	}
	return 0;
}
