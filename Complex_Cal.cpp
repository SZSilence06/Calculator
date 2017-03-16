#include "Complex_Cal.h"
#include "exception.h"

Complex::Complex()
{
	real=imag=0;
}

void Complex::SetCom(float r,float i)
{
	real=r;
	imag=i;
}

void Complex::Print()
{
	if(real==0){
		if(imag==0)cout<<real<<endl;
		else cout<<imag<<"i"<<endl;
	}
	else{
		if(imag<0)cout<<real<<imag<<"i"<<endl;
		else if(imag==0) cout<<real<<endl;
        else cout<<real<<"+"<<imag<<"i"<<endl;
	}
}

Complex Complex::ADD(Complex C1,Complex C2)
{
	real=C1.real+C2.real;
	imag=C1.imag+C2.imag;
	return *this;
}

Complex Complex::SUB(Complex C1,Complex C2)
{
	real=C1.real-C2.real;
	imag=C1.imag-C2.imag;
	return *this;
}
 
Complex Complex::MUL(Complex C1,Complex C2)
{
	real=C1.real*C2.real-C1.imag*C2.imag;
	imag=C1.real*C2.imag+C1.imag*C2.real;
	return *this;
}

Complex Complex::DIV(Complex C1,Complex C2)
{
	if(C2.real*C2.real+C2.imag*C2.imag==0){
		Math_Error e(1);
		throw e;
	}
	real=(C1.real*C2.real+C1.imag*C2.imag)/(C2.real*C2.real+C2.imag*C2.imag);
	imag=(C1.imag*C2.real-C1.real*C2.imag)/(C2.real*C2.real+C2.imag*C2.imag);
	return *this;
}

//*****************����Ϊ��������������**********************************

Complex_Cal::Complex_Cal()
{
}

void Complex_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************����������*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
	while(n){
		try{
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int Complex_Cal::GetInput()
{
	float rx,iy;
	char ch;
	strstream str(read,1000);
	char buf;
	
	cout<<"�����һ��������\nʵ�� �鲿\n";
	cin.getline(read,1000);
	if(strcmp(read,"r")==0||strcmp(read,"R")==0) return 0;
	if(strcmp(read,"l")==0||strcmp(read,"L")==0) {
		Clear();
		return 1;
	}

	str>>rx>>iy;
	if(str.fail()){
		str.clear();
		str>>buf;
		Input_Error e(buf);
		throw e;
	}
	str>>buf;
	if(buf){
		Input_Error e(buf);
		throw e;
	}
	C1.SetCom(rx,iy);
	cout << "�����������:" << endl;
	
	cin.getline(read,1000);
	Pretreat();
	if(strcmp(read,"r")==0||strcmp(read,"R")==0) return 0;
	if(strcmp(read,"l")==0||strcmp(read,"L")==0){
		Clear();
		return 1;
	}
	if(read[1]){
		Input_Error e(read[1]);
		throw e;
	}
	if(!(read[0]=='+'||read[0]=='-'||read[0]=='*'||read[0]=='/')){
		Input_Error e(read[0]);
		throw e;
	}
	
	ch=read[0];
	cout<<"����ڶ���������\nʵ�� �鲿\n";
	
	cin.getline(read,1000);
	if(strcmp(read,"r")==0||strcmp(read,"R")==0) return 0;
	if(strcmp(read,"l")==0||strcmp(read,"L")==0){
		Clear();
		return 1;
	}

	str.seekg(0,ios::beg);
	str.clear();
	str>>rx>>iy;
	if(str.fail()){
		str.clear();
		str>>buf;
		Input_Error e(buf);
		throw e;
	}
	str>>buf;
	if(buf){
		Input_Error e(buf);
		throw e;
	}
	C2.SetCom(rx,iy); 

	switch(ch){
	case '+': 
		cout<<"���:\n";
		C.ADD(C1,C2);
		break;
	case '-':
		cout<<"���:\n";
		C.SUB(C1,C2);
		break;
	case '*':
		cout<<"���:\n";
		C.MUL(C1,C2);
		break;
	case '/':
		cout<<"���:\n";
		C.DIV(C1,C2);
	}
	ShowAnswer();
	return 1;
}

void Complex_Cal::ShowAnswer()
{
	C.Print();
}

void Complex_Cal::Clear()
{
	system("cls");
	cout<<"*********************************����������*************************************"<<endl;
	cout<<"     R:�������˵�     L:����    "<<endl<<endl;
}
