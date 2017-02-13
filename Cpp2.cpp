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
	expression+=outoper;
	expression+=str1;
	return expression;
}


int main()
{
	string a;
	cout<<"您想使用什么语言？/What language do you want to use?"<<endl;
	cout<<"中文请输入：Chi/英文请输入：Eng"<<endl;
	cin>>a;
	string expression;
	int i,n;
	string str;
	cin>>n;
	for(i=0;i<n;i++)
	{
	    str= expression;
		cout<<"请输入您的答案"<<endl;
	}
	return 0;
}
