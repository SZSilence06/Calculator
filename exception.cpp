#include <iostream>
#include "exception.h"
using namespace std;

void Error::OnError()
{
}

Input_Error::Input_Error()
{
	ErrorChar=' ';
}

Input_Error::Input_Error(char c)
{
	ErrorChar=c;
}

void Input_Error::OnError()
{
	if(ErrorChar==' '){
		cout<<"���������Ƿ�!"<<endl;
		return;
	}
	cout<<"�����ʽ����ȷ���Ƿ��ַ���"<<ErrorChar<<endl;
}

Expression_Error::Expression_Error()
{
}

void Expression_Error::OnError()
{
	cout<<"���ʽ�Ƿ���"<<endl;
}

Math_Error::Math_Error()
{
}

Math_Error::Math_Error(int a)
{
	ErrorID=a;
}

void Math_Error::OnError()
{
	cout<<"��ѧ����";
	switch(ErrorID){
	case 1:cout<<"����Ϊ0!"<<endl;break;
	case 2:cout<<"����ĸ���֮�Ͳ�Ϊ1!"<<endl;break;
	case 3:cout<<"��������ڵ���������!"<<endl;break;
	case 4:cout<<"����Ϊ�������1!"<<endl;break;
	case 5:cout<<"��������ڷǷ�!"<<endl;break;
	case 6:cout<<"����ľ����޷��������!"<<endl;break;
	case 7:cout<<"�������䲻�ڶ�������!"<<endl;break;
	}
}