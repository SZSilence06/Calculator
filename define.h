#ifndef _DEFINE_H
#define _DEFINE_H

#include <string.h>
#include <iostream>
#include <stack>
#include <strstream>
using namespace std;

int CharToNum(char c);
char NumToChar(int a);
int Max(int a,int b);

class Bign  //�߾���������Bign
{
public:	
	static int Show_Digit;   //��ʾλ��
	int num[1000];    
	int length;   //�߾������ĳ��ȣ�λ����
	int sign;  //�������ű�ʾλ��sign=0��ʾ������1��ʾ����
	int digit; //С��λ
public:	
	Bign();    //Ĭ�ϵĹ��캯��
	Bign(int a);    //����Ϊ�����Ĺ��캯����������ת��Ϊ�߾����͵�
	Bign(char s[]);   //����Ϊ�ַ����Ĺ��캯���������硰-123.456���͵��ַ���ת��Ϊ�߾�����
	Bign operator -();   //ȡ��
	void Correct();    //�������õ�������������������ɾȥ�����0���������ȼ�С����λ�õ�
	static void SetShowDigit(int a);  //������ʾλ��
};

//�����Ǹ߾��������
Bign Abs(Bign a);
Bign operator +(Bign a,Bign b);
Bign operator -(Bign a,Bign b);
Bign operator *(Bign a,Bign b);
Bign operator /(Bign a,Bign b);
bool operator >(Bign a,Bign b);
bool operator ==(Bign a,Bign b);
bool operator >=(Bign a,Bign b);
ostream &operator <<(ostream &out,Bign a);

class Calculator    //����
{
protected:
	char read[1000];       //�������������ַ���
public:
	Calculator(); 
	void SetSkin();       //����Ƥ��
	void Run();          //��������
	void Pretreat();    //���������Ԥ����ȥ���ո񣬲�����д��ĸת��ΪСд
	virtual int GetInput();    //����������Ϣ������Ӧ����
	virtual void ShowAnswer();   //���ش�
	virtual void MainMenu();    //���˵�
	void ShowStudio();          //������
	int Exit();
};

#endif