#include "Integral_Cal.h"
#include "exception.h"
#include <cmath>

Integral_Cal::Integral_Cal()
{
}

void Integral_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************���ּ�����*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
	while(n){
		try{
			cout<<"��ѡ��Ҫ���ֵĺ������ͣ�\n1.���Һ���\n2.ָ������\n3.��������"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int Integral_Cal::GetInput()
{
	int command;
 
	cin.getline(read,1000);
	Pretreat();
	if(strcmp(read,"r")==0) return 0;
	if(strcmp(read,"l")==0){
		Clear();
		return 1;
	}
	command=CharToNum(read[0]);

	if(!read[1]){
		switch(command){
		case 1:
			{
				OnSin();
				break;
			}
		case 2:
			{
				OnExp();
				break;
			}
		case 3:
			{
				OnLog();
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
    return 1;
}

void Integral_Cal::ShowAnswer()
{
}

void Integral_Cal::Clear()
{
	system("cls");
	cout<<"*********************************���ּ�����*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
}

double Integral_Cal::intergral(double(Integral_Cal::*p)(double),double a,double b)
{   
	int i;
	const int n=200;
	double x,h,s;
	h=(b-a)/n;//��a��b����ֳ�200�ݣ�h��ƽ����ֵ��
	x=a;
	s=0;
	for(i=1;i<n;i++)
	{
		x=x+h;
		s=s+(this->*p)(x)*h;//s=h.(f(a+h/2)+f(a+h+h/2)+...+f(a+n-1)h+h/2);����f��(a,b)����Ķ����ֹ�ʽ��
	}
	return (s);
}
 
double Integral_Cal::fsin(double x)
{
	return a*sin(b*x+c)+d;
}

double Integral_Cal::fexp(double x)
{
	return a*exp(b*x+c)+d;
}

double Integral_Cal::flog(double x)
{
	return a*log(b*x+c)+d;
}

void Integral_Cal::OnSin()
{
	double dLeft,dRight;
	char buf;
	double (Integral_Cal::*pfn)(double);
	cout<<"��ѡ��ĺ�����ʽΪAsin(Bx+C)+D"<<endl<<"���������������ʽΪ:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"������������䣨��ʽΪ:������ �����䣩:"<<endl;
	cin>>dLeft>>dRight;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	if(dLeft>=dRight){
		Math_Error e(3);
		throw e;
	}
	pfn=fsin;
	cout<<"��Ϊ��"<<intergral(pfn,dLeft,dRight)<<endl;
}

void Integral_Cal::OnExp()
{
	double dLeft,dRight;
	char buf;
	double (Integral_Cal::*pfn)(double);
	cout<<"��ѡ��ĺ�����ʽΪAExp(Bx+C)+D"<<endl<<"���������������ʽΪ:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"������������䣨��ʽΪ:������ �����䣩:"<<endl;
	cin>>dLeft>>dRight;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	if(dLeft>=dRight){
		Math_Error e(3);
		throw e;
	}
	pfn=fexp;
	cout<<"��Ϊ��"<<intergral(pfn,dLeft,dRight)<<endl;
}

void Integral_Cal::OnLog()
{
	double dLeft,dRight;
	char buf;
	double (Integral_Cal::*pfn)(double);
	cout<<"��ѡ��ĺ�����ʽΪALn(Bx+C)+D"<<endl<<"���������������ʽΪ:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"������������䣨��ʽΪ:������ �����䣩:"<<endl;
	cin>>dLeft>>dRight;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	if(dLeft>=dRight){
		Math_Error e(3);
		throw e;
	}
	if(dLeft<=0){
		Math_Error e(7);
		throw e;
	}
	pfn=flog;
	cout<<"��Ϊ��"<<intergral(pfn,dLeft,dRight)<<endl;
}
