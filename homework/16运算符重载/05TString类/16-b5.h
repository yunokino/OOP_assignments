/* 2152041 计科 王浩 */


#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */

class TString {
private:
	char* content;
	int   len;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	TString();//空参构造函数
	TString(const char* str);//一参构造函数
	TString(const TString& str);//一参构造函数
	/* 赋值运算符重载 */
	TString& operator=(const char* str);
	TString& operator=(const TString& str);
	/* +运算符重载 */
	friend const TString operator+(const TString& str1, const TString& str2);
	friend const TString operator+(const TString& str2, const char* str1);
	friend const TString operator+(const char* str1, const TString& str2);
	friend const TString operator+(const TString& str2, const char ch);
	friend const TString operator+(const char ch, const TString& str2);
	/* 自加+=运算符重载 */
	TString& operator+=(const TString& str);
	TString& operator+=(const char* str);
	TString& operator+=(const char ch);
	/* -运算符重载 */
	friend const TString operator-(const TString& str1, const TString&str2);
	friend const TString operator-(const TString& str1, const char* str2);
	friend const TString operator-(const TString& str1, const char ch);
	/* 自减-=运算符重载 */
	TString& operator-=(const TString& str);
	TString& operator-=(const char* str);
	TString& operator-=(const char ch);
	/* *运算符重载 */
	friend TString operator*(const TString& str1, const int multiplier);
	/* 自乘*=运算符重载*/
	TString& operator*=(const int multiplier);
	/* 取反(反转)!运算符重载 */
	TString operator!();
	/* 输入输出流运算符重载 */
	friend ostream& operator<<(ostream& out, const TString& str);
	friend istream& operator>>(istream& in, TString& str);
	/* 六个比较运算符 */
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
	/* 取字符串内容函数 */
	const char* c_str ()const;
	/* 求串长度 */
	const int length();
	/* 类型转换函数 */
	//operator char* ();
	char& operator[](const int location);
	/* 析构函数 */
	~TString();
};

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString&);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
#define CHAR_SIZE 1
#define MAX_SIZE 65536