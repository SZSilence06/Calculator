#include "H_Cal.h"
#include "exception.h"

H_Cal::H_Cal()
{
	Show_Digit=20;
}

int H_Cal::Compare(char c)   //将运算符c与ss栈顶的运算符比较优先级。1：栈顶高；0：括号；-1：栈顶低
{
	if(ss.empty()){
		Expression_Error e;
		throw e;
	}
	char a=ss.top();
	int n1,n2,cmp[6][6]={{1,1,-1,-1,-1,1},{1,1,-1,-1,-1,1},{1,1,1,1,-1,1},{1,1,1,1,-1,1},{-1,-1,-1,-1,-1,0},{1,1,1,1,0,1}};
	switch(a){
	case '+':n1=0;break;
	case '-':n1=1;break;
	case '*':n1=2;break;
	case '/':n1=3;break;
	case '(':n1=4;break;
	case ')':n1=5;break;
	}
	switch(c){
	case '+':n2=0;break;
	case '-':n2=1;break;
	case '*':n2=2;break;
	case '/':n2=3;break;
	case '(':n2=4;break;
	case ')':n2=5;break;
	}
	return cmp[n1][n2];
}

void H_Cal::MainMenu()
{
	int n=1;
	system("cls");
	cout<<"****************************十六进制高精度计算器********************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     S:设置小数点后显示位数"<<endl<<endl;
	while(n){
		try{
			cout<<"请输入表达式（仅支持+、-、*、/、括号）:"<<endl;
			n=GetInput();
		}
		catch(Error &e){
			e.OnError();
		}	
	}
}

int H_Cal::GetInput()
{
	char number[1000];
	int sign=0;
	cin.getline(read,1000);
	Pretreat();
	while(!ns.empty()) ns.pop();
	while(!ss.empty()) ss.pop();
	if(strcmp(read,"r")==0) return 0;
	if(strcmp(read,"l")==0){
		Clear();
		return 1;
	}
	if(strcmp(read,"s")==0){
		SetShowDigit();
		return 1;
	}
	ss.push('(');    //先将左括号入栈
	for(int i=0,j=0;read[i];i++);
	read[i]=')';read[i+1]='\0';   //在输入末尾加上一个右括号，以闭合栈底的左括号
	for(i=0,j=0;read[i];i++)
	{
		if(read[i]>='0'&&read[i]<='9') 
		{
			number[j++]=read[i];
		}
		else if(read[i]>='a'&&read[i]<='f') number[j++]=read[i];
		else if(read[i]=='.') number[j++]=read[i];
		else if(read[i]=='+'||read[i]=='-'||read[i]=='*'
			||read[i]=='/'||read[i]=='('||read[i]==')')
		{
			if(i>0){
				if((read[i]=='('&&((read[i-1]>='0'&&read[i-1]<='9')||(read[i-1]>='a'&&read[i-1]<='f')))||
					(read[i]==')'&&((read[i+1]>='0'&&read[i+1]<='9')||(read[i+1]>='a'&&read[i+1]<='f'))))
				{
					Expression_Error e;
					throw e;
				}
			}
			number[j]='\0';
			H_Bign numb(number);
			if(read[i]=='-'&&((i>0&&read[i-1]=='(')||i==0)){    //判断'-'是负号而不是减号
				sign=1;
				continue;
			}
			numb.sign=sign;
			sign=0;
			if(j>0) ns.push(numb);	  //数据入ns栈
			j=0;
			switch(Compare(read[i])){    //将读取的运算符与栈顶的运算符比较优先级
			case -1:ss.push(read[i]);break;    //栈顶运算符优先级低，直接入栈
			case 0: ss.pop();break;            //闭合括号            
			case 1:                            //栈顶运算符优先级高，出栈并运算
				while(Compare(read[i])==1)
				{
					char op;
					H_Bign number1,number2;
					if(ss.empty()){
						Expression_Error e;
						throw e;
					}
				    op=ss.top();
					ss.pop();
					if(ns.empty()){
						Expression_Error e;
						throw e;
					}
					number2=ns.top();
					ns.pop();
					if(ns.empty()){
						Expression_Error e;
						throw e;
					}
					number1=ns.top();
					ns.pop();						   
					ns.push(Calculate(number1,number2,op));
				}
				if(Compare(read[i])==0) ss.pop();   //闭合括号
				else ss.push(read[i]);              //到这里表示栈顶运算符优先级低了，所以直接入栈
			}
		}
		else{
			Input_Error e(read[i]);
			throw e;
		}
	}
	if(!ss.empty()){
		Expression_Error e;
		throw e;
	}
	ShowAnswer();
	return 1;
}


H_Bign H_Cal::Calculate(H_Bign number1,H_Bign number2,char op)
{
	switch(op){
	case'+':return number1+number2;
	case'-':return number1-number2;
	case'*':return number1*number2;
	case'/':return number1/number2;
	default:Input_Error e(op);
		throw e;
	}
}

void H_Cal::ShowAnswer()
{
	if(ns.empty()){
		Expression_Error e;
		throw e;
	}
	if(ns.size()>1){
		Expression_Error e;
		throw e;
	}
	H_Bign number=ns.top();
	cout<<endl<<number<<endl<<endl;
}

void H_Cal::Clear()
{
	system("cls");
	cout<<"****************************十六进制高精度计算器********************************"<<endl;
	cout<<"    R:返回主菜单     L:清屏     S:设置小数点后显示位数"<<endl<<endl;
}

void H_Cal::SetShowDigit()
{
	int a,n=1;
	while(n){
		cout<<"当前小数点后显示位数："<<Show_Digit<<endl;
		cout<<"请输入小数点后显示位数(0-500):";
		try{
			cin>>a;
			if(cin.fail()){
				cin.clear();
				cin.ignore(1024,'\n');
				Input_Error e;
				throw e;
			}
			if(a>500||a<0){
				Input_Error e;
				throw e;
			}
			n=0;
			Show_Digit=a;
			cin.ignore(1024,'\n');
			H_Bign::SetShowDigit(Show_Digit);
		}
		catch(Error &e){
			e.OnError();
		}
	}
}
