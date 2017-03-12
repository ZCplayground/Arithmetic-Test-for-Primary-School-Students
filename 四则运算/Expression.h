#pragma once
/*******************************************
ÎÄ¼şÃû£º Expression.h
×÷Õß£ºZC   ÈÕÆÚ£º2017/02/15
ÃèÊö: ±í´ïÊ½Àà¡£ÀàÉùÃ÷¡¢Àà·½·¨²¿·Ö£¬Ëæ»úÉú³É²¿·Ö
*******************************************/
#include "stack.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>
using namespace std;

/*Ëæ»úÉú³ÉÔËËã·ûÏà¹Ø£¬¶ÔÓÚĞ¡Ñ§Éú£¬Òª¼õÉÙ³ı·¨³öÏÖµÄ¸ÅÂÊ*/
char *rand_Oper_List = "+-*/+-*+*/-+*-+/*-+-*-+*/-+*-*+-*/+-*+*+-*-+*-+/*/+-/*-++-*/-*+-+*";
const int operListLen = strlen(rand_Oper_List);

/*Ëæ»úÊı¡¢Ëæ»úÖÖ×ÓÏà¹Ø*/
static unsigned int long seed = (unsigned int)time(NULL);/*ÓÃÊ±¼ä¶¨Òå³õÊ¼ÖÖ×Ó*/
unsigned int RandomeSeed(void)/*Ã¿´ÎËæ»úºóÈÃÖÖ×Ó±ä³ÉÒ»¸öĞÂµÄ*/
{
	seed = seed * 11035152465 + 12345;
	return (unsigned int)(seed / 65536) % 32768;
}
/*½âÊÍÏÂÎªÊ²Ã´¡£Èç¹ûÖ»ÓĞÊ±¼ä×÷ÎªÖÖ×Ó£¬ÄÇÃ´Èç¹û³ÌĞòÔÚÒ»ÃëÖ®ÄÚÅÜÍê£¬»áµ¼ÖÂËùÓĞ¼ÆËãÌâ¶¼ÊÇÒ»ÑùµÄ*/

//ÔÚ±í´ïÊ½µÄ¼ÆËãÖµ²»·ûºÏÒªÇóÊ±£¬ÊÇFALSE
#define FALSE -9999

/*Expression£¬±í´ïÊ½Àà¡£ÀàÉùÃ÷²¿·Ö: Expression.h¡£*/
//#include "Expression.h"
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

	friend ostream & operator<<(ostream & os, const Expression &e);//ÖØÔØ<<ÔËËã·û
};

/*±í´ïÊ½Àà£¬Àà·½·¨²¿·Ö Expression.cpp*/

/*¹¹Ôìº¯Êı*/
Expression::Expression()
{
	expression = "";
	string reversePolishNotation = "";
	value = FALSE;
}

Expression::~Expression()
{

}
/*Ëæ»úÉú³ÉÒ»¸öÊı×Ö£¬·¶Î§0~10*/
int Expression::RandomNum()
{
	srand(RandomeSeed());
	int randNum;
	randNum = rand() % 11;
	return randNum;
}

/*Ëæ»úÉú³ÉÒ»¸ö²Ù×÷·û²¢·µ»Ø£¬·µ»ØÖµÀàĞÍchar*/
char Expression::RandomOperator()
{
	int randOperIndex;
	srand(RandomeSeed());
	randOperIndex = rand() % operListLen;
	return rand_Oper_List[randOperIndex];
}

/*°Ñ²Ù×÷·ûoperÁ¬½ÓÔÚexpressionºó*/
string & Expression::AddOperator(const char oper)
{
	expression += oper;
	return expression;
}

/*part£ºËæ»úÉú³ÉÒ»¸ö²Ù×÷Êı¡¢»òÒ»¸öĞÎÈç£¨a+b£©µÄ²¿·Ö£¬²¢·µ»Ø¡£·µ»ØÖµÊÇstringÀàĞÍ¡£*/
string Expression::RandomPart()
{
	int randChoice;/*Èç¹ûÎª0£¬partÎªÒ»¸öÊı£»Èç¹ûÎª1£¬partÎªĞÎÈç£¨a+b£©µÄÊ½×Ó*/
	srand(RandomeSeed());
	randChoice = rand() % 2;

	string part;

	if (randChoice == 0)
	{
		int randNum;
		randNum = RandomNum();
		if (randNum == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum + 48);/*ÕâÀïÓÃµÄÊÇstringÀà¹¹Ôìº¯Êı£ºstring(char c);*/
		}
	}

	else if (randChoice == 1)
	{
		int randNum1;
		randNum1 = RandomNum();

		part += "(";
		if (randNum1 == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum1 + 48);
		}

		char oper = RandomOperator();
		part += oper;

		int randNum2;
		randNum2 = RandomNum();

<<<<<<< HEAD:å››åˆ™è¿ç®—/Expression.h
		if (oper == '/') //Èç¹û³öÏÖÁË´¥·¢£¬ÒªÈ·±£µÚ¶ş¸öÊı²»Îª0
=======
		if (oper == '/') //å¦‚æœå‡ºç°äº†é™¤æ³•ï¼Œè¦ç¡®ä¿ç¬¬äºŒä¸ªæ•°ä¸ä¸º0
>>>>>>> be382e278b062a6728f9be658f1f7a9815af5ce8:Expression.h
		{
			while (randNum2 == 0)
				randNum2 = RandomNum();
		}

		if (randNum2 == 10)
		{
			part += "10";
		}
		else
		{
			part += (char)(randNum2 + 48);
		}

		part += ")";
	}

	return part;
}

/*²ÎÊıÊÇÒ»¸östringÀàĞÍ£¬´ú±íÒ»¸öpart£¬×÷ÓÃÊÇ½«Õâ¸öpartÁ¬½Óµ½Ë½ÓĞ³ÉÔ±expressionºóÃæ*/
string & Expression::AddPart(const string & part)
{
	expression += part;
	return expression;
}

/*²ÎÊıÊÇÒ»¸östringÀàĞÍ£¬´ú±íÒ»¸öpart£¬·µ»ØÖµÊÇÕâ¸öpartµÄ¼ÆËãÖµ*/
int Expression::PartValue(const string & part)
{
	int val = FALSE;
	char oper;
	int num1;
	int num2;

	//Òª·ÀÖ¹(7*1)+(5-6)*(9*8)/10+9
	if (part[0] == '(')//partÊÇĞÎÈç£¨a+b£©µÄ  µ«ÓĞ¿ÉÄÜ³öÏÖ(10+5) (5+10) (10+10)
	{
		if (part.length() == 7) //ĞÎÈç (10+10)
		{
			oper = part[3];
			num1 = num2 = 10;
		}
		else if (part.length() == 6) //ĞÎÈç (10+a)
		{
			if (part[1] == '1'&&part[2] == '0')//ĞÎÈç (10+a)
			{
				num1 = 10;
				oper = part[3];
				num2 = part[4] - '0';//AscllÂë×Ö·û×ª»»intÊıÖµ 
			}
			else //»ò(a+10)
			{
				num1 = part[1] - '0';
				oper = part[2];
				num2 = 10;
			}
		}
		else //ĞÎÈç (a+b)
		{
			oper = part[2];
			num1 = part[1] - '0';
			num2 = part[3] - '0';
		}

		switch (oper)
		{
		case'+':
			val = num1 + num2;
			break;
		case'-':
			val = num1 - num2;
			break;
		case'*':
			val = num1 * num2;
			break;
		case'/':
			//Èç¹û³öÏÖ³ı·¨£¬Á½ÖÖÇé¿öÒª·µ»ØFLASE¡£µÚÒ»¸ö£º³ıÊıÎª0£¬µÚ¶ş¸ö£º²»ÄÜÕû³ı
			if (num1%num2 != 0 || num2 == 0)
			{
				return FALSE;
			}
			else
			{
				val = num1 / num2;
			}
		default:
			break;
		}
	}

	else //partÊÇÒ»¸öÊı
	{
		if (part[0] == '1'&&part[1] == '0')
		{
			val = 10;
		}
		else
		{
			val = part[0] - '0';
		}
	}

	return val;
}

/*Ëæ»úÉú³ÉÒ»¸öÖĞ×º±í´ïÊ½*/
Expression Expression::CreateInfixExpression()
{
	srand(RandomeSeed());
	int rank;
	rank = rand() % 3 + 2; //rankÎª2~4£¬ÒâË¼ÊÇ³¤¶È¿É±äµÄÖĞ×ºÊ½×Ó

	int val1, val2;//val1´ú±íÇ°ÃæµÄ£¬val2´ú±íºóÃæµÄ£¬·ÀÖ¹³öÏÖÇ°Ãæ³ıÒÔºóÃæ²»Õû³ı

	string randPart = RandomPart();
	val1 = PartValue(randPart);
	while (val1 == FALSE)//·ÀÖ¹ÁË£¨7/5£©   
	{
		randPart = RandomPart();
		val1 = PartValue(randPart);
	}
	AddPart(randPart);

	int i;
	for (i = 0; i < rank; i++)
	{
		char oper;
		oper = RandomOperator();
		AddOperator(oper);

		randPart = RandomPart();
		val2 = PartValue(randPart);
		if (oper == '/')    //Èç¹û³öÏÖÁË³ıºÅ£¬ÄÇÒªÈ·±£³ıÊı²»ÎªÁã
		{
			while (val2 == 0 || val1%val2 != 0)
			{
				randPart = RandomPart();
				val2 = PartValue(randPart);
			}
		}
		else
		{
			while (val2 == FALSE)
			{
				randPart = RandomPart();
				val2 = PartValue(randPart);
			}
		}

		//À©Õ¹val1 = val2;
		if (oper == '/')//  Òª·ÀÖ¹£º 8/(7-3)/4
		{
			val1 = val1 / val2;
		}
		else if (oper == '*')
		{
			val1 = val1 * val2;
		}
		else
		{
			val1 = val2;
		}
		AddPart(randPart);
	}
	return *this;
}

<<<<<<< HEAD:å››åˆ™è¿ç®—/Expression.h
/*¸ù¾İÀà³ÉÔ±expressionµÄÖĞ×º±í´ïÊ½£¬Éú³ÉÆä¶ÔÓ¦µÄÄæ²¨À¼Ê½£¬·Åµ½³ÉÔ±reversePolishNotationÖĞ*/
=======
/*ä¿®æ”¹ç§æœ‰ç±»æˆå‘˜expressionï¼Œä¿®æ”¹æˆå…¶å¯¹åº”çš„é€†æ³¢å…°å¼*/
>>>>>>> be382e278b062a6728f9be658f1f7a9815af5ce8:Expression.h
Expression Expression::ReversePolishNotation()
{
	Stack s1, s2;

	int i;
	char ch;

	int size = expression.length();
	for (i = 0; i < size; i++)
	{
		switch (expression[i])
		{
		case'(':
			s1.push(expression[i]);
			break;
		case')':
			while (s1.top() != '(')
			{
				ch = s1.top();
				s1.pop();
				s2.push(ch);
			}
			ch = s1.top();
			s1.pop();
			break;

		case'+':
		case'-':
			for (ch = s1.top(); !s1.empty(); ch = s1.top())
			{
				if (ch == '(')
				{
					break;
				}
				else
				{
					ch = s1.top();
					s1.pop();
					s2.push(ch);
				}
			}
			s1.push(expression[i]);
			break;

		case'*':
		case'/':
			for (ch = s1.top(); !s1.empty() && ch != '+'&&ch != '-'; ch = s1.top())
			{
				if (ch == '(')
					break;
				else
				{
					ch = s1.top();
					s1.pop();
					s2.push(ch);
				}
			}
			s1.push(expression[i]);
			break;

		case'1':
			if (expression[i + 1] == '0')//ËµÃ÷ÊÇÊı×ÖÊ®;
			{
				//ÔÚstringÖĞ£¬ÓÃ'#'´ú±íÊıÖµ10¡£ÔÚ¼ÆËãº¯ÊıÖĞ£¬Óöµ½#¾ÍÓÃ10´øÈë¼ÆËã
				s2.push('#');
				i++;
				break;
			}
		default://ÆäËûÊı×Ö
			s2.push(expression[i]);
		}
	}
	while (!s1.empty())
	{
		ch = s1.top();
		s1.pop();
		s2.push(ch);
	}

	string temp;
	for (; !s2.empty(); )
	{
		ch = s2.top();
		s2.pop();
		temp += ch;
	}
	int j = temp.length() - 1;
	for (; j >= 0; j--)
	{
		reversePolishNotation += temp[j];
	}
	return *this;
}

/*¸ù¾İÄæ²¨À¼Ê½£¬Çó³ö±í´ïÊ½µÄÖµ£¬·Åµ½Ë½ÓĞ³ÉÔ±valueÖĞ¡£½á¹ûÈç¹ûÊÇÕûÊı£¬Ôò·µ»ØÕûÊı¡£Èç¹û²»ÊÇÕûÊı£¬·µ»ØFALSE¡£*/
int Expression::ExpressionValue()
{
	Stack s;
	int size = reversePolishNotation.length();

	int num1, num2;//ÒòÎªÓĞÓÃ#´ú±í10£¬¾ÍÏÈÓÃint´æ
	int i;

	for (i = 0; i < size; i++)
	{
		switch (reversePolishNotation[i])
		{
		case'+':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num1 + num2);
			break;

		case'-':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num2 - num1);
			break;

		case'*':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			s.push(num1 * num2);
			break;

		case'/':
			num1 = s.top();
			s.pop();
			num2 = s.top();
			s.pop();
			//Ö»ÓĞ×ö³ı·¨Ê±¿ÉÄÜ³öÏÖ´ğ°¸Îª·ÇÕûÊıµÄÇé¿ö
			if (num2%num1 == 0)
			{
				s.push(num2 / num1);
			}
			else
			{
				return FALSE;
			}
			break;

		case'#'://ÊıÖµ10
			s.push(10);
			break;

		default://ÆäËûÊıÖµ
			s.push(reversePolishNotation[i] - '0');
			break;
		}
	}
	value = s.top();
	return value;
}

/*ÖØÔØÊä³öÔËËã·û*/
ostream & operator<<(ostream & os, const Expression & e)
{
	os << e.expression;
	return os;
}
