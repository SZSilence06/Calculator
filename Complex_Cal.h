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
	void Clear();   //����
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //�����      
};

#endif
