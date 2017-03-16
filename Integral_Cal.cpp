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
	cout<<"*********************************积分计算器*************************************"<<endl;
	cout<<"     R:返回主菜单     L:清屏    "<<endl<<endl;
	while(n){
		try{
			cout<<"请选择要积分的函数类型：\n1.正弦函数\n2.指数函数\n3.对数函数"<<endl;
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
	cout<<"*********************************积分计算器*************************************"<<endl;
	cout<<"     R:返回主菜单     L:清屏    "<<endl<<endl;
}

double Integral_Cal::intergral(double(Integral_Cal::*p)(double),double a,double b)
{   
	int i;
	const int n=200;
	double x,h,s;
	h=(b-a)/n;//将a到b区间分成200份；h是平均数值；
	x=a;
	s=0;
	for(i=1;i<n;i++)
	{
		x=x+h;
		s=s+(this->*p)(x)*h;//s=h.(f(a+h/2)+f(a+h+h/2)+...+f(a+n-1)h+h/2);函数f在(a,b)区间的定积分公式；
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
	cout<<"您选择的函数形式为Asin(Bx+C)+D"<<endl<<"请输入各参数（格式为:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"请输入积分区间（格式为:左区间 右区间）:"<<endl;
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
	cout<<"答案为："<<intergral(pfn,dLeft,dRight)<<endl;
}

void Integral_Cal::OnExp()
{
	double dLeft,dRight;
	char buf;
	double (Integral_Cal::*pfn)(double);
	cout<<"您选择的函数形式为AExp(Bx+C)+D"<<endl<<"请输入各参数（格式为:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"请输入积分区间（格式为:左区间 右区间）:"<<endl;
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
	cout<<"答案为："<<intergral(pfn,dLeft,dRight)<<endl;
}

void Integral_Cal::OnLog()
{
	double dLeft,dRight;
	char buf;
	double (Integral_Cal::*pfn)(double);
	cout<<"您选择的函数形式为ALn(Bx+C)+D"<<endl<<"请输入各参数（格式为:A B C D):"<<endl;
	cin>>a>>b>>c>>d;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		cin.ignore(1024,'\n');
		Input_Error e(buf);
		throw e;
	}
	cin.ignore(1024,'\n');
	cout<<"请输入积分区间（格式为:左区间 右区间）:"<<endl;
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
	cout<<"答案为："<<intergral(pfn,dLeft,dRight)<<endl;
}
