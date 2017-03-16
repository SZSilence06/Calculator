#ifndef _EXCEPTION_H
#define _EXCEPTION_H

class Error
{
public:
	virtual void OnError();
};

class Input_Error:public Error
{
private:
	char ErrorChar;
public:
	Input_Error();
	Input_Error(char c);
	virtual void OnError();
};

class Expression_Error:public Error
{
public:
	Expression_Error();
	virtual void OnError();
};

class Math_Error:public Error
{
private:
	int ErrorID;
public:
	Math_Error();
	Math_Error(int a);
	virtual void OnError();
};

#endif