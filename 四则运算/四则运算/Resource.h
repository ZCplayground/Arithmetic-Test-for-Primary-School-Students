#pragma once
#include<malloc.h>
#define MAXLINE 30 //��Դ�ļ��ڵ��������
#define MAXLEN 200 //ÿ�е�����ַ���

//�洢��Դ�ļ����ݵ�ָ������
char *Resource[MAXLINE] = { (char *)malloc(MAXLEN * sizeof(char)) };