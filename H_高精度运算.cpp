#include "H_高精度运算.h"
#include "exception.h"

int H_Bign::Show_Digit=20;

int H_CharToNum(char c){    //字符转换为数
	if('c'>='0'&&c<='9') return c-('1'-1);
	else return c-('a'-10);
}

char H_NumToChar(int a){    //数转换为字符
	if(a<10) return a+('1'-1);
	else return a+('a'-10);
}

H_Bign::H_Bign()
{
	for(int i=0;i<1000;i++) num[i]=0;
	length=0;
	sign=0;
	digit=0;
}

H_Bign::H_Bign(int a)
{
	for(int i=0;i<1000;i++) num[i]=0;
	if(a>=0) sign=0;
	else sign=1;
	i=0;
	while(a){
		num[i++]=a%16;
		a=(a-(a%16))/16;
	}
	length=i;
	digit=0;
	Correct();
}

H_Bign::H_Bign(char s[])
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
		num[j++]=H_CharToNum(s[i]);
		length++;
	}
	for(;j<1000;j++) num[j]=0;
	Correct();
}

H_Bign Abs(H_Bign a){
	H_Bign c=a;
	c.sign=1;
	return c;
};

bool operator >(H_Bign a,H_Bign b){
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

bool operator ==(H_Bign a,H_Bign b){
	if(a.sign!=b.sign) return false;
	if(a.length!=b.length) return false;
	for(int i=0;i<a.length;i++){
		if(a.num[i]!=b.num[i]) return false;
	}
	return true;
}

bool operator >=(H_Bign a,H_Bign b){
	if(a>b||a==b) return true;
	return false;
}

bool operator !=(H_Bign a,H_Bign b){
	return !(a==b);
}


H_Bign H_Bign::operator -()
{
	H_Bign c=*this;
	c.sign=!c.sign;
	return c;
}

H_Bign operator +(H_Bign a,H_Bign b)
{
	H_Bign c;
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
			if(sum>=16){
				jin++;
				sum-=16;
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

H_Bign operator -(H_Bign a,H_Bign b)
{
	H_Bign c;
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
					sub+=16;
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

H_Bign operator *(H_Bign a,H_Bign b)
{
	H_Bign c;
	int jin,ji,i,j;
	c.digit=a.digit+b.digit;
	c.sign=a.sign^b.sign;  
	jin=0;
	for(i=0;i<a.length;i++){
		for(j=0;j<b.length;j++){
			ji=a.num[i]*b.num[j]+jin;
			jin=ji/16;
			ji%=16;
			c.num[i+j]+=ji;
			jin+=c.num[i+j]/16;
			c.num[i+j]%=16;
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

H_Bign operator /(H_Bign a,H_Bign b)
{
	if(b==0){
		Math_Error e(1);
		throw e;
	}
	H_Bign yu;
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
		x[j++]=H_NumToChar(a.num[i]);
		if(i==a.digit) x[j++]='.';
	}
	x[j]='\0';
	H_Bign bdiv(x),div;
	
	for(j=1;j<16;j++){
		div=j*b;
		if(div>bdiv) break;
	}
	k=0;
	y[k++]=H_NumToChar(j-1);
	yu=bdiv-(j-1)*b;

	//接着继续除
	for(;i>=0;i--){
		bdiv=yu*16+a.num[i];
		for(j=1;j<16;j++){
			div=j*b;
			if(div>bdiv) break;
		}
		y[k++]=H_NumToChar(j-1);
		yu=bdiv-(j-1)*b;
	}

	//若没有除尽，则商为小数，处理小数问题
	if(yu!=0){
		y[k++]='.';
		for(i=1;i<=20;i++){   //精确到小数点后20位
			bdiv=yu*16;
			for(j=1;j<16;j++){
				div=j*b;
				if(div>bdiv) break;
			}
			y[k++]=H_NumToChar(j-1);
			yu=bdiv-(j-1)*b;
		}
	}


	y[k]='\0';
	H_Bign c(y);
	return c;
}

ostream &operator <<(ostream &out,H_Bign a){
	int i=a.length-1;
	int count=H_Bign.Show_Digit;
	if(a.length==0){
		out<<0;
		return out;
	}
	if(a.sign)	out<<"-";
	for(;i>=a.digit;i--){
		if(a.num[i]<10) out<<a.num[i];
		else out<<(char)(a.num[i]+'A'-10);
	}
	if(!count) return out;
	if(i>=0) out<<".";
	for(;i>=0;i--){
		if(!count) return out;
		if(a.num[i]<10) out<<a.num[i];
		else out<<(char)(a.num[i]+'A'-10);
		count--;	
	}
	return out;
}

void H_Bign::SetShowDigit(int a)
{
	Show_Digit=a;
}
