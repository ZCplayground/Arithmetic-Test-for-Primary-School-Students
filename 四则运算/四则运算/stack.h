#pragma once
#pragma once
/********************************
文件名： stack.h
作者：ZC   日期：2017/02/15
描述: 数据结构栈，stack类声明、类方法
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
