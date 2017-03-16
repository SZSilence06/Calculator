#ifndef _H_BIGN_H
#define _H_BIGN_H

#include "define.h"

int H_CharToNum(char c);
char H_NumToChar(int a);

class H_Bign:public Bign
{
public:
	static int Show_Digit;
public:
	H_Bign();
	H_Bign(char s[]);
	H_Bign(int a);
	H_Bign operator -();
	static void SetShowDigit(int a);
};

H_Bign Abs(H_Bign a);
H_Bign operator +(H_Bign a,H_Bign b);
H_Bign operator -(H_Bign a,H_Bign b);
H_Bign operator *(H_Bign a,H_Bign b);
H_Bign operator /(H_Bign a,H_Bign b);
bool operator >(H_Bign a,H_Bign b);
bool operator ==(H_Bign a,H_Bign b);
bool operator >=(H_Bign a,H_Bign b);
ostream &operator <<(ostream &out,H_Bign a);

#endif