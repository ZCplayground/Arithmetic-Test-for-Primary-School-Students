#pragma once

#include<iostream>
#include<string>

using namespace std;
unsigned int RandomeSeed(void);/*每次随机后让种子变成一个新的*/

//在表达式的计算值不符合要求时，是FALSE
#define FALSE -9999

/*Expression，表达式类。类声明部分: Expression.h。*/
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

	friend ostream & operator<<(ostream & os, const Expression &e);//重载<<运算符
};
