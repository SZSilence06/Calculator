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
	cout<<"*********************************统计计算器*************************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     "<<endl<<endl;
	while(n){
		try{
			cout<<"Please insert number:\n1.不带权离散型样本\n2.带权离散型样本\n3.离散型随机变量\n4.均匀分布\n5.指数分布\n6.正态分布\n"<<endl;
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
	X=0;//X是随机变量，E是均值，D是方差，d是标准差，Cov是协方差
	int k;//k=1表示算数平均值，k=2表示加权平均值，k=3表示数学期望，k=4表示均匀分布，k=5表示指数分布，k=6表示正态分布
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
		int t=0;//t累计变量的个数
		double E1,X1=0,X2=0;//X1和X2分别用来计算X和X^2的均值,E1表示X^2的均值
		printf("请输入数据。输入任意非数字字符来结束输入:\n");
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
		double P,t=0;//P表示每一个变量的权重,t表示权的累加
        double E1=0,X1=0,X2=0;//X1和X2分别用来计算X和X^2的均值,E1表示X^2的均值
        printf("输入两个数，分别为数值和权值。输入任意非数值字符来结束输入\n数值  权值\n");
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
        cout<<"请输入所有可能值及其概率。输入任意非数值字符来终止输入:\n";
		cout<<"可能值  概率"<<endl;
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
		cout<<"请输入参数:\n";
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
		cout<<"请输入参数:\n";
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
		cout<<"请输入参数:\n";
		cout<<"均值  方差"<<endl;
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
	cout<<"*********************************统计计算器*************************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     "<<endl<<endl;
}
