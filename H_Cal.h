#ifndef _H_CAL_H
#define _H_CAL_H

#include "H_高精度运算.h"

class H_Cal:public Calculator //十六进制高精度计算器
{
private:
	int Show_Digit;  //显示位数
	stack<char>ss;  //ss存放括号及运算符
	stack<H_Bign>ns;  //ns存放将要运算的数
public:
	H_Cal();
	void Clear();   //清屏
	int Compare(char c);  //比较栈顶运算符与将要入栈的运算符的优先级
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案               
	H_Bign Calculate(H_Bign number1,H_Bign number2,char op);    //按运算符op进行运算
	void SetShowDigit();     //设置小数点后显示位数
};

#endif