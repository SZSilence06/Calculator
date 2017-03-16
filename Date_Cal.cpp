#include "Date_Cal.h"
#include "exception.h"

Date::Date()
{
}

Date::Date(int stdday)
{
	int daynum[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	const int a=365*400+97;
	const int b=365*100+24;
	const int c=365*4+1;

	year=1;
	year+=stdday/a*400;
	stdday%=a;
	year+=stdday/b*100;
	stdday%=b;
	year+=stdday/c*4;
	stdday%=c;
	year+=stdday/365;
	stdday%=365;
	if(stdday==0){
		year--;
		if(IsLeapYear(year)) stdday+=366;
		else stdday+=365;
	}

	for(int i=0;i<12;i++){
		if(IsLeapYear(year)&&i==1){
			if(stdday<=29) break;
			stdday-=29;
			continue;
		}
		if(stdday<=daynum[i]) break;
		stdday-=daynum[i];
	}
	month=i+1;
	day=stdday;
}

int Date::StdDay()
{
	int stdday=0;
	int daynum[12]={31,28,31,30,31,30,31,31,30,31,30,31};

	if(year>0){
		for(int i=1;i<year;i++){
			if(IsLeapYear(i)) stdday+=366;
			else stdday+=365;
		}
	}
	for(int i=0;i<month-1;i++){
		if(IsLeapYear(year)&&i==1){
			stdday+=29;
			continue;
		}
		stdday+=daynum[i];
	}
	stdday+=day;
	return stdday;
}

bool Date::IsLeapYear(int y)
{	
	if(y%4) return false;
	if(y%100) return true;
	if(y%400) return false;
	return true;
}

istream& operator >>(istream &in,Date &date){
	int daynum[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int year,month,day;
	cout<<"请输入日期（格式为：年 月 日）："<<endl;
	in>>year>>month>>day;
	if(in.fail()){
		in.clear();
		in.ignore(1024,'\n');
		Input_Error e;
		throw e;
	}
	in.ignore(1024,'\n');
	bool leap=date.IsLeapYear(year);
	if(month<1||month>12||day<1){
		Math_Error e(5);
		throw e;
	}
	if(month==2&&leap){
		if(day>29){
			Math_Error e(5);
			throw e;
		}
	}
	else if(day>daynum[month-1]){
		Math_Error e(5);
		throw e;
	}
	date.year=year;date.month=month;date.day=day;	
	return in;
}

ostream& operator <<(ostream &out,Date date){
	cout<<date.year<<"年"<<date.month<<"月"<<date.day<<"日";
	return out;
}

int operator -(Date d1,Date d2){
	return abs(d1.StdDay()-d2.StdDay());
}

Date operator +(Date date,int a){
	Date d(date.StdDay()+a);
	return d;
}

Date operator -(Date date,int a){
	Date d(date.StdDay()-a);
	return d;
}

/******************************以下为日期计算器部分**********************************/

Date_Cal::Date_Cal()
{
}

void Date_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"*********************************日期计算器*************************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     "<<endl<<endl;
	while(n){
		try{
			cout<<"请选择功能:\n1.日期相减\n2.日期与数相加\n3.日期与数相减"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int Date_Cal::GetInput()
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
			Date d1,d2;
			cin>>d1>>d2;
			cout<<"两日期相差"<<d1-d2<<"天"<<endl;
			break;
			}
		case 2:
			{
			Date d1;
			int a;
			cin>>d1;
			cout<<"输入数"<<endl;
			cin>>a;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1024,'\n');
				Input_Error e;
				throw e;
			}
			cin.ignore(1024,'\n');
			cout<<a<<"天后为"<<d1+a<<endl;
			break;
			}
		case 3:
			{
			Date d1;
			int a;
			cin>>d1;
			cout<<"输入数"<<endl;
			cin>>a;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1024,'\n');
				Input_Error e;
				throw e;
			}
			cin.ignore(1024,'\n');
			cout<<a<<"天前为"<<d1-a<<endl;
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

void Date_Cal::ShowAnswer()
{
}

void Date_Cal::Clear()
{
	system("cls");
	cout<<"*********************************日期计算器*************************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     "<<endl<<endl;
}