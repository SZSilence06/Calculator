#ifndef _DEFINE_H
#define _DEFINE_H

#include <string.h>
#include <iostream>
#include <stack>
#include <strstream>
using namespace std;

int CharToNum(char c);
char NumToChar(int a);
int Max(int a,int b);

class Bign  //高精度运算类Bign
{
public:	
	static int Show_Digit;   //显示位数
	int num[1000];    
	int length;   //高精度数的长度（位数）
	int sign;  //正负符号表示位。sign=0表示正数，1表示负数
	int digit; //小数位
public:	
	Bign();    //默认的构造函数
	Bign(int a);    //参数为整数的构造函数，将整数转换为高精度型的
	Bign(char s[]);   //参数为字符串的构造函数，将形如“-123.456”型的字符串转换为高精度数
	Bign operator -();   //取负
	void Correct();    //对运算后得到的数进行修正，包括删去多余的0、修正长度及小数点位置等
	static void SetShowDigit(int a);  //设置显示位数
};

//以下是高精度运算符
Bign Abs(Bign a);
Bign operator +(Bign a,Bign b);
Bign operator -(Bign a,Bign b);
Bign operator *(Bign a,Bign b);
Bign operator /(Bign a,Bign b);
bool operator >(Bign a,Bign b);
bool operator ==(Bign a,Bign b);
bool operator >=(Bign a,Bign b);
ostream &operator <<(ostream &out,Bign a);

class Calculator    //主类
{
protected:
	char read[1000];       //用来存放输入的字符串
public:
	Calculator(); 
	void SetSkin();       //更换皮肤
	void Run();          //启动运行
	void Pretreat();    //对输入进行预处理，去除空格，并将大写字母转换为小写
	virtual int GetInput();    //接受输入信息并作相应处理
	virtual void ShowAnswer();   //返回答案
	virtual void MainMenu();    //主菜单
	void ShowStudio();          //制作组
	int Exit();
};

#endif