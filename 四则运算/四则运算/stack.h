#pragma once
#pragma once
/********************************
�ļ����� stack.h
���ߣ�ZC   ���ڣ�2017/02/15
����: ���ݽṹջ��stack���������෽��
*********************************/
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
