#include "Stat_Cal.h"
#include "exception.h"
#include <math.h>

Stat_Cal::Stat_Cal()
{
}

void Stat_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************ͳ�Ƽ�����*************************************"<<endl;
	cout<<"    R:�������˵�     L:����     "<<endl<<endl;
	while(n){
		try{
			cout<<"Please insert number:\n1.����Ȩ��ɢ������\n2.��Ȩ��ɢ������\n3.��ɢ���������\n4.���ȷֲ�\n5.ָ���ֲ�\n6.��̬�ֲ�\n"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int Stat_Cal::GetInput()
{
	char buf[1000];
	X=0;//X�����������E�Ǿ�ֵ��D�Ƿ��d�Ǳ�׼�Cov��Э����
	int k;//k=1��ʾ����ƽ��ֵ��k=2��ʾ��Ȩƽ��ֵ��k=3��ʾ��ѧ������k=4��ʾ���ȷֲ���k=5��ʾָ���ֲ���k=6��ʾ��̬�ֲ�
	cin>>k;
	if(cin.fail()){
		cin.clear();
		cin>>buf;
		if(strcmp(buf,"r")==0||strcmp(buf,"R")==0) {
			cin.ignore(1024,'\n');
			return 0;
		}
		if(strcmp(buf,"l")==0||strcmp(buf,"L")==0) {
			Clear();
			cin.ignore(1024,'\n');
			return 1;
		}
		cin.ignore(1024,'\n');
		Input_Error e(buf[0]);
		throw e;
	}
	cin.ignore(1024,'\n');
	if(k==1){
		int t=0;//t�ۼƱ����ĸ���
		double E1,X1=0,X2=0;//X1��X2�ֱ���������X��X^2�ľ�ֵ,E1��ʾX^2�ľ�ֵ
		printf("���������ݡ���������������ַ�����������:\n");
		for(int i=1;;i++){
			cin>>X1;
			if(cin.fail()) break;
			X2=X2+X1*X1;
			X=X+X1;
            t=i;
		}
		cin.clear();
		cin.ignore(1024,'\n');
		if(t==0){
			Input_Error e;
			throw e;
		}
		E=X/t;
		E1=X2/t;
		D=E1-E*E;
		d=sqrt(D);
		ShowAnswer();
	}
	if(k==2){
		double P,t=0;//P��ʾÿһ��������Ȩ��,t��ʾȨ���ۼ�
        double E1=0,X1=0,X2=0;//X1��X2�ֱ���������X��X^2�ľ�ֵ,E1��ʾX^2�ľ�ֵ
        printf("�������������ֱ�Ϊ��ֵ��Ȩֵ�������������ֵ�ַ�����������\n��ֵ  Ȩֵ\n");
		for(int i;;i++){
			cin>>X1;
			if(cin.fail()) break;
			cin>>P;	
			if(cin.fail()){
				cin.clear();
				cin.ignore(1024,'\n');
				Input_Error e;
				throw e;
			}
			X=X+X1*P;
			X2=X2+X1*X1*P;
            t=t+P;
		}
		cin.clear();
		cin.ignore(1024,'\n');
		if(t==0){
			Input_Error e;
			throw e;
		}
	    E=X/t;
		E1=X2/t;
		D=E1-E*E;
		d=sqrt(D);
		ShowAnswer();
	}
	if(k==3){
		double p=0,p1=0,E1=0;
        cout<<"���������п���ֵ������ʡ������������ֵ�ַ�����ֹ����:\n";
		cout<<"����ֵ  ����"<<endl;
		for(int i;;i++){
			cin>>X;
			if(cin.fail()) break;
			cin>>p;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1024,'\n');
				Input_Error e;
				throw e;
			}
			if(p<0||p>1){
				Math_Error e(4);
				throw e;
			}
			p1=p+p1;
			E=E+X*p;
			E1=E1+X*X*p;
			D=E1-E*E;
			d=sqrt(D);
		}
		cin.clear();
		cin.ignore(1024,'\n');
		if(p1==0){
			Input_Error e;
			throw e;
		}
		if(p1>1){
			Math_Error e(2);
			throw e;
		}
        else ShowAnswer();
	}
	if(k==4){
		cout<<"���������:\n";
		cout<<"a  b"<<endl;
		double a,b;
		cin>>a>>b;
		if(cin.fail()){
			cin.clear();
			cin.ignore(1024,'\n');
			Input_Error e;
			throw e;
		}
		if(a>=b){
			Math_Error e(3);
			throw e;
		}
		cin.ignore(1024,'\n');
		E=(a+b)/2;
		D=(b-a)*(b-a)/12;
		d=sqrt(D);
        ShowAnswer();
	}
	if(k==5){
		double a;
		cout<<"���������:\n";
		cout<<"theta"<<endl;
		cin>>a;
		if(cin.fail()){
			cin.clear();
			cin.ignore(1024,'\n');
			Input_Error e;
			throw e;
		}
		cin.ignore(1024,'\n');
		E=a;
		D=a*a;
		d=a;
        ShowAnswer();
	}
	if(k==6){
		double a,b;
		cout<<"���������:\n";
		cout<<"��ֵ  ����"<<endl;
		cin>>a>>b;
		if(cin.fail()){
			cin.clear();
			cin.ignore(1024,'\n');
			Input_Error e;
			throw e;
		}
		cin.ignore(1024,'\n');
		E=a;
		D=b;
		d=sqrt(D);
        ShowAnswer();
	}
	return 1;
}

void Stat_Cal::ShowAnswer()
{
	cout<<"E="<<E<<" D="<<D<<" d="<<d<<endl;
}

void Stat_Cal::Clear()
{
	system("cls");
	cout<<"*********************************ͳ�Ƽ�����*************************************"<<endl;
	cout<<"    R:�������˵�     L:����     "<<endl<<endl;
}
