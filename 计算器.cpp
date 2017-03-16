#include "define.h"
#include "exception.h"
#include "D_Cal.h"
#include "H_Cal.h"
#include "Complex_Cal.h"
#include "Stat_Cal.h"
#include "Matrix_Cal.h"
#include "Date_Cal.h"
#include "Integral_Cal.h"
#include <windows.h>
#include <mmsystem.h> 
#pragma comment(lib, "WINMM.LIB")

Calculator::Calculator(){}

void Calculator::Run()
{
	PlaySound (TEXT ("wavmusic\\Windows XP 启动.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	for(int i=1;i<=29;i++){
		Sleep(50);
		cout<<'*';
	}
	Sleep(50);
	cout<<"欢";
	Sleep(50);
	cout<<"迎";
	Sleep(50);
	cout<<"使";
	Sleep(50);
	cout<<"用";
	Sleep(50);
	cout<<"多";
	Sleep(50);
	cout<<"功";
	Sleep(50);
	cout<<"能";
	Sleep(50);
	cout<<"计";
	Sleep(50);
	cout<<"算";
	Sleep(50);
	cout<<"器";
	Sleep(50);
	cout<<"!";
	for(i=1;i<=30;i++){
		Sleep(50);
		cout<<'*';
	}
	Sleep(1000);
	MainMenu();
}

void Calculator::MainMenu()
{
	int n=1;
	while(n){
		try{
			system("cls");
			cout<<"******************************请选择以下功能************************************"<<endl<<endl;
			cout<<"1.十进制高精度计算器\n2.十六进制高精度计算器\n3.复数计算器\n4.统计计算器\n5.矩阵计算器\n"; 
			cout<<"6.日期计算器\n7.积分计算器\n8.更换皮肤\n9.制作组\n0.退出"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
			system("pause");
		}
	}
}

void Calculator::Pretreat()    //对输入进行预处理，去除空格，并将大写字母转换为小写
{
	char c[1000];
	for(int i=0,j=0;read[i];i++){
		if(read[i]==' ') continue;
		if(read[i]>='A'&&read[i]<='Z') c[j++]=read[i]+32;
		else c[j++]=read[i];
	}
	c[j]='\0';
	strcpy(read,c);
}

void Calculator::ShowAnswer()
{
}

int Calculator::GetInput()
{
	int command;
	cin.getline(read,1000);
	Pretreat();
	command=CharToNum(read[0]);
	if(!read[1]){
		switch(command){
		case 1:
			{
			D_Cal d_cal;
			d_cal.MainMenu();
			break;
			}
		case 2:
			{
			H_Cal h_cal;
			h_cal.MainMenu();
			break;
			}
		case 3:
			{
			Complex_Cal complex_cal;
			complex_cal.MainMenu();
			break;
			}
		case 4:
			{
			Stat_Cal stat_cal;
			stat_cal.MainMenu();
			break;
			}
		case 5:
			{
			Matrix_Cal matrix_cal;
			matrix_cal.MainMenu();
			break;
			}
		case 6:
			{
			Date_Cal date_cal;
			date_cal.MainMenu();
			break;
			}
		case 7:
			{
			Integral_Cal integral_cal;
			integral_cal.MainMenu();
			break;
			}
		case 8:SetSkin();break;
		case 9:ShowStudio();break;
		case 0:return Exit();
		default:
			Input_Error e;
			throw e;
		}
	}
	else{
		Input_Error e;
		throw e;
	}
	return 1;
}

void Calculator::ShowStudio()
{
	system("cls");
	char s1[]="制作组",s2[]="组长：王恺怿",s3[]="组员：梁议丹",s[][10]={"许婷婷","刘兵","张继枝","叶新宇"};
	int i;
	for(i=0;i<=35;i++){
		Sleep(50);
		cout<<'*';
	}
	for(i=0;s1[i];i++){
		Sleep(50);
		cout<<s1[i];
	}
	for(i=0;i<=37;i++){
		Sleep(50);
		cout<<'*';
	}
	cout<<endl<<endl<<endl;
	cout<<"                              ";
	for(i=0;s2[i];i++){
		Sleep(150);
		cout<<s2[i];
	}
	cout<<endl<<endl;
	cout<<"                              ";
	for(i=0;s3[i];i++){
		Sleep(150);
		cout<<s3[i];
	}
	for(i=0;i<4;i++){
		cout<<endl<<endl;
		cout<<"                                    ";
		for(int j=0;s[i][j];j++){
			Sleep(150);
			cout<<s[i][j];
		}
	}
	Sleep(1000);
	cout<<endl<<endl<<endl;
	system("pause");
}

void Calculator::SetSkin()
{
	int command;
	cout<<"请选择："<<endl<<"1.默认   2.日落黄   3.枫叶红    4.海之蓝"<<endl;
	cin.getline(read,1000);
	Pretreat();
	command=CharToNum(read[0]);
	if(!read[1]){
		switch(command){
		case 1:
			{
				system("color 07");
				break;
			}
		case 2:
			{
				system("color 0E");
				break;
			}
		case 3:
			{
				system("color 4A");
				break;
			}
		case 4:
			{
				system("color 17");
				break;
			}
		default:
			Input_Error e;
			throw e;
		}
	}
	else{
		Input_Error e;
		throw e;
	}
}

int Calculator::Exit()
{
	system("cls");
	cout<<endl<<endl<<endl<<endl;
	cout<<"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★★★★★★★★★★★★★★★★★★★★★★";
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                 谢谢使用！";
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"★★★★★★★★★★★★★★★★★★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆"<<endl;
	Sleep(1000);
	return 0;
}