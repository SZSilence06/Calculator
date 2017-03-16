#ifndef _STAT_CAL_H
#define _STAT_CAL_H

#include "define.h"

class Stat_Cal:public Calculator
{
private:
	double X,E,D,d;//X是随机变量，E是均值，D是方差，d是标准差，Cov是协方差
public:
	Stat_Cal();
	virtual void MainMenu();
	virtual int GetInput();
	virtual void ShowAnswer();
	void Clear();
};

#endif