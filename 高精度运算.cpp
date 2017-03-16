#include "define.h"
#include "exception.h"

int Bign::Show_Digit=20;

int CharToNum(char c){    //字符转换为数
	return c-('1'-1);
}

char NumToChar(int a){    //数转换为字符
	return a+('1'-1);
}

int Max(int a,int b){    
	return a>b?a:b;
}

Bign::Bign()
{
	for(int i=0;i<1000;i++) num[i]=0;
	length=0;
	sign=0;
	digit=0;
}

Bign::Bign(int a)
{
	for(int i=0;i<1000;i++) num[i]=0;
	if(a>=0) sign=0;
	else sign=1;
	i=0;
	while(a){
		num[i++]=a%10;
		a=(a-(a%10))/10;
	}
	length=i;
	digit=0;
	Correct();
}

Bign::Bign(char s[])
{
	int i,j;
	length=0;
	digit=0;
	for(i=0;s[i];i++);
	i--;
	if(s[0]=='-'){
		sign=1;
	}
	else sign=0;
	j=0;	 
	for(;i>=0;i--){
		if(s[i]=='.'){
			digit=j;
			continue;
		}
		if(i==0&&s[i]=='-') break;
		num[j++]=CharToNum(s[i]);
		length++;
	}
	for(;j<1000;j++) num[j]=0;
	Correct();
}

Bign Abs(Bign a){
	Bign c=a;
	c.sign=1;
	return c;
}

bool operator >(Bign a,Bign b){
	if(a.length!=b.length) return a.length>b.length;
	if(a.sign!=b.sign) return a.sign<b.sign;
	for(int i=a.length-1;i>=0;i--){
		if(a.num[i]!=b.num[i]){
			if(a.sign==0) return a.num[i]>b.num[i];
			else return a.num[i]<b.num[i];
		}
	}
	return false;    //a==b,返回false
}

bool operator ==(Bign a,Bign b){
	if(a.sign!=b.sign) return false;
	if(a.length!=b.length) return false;
	for(int i=0;i<a.length;i++){
		if(a.num[i]!=b.num[i]) return false;
	}
	return true;
}

bool operator >=(Bign a,Bign b){
	if(a>b||a==b) return true;
	return false;
}

bool operator !=(Bign a,Bign b){
	return !(a==b);
}


Bign Bign::operator -()
{
	Bign c=*this;
	c.sign=!c.sign;
	return c;
}

Bign operator +(Bign a,Bign b)
{
	Bign c;
	int jin=0,sum,dig;
	dig=Max(a.digit,b.digit);
	c.digit=dig;
	if(a.digit<dig){             
		for(int i=a.length-1;i>=0;i--){    //采用在末尾加0的方式对齐小数点
			a.num[i+(dig-a.digit)]=a.num[i];
			a.num[i]=0;
		}
		a.length+=dig-a.digit;
		a.digit=dig;
	}
	else if(b.digit<dig){         
		for(int i=b.length-1;i>=0;i--){    //采用在末尾加0的方式对齐小数点
			b.num[i+(dig-b.digit)]=b.num[i];
			b.num[i]=0;
		}
		b.length+=dig-b.digit;
		b.digit=dig;
	}
	if(a.sign==0&&b.sign==0){
		for(int i=0;i<a.length||i<b.length;i++){
			sum=a.num[i]+b.num[i]+jin;
			jin=0;
			if(sum>=10){
				jin++;
				sum-=10;
			}
			c.num[i]+=sum;
			c.length++;
		}
		if(jin){
			c.num[i]++;
			c.length++;
		}
		c.Correct();
		return c;
	}
	else if(a.sign==1&&b.sign==0) return b-(-a);
	else if(a.sign==0&&b.sign==1) return a-(-b);
	return -((-a)+(-b));
}

Bign operator -(Bign a,Bign b)
{
	Bign c;
	int jin=0,sub,dig;
	dig=Max(a.digit,b.digit);
	c.digit=dig;
	if(a.digit<dig){             
		for(int i=a.length-1;i>=0;i--){   //采用在末尾加0的方式对齐小数点
			a.num[i+(dig-a.digit)]=a.num[i];
			a.num[i]=0;
		}
		a.length+=dig-a.digit;
		a.digit=dig;
	}
	else if(b.digit<dig){              
		for(int i=b.length-1;i>=0;i--){    //采用在末尾加0的方式对齐小数点
			b.num[i+(dig-b.digit)]=b.num[i];
			b.num[i]=0;
		}
		b.length+=dig-b.digit;
		b.digit=dig;
	}
	if(a.sign==b.sign){
		if(a>=b){          //如果a>b,表明结果是正数，按正常减法步骤计算
			for(int i=0;i<a.length||i<b.length;i++){
				sub=a.num[i]-b.num[i]-jin;
				jin=0;
				if(sub<0){
					jin++;
					sub+=10;
				}
				c.num[i]+=sub;
				c.length++;
			}
			if(jin){
				c.num[i]--;
				c.length++;
			}
			c.sign=0;
			c.Correct();
			return c;
		}
		else return -(b-a);
	}
	else if(a.sign==0&&b.sign==1) return a+(-b);
	return -(-a+b);
}

Bign operator *(Bign a,Bign b)
{
	Bign c;
	int jin,ji,i,j;
	c.digit=a.digit+b.digit;
	c.sign=a.sign^b.sign;  
	jin=0;
	for(i=0;i<a.length;i++){
		for(j=0;j<b.length;j++){
			ji=a.num[i]*b.num[j]+jin;
			jin=ji/10;
			ji%=10;
			c.num[i+j]+=ji;
			jin+=c.num[i+j]/10;
			c.num[i+j]%=10;
		}
		c.num[i+j]+=jin;
		jin=0;
	}
	c.num[i+j-1]+=jin;
	jin=0;
	c.length=i+j;
	c.Correct();
	return c;
}

Bign operator /(Bign a,Bign b)
{
	if(b==0){
		Math_Error e(1);
		throw e;
	}
	Bign yu;
	char x[1000],y[1000];
	int k;
	a.digit-=b.digit;
	if(a.digit<0){        //将b化为整数，同时相应地放大或缩小a
		int n=-a.digit;
		for(int i=a.length-1;i>=0;i--){
			a.num[i+n]=a.num[i];
			a.num[i]=0;
		}
		a.length+=n;
		a.digit=0;
	}
	b.digit=0;
	
	//作第一次除法
	int j=0;
	for(int i=a.length-1;i>=a.length-b.length&&i>=0;i--){
		x[j++]=NumToChar(a.num[i]);
		if(i==a.digit) x[j++]='.';
	}
	x[j]='\0';
	Bign bdiv(x),div;
	
	for(j=1;j<10;j++){
		div=j*b;
		if(div>bdiv) break;
	}
	k=0;
	y[k++]=NumToChar(j-1);
	yu=bdiv-(j-1)*b;

	//接着继续除
	for(;i>=0;i--){
		bdiv=yu*10+a.num[i];
		for(j=1;j<10;j++){
			div=j*b;
			if(div>bdiv) break;
		}
		y[k++]=NumToChar(j-1);
		yu=bdiv-(j-1)*b;
	}

	//若没有除尽，则商为小数，处理小数问题
	if(yu!=0){
		y[k++]='.';
		for(i=1;i<=500;i++){   //精确到小数点后500位
			bdiv=yu*10;
			for(j=1;j<10;j++){
				div=j*b;
				if(div>bdiv) break;
			}
			y[k++]=NumToChar(j-1);
			yu=bdiv-(j-1)*b;
		}
	}


	y[k]='\0';
	Bign c(y);
	return c;
}

ostream &operator <<(ostream &out,Bign a){
	int i=a.length-1;
	int count=a.Show_Digit;
	if(a.length==0){
		out<<0;
		return out;
	}
	if(a.sign)	out<<"-";
	for(;i>=a.digit;i--) out<<a.num[i];
	if(!count) return out;
	if(i>=0) out<<".";
	for(;i>=0;i--){
		if(!count) return out;
		out<<a.num[i];
		count--;
	}
	return out;
}

void Bign::Correct()   //对运算后得到的数进行修正，包括删去多余的0、修正长度及小数点位置等
{
	int i,x=0;
	for(i=length-1;i>=digit&&num[i]==0;i--) length--;   //去除整数部分开头的0
	for(i=0;i<digit&&num[i]==0;i++){                    //计算小数末尾多余的0的个数
		x++;
	}
	for(i=x;i<length&&x;i++){                           //去除小数末尾多余的0    
		num[i-x]=num[i];
		num[i]=0;
	}
	length-=x;
	digit-=x;
	if(digit==length) length++;                         //如果是纯小数，则在小数点前面加个0，形成0.***的格式
}

void Bign::SetShowDigit(int a)
{
	Show_Digit=a;
}