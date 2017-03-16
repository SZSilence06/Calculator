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
	PlaySound (TEXT ("wavmusic\\Windows XP ����.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	for(int i=1;i<=29;i++){
		Sleep(50);
		cout<<'*';
	}
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"ӭ";
	Sleep(50);
	cout<<"ʹ";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
	Sleep(50);
	cout<<"��";
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
			cout<<"******************************��ѡ�����¹���************************************"<<endl<<endl;
			cout<<"1.ʮ���Ƹ߾��ȼ�����\n2.ʮ�����Ƹ߾��ȼ�����\n3.����������\n4.ͳ�Ƽ�����\n5.���������\n"; 
			cout<<"6.���ڼ�����\n7.���ּ�����\n8.����Ƥ��\n9.������\n0.�˳�"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
			system("pause");
		}
	}
}

void Calculator::Pretreat()    //���������Ԥ����ȥ���ո񣬲�����д��ĸת��ΪСд
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
	char s1[]="������",s2[]="�鳤��������",s3[]="��Ա�����鵤",s[][10]={"������","����","�ż�֦","Ҷ����"};
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
	cout<<"��ѡ��"<<endl<<"1.Ĭ��   2.�����   3.��Ҷ��    4.��֮��"<<endl;
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
	cout<<"�����������������������������������������";
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                 ллʹ�ã�";
	cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"�����������������������������������������"<<endl;
	Sleep(1000);
	return 0;
}