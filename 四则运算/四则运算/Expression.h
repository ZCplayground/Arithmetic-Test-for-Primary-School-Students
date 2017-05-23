#pragma once

#include<iostream>
#include<string>

using namespace std;
unsigned int RandomeSeed(void);/*ÿ������������ӱ��һ���µ�*/

//�ڱ��ʽ�ļ���ֵ������Ҫ��ʱ����FALSE
#define FALSE -9999

/*Expression�����ʽ�ࡣ����������: Expression.h��*/
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

	friend ostream & operator<<(ostream & os, const Expression &e);//����<<�����
};
