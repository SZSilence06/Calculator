#ifndef _STAT_CAL_H
#define _STAT_CAL_H

#include "define.h"

class Stat_Cal:public Calculator
{
private:
	double X,E,D,d;//X�����������E�Ǿ�ֵ��D�Ƿ��d�Ǳ�׼�Cov��Э����
public:
	Stat_Cal();
	virtual void MainMenu();
	virtual int GetInput();
	virtual void ShowAnswer();
	void Clear();
};

#endif