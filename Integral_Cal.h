#ifndef _INTEGRAL_CAL_H
#define _INTEGRAL_CAL_H

#include "define.h"

class Integral_Cal:public Calculator //积分计算器
{
private:
	double a,b,c,d;
public:
	Integral_Cal();
	void Clear();   //清屏
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案 
	double intergral(double(Integral_Cal::*p)(double),double a,double b);
	double fsin(double x);
	double fexp(double x);
	double flog(double x);
	void OnSin();
	void OnExp();
	void OnLog();
};

#endif
