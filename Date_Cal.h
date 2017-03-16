#ifndef _DATE_CAL_H
#define _DATE_CAL_H

#include "define.h"

class Date
{
public:
	int year;
	int day;
	int month;
public:
	Date();
	Date(int stdday);      //根据标准天数换算成日期
	int StdDay();          //根据日期换算成标准天数
	bool IsLeapYear(int y);        //判断y是否闰年
};

Date operator +(Date date,int a);
Date operator -(Date date,int a);
int operator -(Date d1,Date d2);

istream& operator >>(istream &in,Date &date);
ostream& operator <<(ostream &out,Date date);

/************************以下为日期计算器部分*****************************************/

class Date_Cal:public Calculator //日期计算器
{
public:
	Date_Cal();
	void Clear();   //清屏
	virtual void MainMenu();     //主菜单  
	virtual int GetInput();      //接受输入并处理
	virtual void ShowAnswer();   //输出答案               
};

#endif