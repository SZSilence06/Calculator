#ifndef _INTEGRAL_CAL_H
#define _INTEGRAL_CAL_H

#include "define.h"

class Integral_Cal:public Calculator //���ּ�����
{
private:
	double a,b,c,d;
public:
	Integral_Cal();
	void Clear();   //����
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //����� 
	double intergral(double(Integral_Cal::*p)(double),double a,double b);
	double fsin(double x);
	double fexp(double x);
	double flog(double x);
	void OnSin();
	void OnExp();
	void OnLog();
};

#endif
