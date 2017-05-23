#pragma once
#include<malloc.h>
#define MAXLINE 30 //资源文件内的最大行数
#define MAXLEN 200 //每行的最大字符数

//存储资源文件内容的指针数组
char *Resource[MAXLINE] = { (char *)malloc(MAXLEN * sizeof(char)) };