#ifndef _D_CAL_H
#define _D_CAL_H

#include "define.h"

class D_Cal:public Calculator //十进制高精度计算器
{
private:
	int Show_Digit;  //显示位数
	stack<char>ss;  //ss存放括号及运算符
	stack<Bign>ns;  //ns存放将要运算的数
	int Compare(char c);  //比较栈顶运算符与将要入栈的运算符的优先级
	Bign Calculate(Bign number1,Bign number2,char op);    //按运算符op进行运算
public:
	D_Cal();
	void SetShowDigit();  //设置显示位数
	void Clear();   //清屏	  
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案               
};

#endif