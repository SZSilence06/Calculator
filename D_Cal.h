#ifndef _D_CAL_H
#define _D_CAL_H

#include "define.h"

class D_Cal:public Calculator //ʮ���Ƹ߾��ȼ�����
{
private:
	int Show_Digit;  //��ʾλ��
	stack<char>ss;  //ss������ż������
	stack<Bign>ns;  //ns��Ž�Ҫ�������
	int Compare(char c);  //�Ƚ�ջ��������뽫Ҫ��ջ������������ȼ�
	Bign Calculate(Bign number1,Bign number2,char op);    //�������op��������
public:
	D_Cal();
	void SetShowDigit();  //������ʾλ��
	void Clear();   //����	  
	virtual void MainMenu();     //���˵�  
	virtual int GetInput();      //�������벢����
	virtual void ShowAnswer();   //�����               
};

#endif