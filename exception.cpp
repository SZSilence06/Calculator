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
		cout<<"输入的命令非法!"<<endl;
		return;
	}
	cout<<"输入格式不正确。非法字符："<<ErrorChar<<endl;
}

Expression_Error::Expression_Error()
{
}

void Expression_Error::OnError()
{
	cout<<"表达式非法！"<<endl;
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
	cout<<"数学错误：";
	switch(ErrorID){
	case 1:cout<<"除数为0!"<<endl;break;
	case 2:cout<<"输入的概率之和不为1!"<<endl;break;
	case 3:cout<<"左区间大于等于右区间!"<<endl;break;
	case 4:cout<<"概率为负或大于1!"<<endl;break;
	case 5:cout<<"输入的日期非法!"<<endl;break;
	case 6:cout<<"输入的矩阵无法如此运算!"<<endl;break;
	case 7:cout<<"积分区间不在定义域内!"<<endl;break;
	}
}