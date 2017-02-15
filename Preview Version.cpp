#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>

using namespace std;

/*��������������أ�����Сѧ����Ҫ���ٳ������ֵĸ���*/
char *rand_Oper_List = "+-*/+-*+*/-+*-+/*-+-*-+*/-+*-*+-*/+-*+*+-*-+*-+/*/+-/*-++-*/-*+-+*";
const int operListLen = strlen(rand_Oper_List);

/*�����������������*/
static unsigned int long seed = (unsigned int)time(NULL);/*��ʱ�䶨���ʼ����*/
unsigned int RandomeSeed(void)/*ÿ������������ӱ��һ���µ�*/
{
    seed = seed * 11035152465 + 12345;
    return (unsigned int)(seed / 65536) % 32768;
}
/*������Ϊʲô�����ֻ��ʱ����Ϊ���ӣ���ô���������һ��֮�����꣬�ᵼ�����м����ⶼ��һ����*/

// stack.h
//#include "stack.h"
/*���ݽṹջ��stack������*/
class Stack
{
private:
    int *Data;
    int posi;
public:
    Stack();
    ~Stack();
    bool empty() const;
    int top() const;
    bool push(const int & item);
    bool pop();
    int size();
};

/*stack�෽��*/
Stack::Stack()
{
    Data = new int[50];
}

Stack::~Stack()
{
    delete[] Data;
}
bool Stack::empty()const
{
    return posi == 0;
}

int Stack::top()const
{
    if (empty())
    {
        return false;
    }
    else
    {
        return Data[posi - 1];
    }
}

bool Stack::push(const int & item)
{
    if (posi < 50)
    {
        Data[posi++] = item;
        return true;
    }
    else
    {
        return false;
    }
}

bool Stack::pop()
{
    if (posi > 0)
    {
        int temp;
        temp = Data[--posi];
        return true;
    }
    else
    {
        return false;
    }
}

int Stack::size()
{
    return posi;
}

//�ڱ��ʽ�ļ���ֵ������Ҫ��ʱ����FALSE
#define FALSE -9999

/*Expression�����ʽ�ࡣ����������: Expression.h��*/
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

    friend ostream & operator<<(ostream & os, const Expression &e);//����<<�����
};

/*���ʽ�࣬�෽������ Expression.cpp*/

/*���캯��*/
Expression::Expression()
{
    expression = "";
    string reversePolishNotation = "";
    value = FALSE;
}

Expression::~Expression()
{

}
/*�������һ�����֣���Χ0~10*/
int Expression::RandomNum()
{
    srand(RandomeSeed());
    int randNum;
    randNum = rand() % 11;
    return randNum;
}

/*�������һ�������������أ�����ֵΪchar����*/
char Expression::RandomOperator()
{
    int randOperIndex;
    srand(RandomeSeed());
    randOperIndex = rand() % operListLen;
    return rand_Oper_List[randOperIndex];
}

/*�Ѳ�����oper������expression��*/
string & Expression::AddOperator(const char oper)
{
    expression += oper;
    return expression;
}

/*part���������һ������������һ�����磨a+b���Ĳ��֣������ء�����ֵ��string���͡�*/
string Expression::RandomPart()
{
    int randChoice;/*���Ϊ0��partΪһ���������Ϊ1��partΪ���磨a+b����ʽ��*/
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
            part += (char)(randNum + 48);/*�����õ���string�๹�캯����string(char c);*/
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

        if (oper == '/') //��������˳�����Ҫȷ���ڶ�������Ϊ0
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

/*������һ��string���ͣ�����һ��part�������ǽ����part���ӵ�˽�г�Աexpression����*/
string & Expression::AddPart(const string & part)
{
    expression += part;
    return expression;
}

/*������һ��string���ͣ�����һ��part������ֵ�����part�ļ���ֵ*/
int Expression::PartValue(const string & part)
{
    int val = FALSE;
    char oper;
    int num1;
    int num2;

    //Ҫ��ֹ(7*1)+(5-6)*(9*8)/10+9
    if (part[0] == '(')//part�����磨a+b����  ���п��ܳ���(10+5) (5+10) (10+10)
    {
        if (part.length() == 7) //���� (10+10)
        {
            oper = part[3];
            num1 = num2 = 10;
        }
        else if (part.length() == 6) //���� (10+a)
        {
            if (part[1] == '1'&&part[2] == '0')//���� (10+a)
            {
                num1 = 10;
                oper = part[3];
                num2 = part[4] - '0';//Ascll���ַ�ת��int��ֵ 
            }
            else //��(a+10)
            {
                num1 = part[1] - '0';
                oper = part[2];
                num2 = 10;
            }
        }
        else //���� (a+b)
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
            //������ֳ������������Ҫ����FLASE����һ��������Ϊ0���ڶ�������������
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

    else //part��һ����
    {
        if (part[0] == '1'&&part[1]=='0')
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

/*�������һ����׺���ʽ*/
Expression Expression::CreateInfixExpression()
{
    srand(RandomeSeed());
    int rank;
    rank = rand() % 3 + 2; //rankΪ2~4����˼�ǳ��ȿɱ����׺ʽ��

    int val1, val2;//val1����ǰ��ģ�val2�������ģ���ֹ����ǰ����Ժ��治����

    string randPart = RandomPart();
    val1 = PartValue(randPart);
    while (val1 == FALSE)//��ֹ�ˣ�7/5��   
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
        if (oper == '/')    //��������˳��ţ���Ҫȷ��������Ϊ��
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

        //��չval1 = val2;
        if (oper == '/' )//  Ҫ��ֹ�� 8/(7-3)/4
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

/*������һ��string���ͣ�����һ����׺���ʽ������ֵ��string���ͣ������Ӧ���沨��ʽ*/
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
            if (expression[i + 1] == '0')//˵��������ʮ;
            {
                //��string�У���'#'������ֵ10���ڼ��㺯���У�����#����10�������
                s2.push('#');
                i++;
                break;
            }
        default://��������
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

/*�����沨��ʽ��������ʽ��ֵ�����������������򷵻������������������������FALSE��*/
int Expression::ExpressionValue()
{
    Stack s;
    int size = reversePolishNotation.length();

    int num1, num2;//��Ϊ����#����10��������int��
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
            //ֻ��������ʱ���ܳ��ִ�Ϊ�����������
            if (num2%num1 == 0)
            {
                s.push(num2 / num1);
            }
            else
            {
                return FALSE;
            }
            break;

        case'#'://��ֵ10
            s.push(10);
            break;

        default://������ֵ
            s.push(reversePolishNotation[i] - '0');
            break;
        }
    }
    value = s.top();
    return value;
}

 /*������������*/
ostream & operator<<(ostream & os, const Expression & e)
{
    os << e.expression;
    return os;
}


/*�����Ƿǳ�Ա����*/
/*���ڲ��Ժ���func1��func2��func3�����뺯��*/


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
    while (scanf_s("%d", &input) != 1)//����Ĳ���%d
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
    while (scanf_s("%d", &input) != 1)//����Ĳ���%d
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

/*����Ϊ��Ӣ�ĵ�����ָʾ*/ 
int ChineseInstruction(int val, int true_Numble)
{
	    cout << "\t��������Ĵ𰸣�";
	    int answer;
        cin >> answer;

        if (answer == val)
        {
            cout << "��ϲ�㣬�ش���ȷ��" << endl << endl;
            true_Numble++;
        }
        else
        {
            cout << "������ȷ����ȷ���ǣ�" << val << endl << endl;
        }
        return true_Numble;
}


int EnglishInstruction(int val, int true_Numble)
{
	    cout << "\tPlease input your answer ��";
	    int answer;
        cin >> answer;

        if (answer == val)
        {
            cout << "Congratulations on a ringht answer ��" << endl << endl;
            true_Numble++;
        }
        else
        {
            cout << "Wrong answer ! The right answer is ��" << val << endl << endl;
        }
        return true_Numble;
}

int main()
{
    int i;
    string versionChoice;//1�Ļ� ���� 2 Ӣ��
    cout<< "����ʹ��ʲô���ԣ�  /  Which language do you want to use? "<<endl; 
    cout<< "���������룺Chi  /  Chinese Please input : Chi "<<endl;
    cout<< "Ӣ�������룺Eng  /  English Please input : Eng "<<endl;
    versionChoice = LanguageChoice();

    int n;
    if(versionChoice == "Chi")
        {
        	n = ChineseGetInt();
		}
	else if(versionChoice == "Eng")
		{
			n = EnglishGetInt();
		}
    
    
    int val, true_Numble = 0, wrong_Numble;     //��ȷ���Լ���ȷ��Ŀ���� 
	double accuracy;     
    for (i = 1; i <= n; i++)
    {
       
    //    val=Question();      //׼���ڼ������Ҳ������Ӣ���л�����Ǻ�������ֵֻ��һ�������㡣 
    //    if(versionChoice=="Chi")
    //    {            
	//		ChineseInsruction(val);
	//	}

    //    else if(versionChoice=="Eng")
    //    {
    //    	EnglishInstruction(val);
	//	}
	    Expression expression;
        expression.CreateInfixExpression();
        expression.ReversePolishNotation();
        val = expression.ExpressionValue();

        while (val == FALSE)
        {
            Expression expression;

            expression.CreateInfixExpression();
            expression.ReversePolishNotation();
            val = expression.ExpressionValue();
        }
		//ȷ��������ִ�Ϊ����������Ŀ
        
        cout << "��" << i << "��:" << expression << endl;   //׼���ڼ������Ҳ������Ӣ���л�����Ǻ�������ֵֻ��һ�������㡣
        
        /*������Judge�Ĺ���*/
        if(versionChoice == "Chi")
        {
        	true_Numble = ChineseInstruction(val,true_Numble); 
		}
		else if(versionChoice == "Eng")
		{
			true_Numble = EnglishInstruction(val,true_Numble);
		}
		
        expression.~Expression();
    }
    wrong_Numble = n - true_Numble;
    accuracy = true_Numble/n;
    cout << "\n���ͳ�ƣ���������" << true_Numble << "�⣬������" << wrong_Numble << "�⣬��ȷ��:" << accuracy << endl;
    cout << "�ݰݣ�~" << endl;
    return 0;
}
