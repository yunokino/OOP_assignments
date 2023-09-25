/* 2152041 �ƿ� ���� */


#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */

class TString {
private:
	char* content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
	TString();//�ղι��캯��
	TString(const char* str);//һ�ι��캯��
	TString(const TString& str);//һ�ι��캯��
	/* ��ֵ��������� */
	TString& operator=(const char* str);
	TString& operator=(const TString& str);
	/* +��������� */
	friend const TString operator+(const TString& str1, const TString& str2);
	friend const TString operator+(const TString& str2, const char* str1);
	friend const TString operator+(const char* str1, const TString& str2);
	friend const TString operator+(const TString& str2, const char ch);
	friend const TString operator+(const char ch, const TString& str2);
	/* �Լ�+=��������� */
	TString& operator+=(const TString& str);
	TString& operator+=(const char* str);
	TString& operator+=(const char ch);
	/* -��������� */
	friend const TString operator-(const TString& str1, const TString&str2);
	friend const TString operator-(const TString& str1, const char* str2);
	friend const TString operator-(const TString& str1, const char ch);
	/* �Լ�-=��������� */
	TString& operator-=(const TString& str);
	TString& operator-=(const char* str);
	TString& operator-=(const char ch);
	/* *��������� */
	friend TString operator*(const TString& str1, const int multiplier);
	/* �Գ�*=���������*/
	TString& operator*=(const int multiplier);
	/* ȡ��(��ת)!��������� */
	TString operator!();
	/* ������������������ */
	friend ostream& operator<<(ostream& out, const TString& str);
	friend istream& operator>>(istream& in, TString& str);
	/* �����Ƚ������ */
	friend bool operator>(const TString& a, const TString& b);
	friend bool operator>(const TString& a, const char*str);
	friend bool operator>(const char* str ,const TString& a);
	friend bool operator<(const TString& a, const TString& b);
	friend bool operator<(const TString& a, const char* str);
	friend bool operator<(const char* str, const TString& a);
	friend bool operator>=(const TString& a, const TString& b);
	friend bool operator>=(const TString& a, const char* str);
	friend bool operator>=(const char* str, const TString& a);
	friend bool operator<=(const TString& a, const TString& b);
	friend bool operator<=(const TString& a, const char* str);
	friend bool operator<=(const char* str, const TString& a);
	friend bool operator==(const TString& a, const TString& b);
	friend bool operator==(const TString& a, const char* str);
	friend bool operator==(const char* str, const TString& a);
	friend bool operator!=(const TString& a, const TString& b);
	friend bool operator!=(const TString& a, const char* str);
	friend bool operator!=(const char* str, const TString& a);
	/* ȡ�ַ������ݺ��� */
	const char* c_str ()const;
	/* �󴮳��� */
	const int length();
	/* ����ת������ */
	//operator char* ();
	char& operator[](const int location);
	/* �������� */
	~TString();
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int TStringLen(const TString&);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
#define CHAR_SIZE 1
#define MAX_SIZE 65536