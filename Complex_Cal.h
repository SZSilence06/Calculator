#ifndef _COMPLEX_CAL_H
#define _COMPLEX_CAL_H

#include"define.h"

class Complex
{
public:
	Complex();
	void SetCom(float r,float i);
	void Print();
	Complex ADD(Complex C1,Complex C2);
	Complex SUB(Complex C1,Complex C2);
	Complex MUL(Complex C1,Complex C2);
	Complex DIV(Complex C1,Complex C2);
private:
	float real,imag;
};

class Complex_Cal:public Calculator
{
private:
	Complex C1,C2,C;
public:
	Complex_Cal();
	void Clear();   //清屏
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案      
};

#endif
