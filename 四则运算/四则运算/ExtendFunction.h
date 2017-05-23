#pragma once

class Expression;

/*展示目前支持的语言列表*/
void ShowLanguageList();

/*检测用户输入的语言是否支持。如果支持，返回true。不支持返回false*/
bool CheckLanguageSupport(char * users_Lang);

/*根据正确的语言文档路径，取得其中的内容以便使用。存放到全局指针数组Resource中*/
void GetResource(char * filepath);


/*对题目数量n的输入检测*/
int GetInt();

/*对于输入题目的答案answer的输入检测*/
int GetAnswer();

/*返回值是一个表达式类，里面的内容是题目*/
Expression CreateProblems();

/*答案判定*/
bool Judge(int answer, Expression & e);

/*两个scan函数，用于与使用标准输入的用户交互取得数据*/
int ScanLanguage(char * language);//两个scan函数用于与用户交互并获取输入信息

int ScanNumofProblems();

/*输出统计结果给用户，输出到标准输出*/
void Print(int n, int numRight, int numWrong);

/*从文件中读取一个整型数字返回*/
int ReadFile(char *filename);//filename是绝对路径


/*将最终结果写入文件，内容包括：用户输入的题目数，每个生成的表达式、正确答案、用户输入的答案，
保存到命令行中第二个参数指定的路径。(请注意参数设置)*/

/*写入表达式、用户输入答案、正确答案*/
void WriteExpression(char *filename, Expression expression, int useranswer, int rightanswer, int i);


/*写入最终结果*/
void WriteResult(char *filename, int n, int numRight, int numWrong);