/* 2152041 ¼Æ¿Æ ÍõºÆ */


#include <iostream>
#include "17-b1-TString.h"
using namespace std;

class TStringAdv :public TString {
public:
	TStringAdv();

	TStringAdv(const char* str);

	TStringAdv(const TString& str);

	TStringAdv& assign(const TStringAdv& ts2);

	TStringAdv& assign(const char* s);

	TStringAdv& append(const TStringAdv& ts2);

	TStringAdv& append(const char* s);

	TStringAdv& append(const char& c);

	TStringAdv& insert(const TStringAdv& ts2, int pos);

	TStringAdv& insert(const char* s, int pos);

	TStringAdv& insert(const char& c, int pos);

	TStringAdv& erase(const TStringAdv& ts2);

	TStringAdv& erase(const char* s);

	TStringAdv& erase(const char& c);

	TStringAdv  substr(const int pos, const int len);

	char& at(const int n);

	friend istream& operator>>(istream& in, TStringAdv& str);

	friend ostream& operator<<(ostream& out, const TStringAdv& str);

};