#ifndef _H_CAL_H
#define _H_CAL_H

#include "H_�߾�������.h"

class H_Cal:public Calculator //ʮ�����Ƹ߾��ȼ�����
{
private:
	int Show_Digit;  //��ʾλ��
	stack<char>ss;  //ss������ż������
	stack<H_Bign>ns;  //ns��Ž�Ҫ�������
public:
	H_Cal();
	void Clear();   //����
	int Compare(char c);  //�Ƚ�ջ��������뽫Ҫ��ջ������������ȼ�
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //�����               
	H_Bign Calculate(H_Bign number1,H_Bign number2,char op);    //�������op��������
	void SetShowDigit();     //����С�������ʾλ��
};

#endif