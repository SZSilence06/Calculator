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
	Date(int stdday);      //���ݱ�׼�������������
	int StdDay();          //�������ڻ���ɱ�׼����
	bool IsLeapYear(int y);        //�ж�y�Ƿ�����
};

Date operator +(Date date,int a);
Date operator -(Date date,int a);
int operator -(Date d1,Date d2);

istream& operator >>(istream &in,Date &date);
ostream& operator <<(ostream &out,Date date);

/************************����Ϊ���ڼ���������*****************************************/

class Date_Cal:public Calculator //���ڼ�����
{
public:
	Date_Cal();
	void Clear();   //����
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //�����               
};

#endif