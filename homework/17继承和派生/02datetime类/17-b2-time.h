/* 2152041 计科 王浩 */
#include <iostream>
using namespace std;
#define MAX_SECONDS 86400

int check_seconds(int& h, int& m, int& s);
int trans_to_seconds( int h,  int m,  int s);
#ifndef _CLASSTIME_
#define _CLASSTIME_
class Time {
protected:
	int hour;
	int min;
	int sec;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	/* 构造函数 */
	Time();
	Time(const int y, const int m);
	Time(const int y, const int m, const int d);
	/* 更改与展示函数 */
	void set(const int y, const int m, const int d);
	void set(const int y, const int m);
	void set(const int y);
	void set();
	void set(const Time& a);
	void get(int& y, int& m, int& d);
	void show();
	/* 转换构造与类型转换函数 */
	Time(const int past_days);
	operator int const();
	/* +、-重载函数 */
	friend Time operator+(const int past_days, const Time& a);
	friend Time operator+(const Time& a, const int past_days);
	friend Time operator-(const Time& a, const int past_days);
	friend int operator-(const Time& a, const Time& b);
	/* ++、--重载函数 */
	Time operator ++();//前置型
	Time operator ++(int);//后置型
	Time operator --();//前置型
	Time operator --(int);//后置型
	/* 标准输出输入cout、cin重载 */
	friend ostream& operator<<(ostream& out, const Time& a);
	friend istream& operator>>(istream& in, Time& a);
	/* 六个比较运算符重载 */
	friend bool operator>(const Time& a, const Time& b);
	friend bool operator<(const Time& a, const Time& b);
	friend bool operator>=(const Time& a, const Time& b);
	friend bool operator<=(const Time& a, const Time& b);
	friend bool operator==(const Time& a, const Time& b);
	friend bool operator!=(const Time& a, const Time& b);
};
#endif
