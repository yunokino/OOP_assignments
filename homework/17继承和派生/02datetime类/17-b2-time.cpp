/* 2152041 计科 王浩 */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

Time::Time()
{
	hour = 0;
	min = 0;
	sec = 0;
}

Time::Time(const int h, const int m)
{
	hour = h;
	min = m;
	sec = 0;
	check_seconds(hour, min, sec);
}

Time::Time(const int h, const int m, const int s)
{
	hour = h;
	min = m;
	sec = s;
	check_seconds(hour, min, sec);
}
/* 更改与展示函数 */
void Time::set()
{
	hour = 0;
	min = 0;
	sec = 0;
}

void Time::set(const int h, const int m, const int s)
{
	hour = h;
	min = m;
	sec = s;
	check_seconds(hour, min, sec);
}
void Time::set(const int h, const int m)
{
	hour = h;
	min = m;
	sec = 0;
	check_seconds(hour, min, sec);
}
void Time::set(const int h)
{
	hour = h;
	min = 0;
	sec = 0;
	check_seconds(hour, min, sec);
}

void Time::set(const Time& a)
{
	hour = a.hour;
	min = a.min;
	sec = a.sec;
	check_seconds(hour, min, sec);
}

void Time::get(int& h, int& m, int& s)
{
	h = hour;
	m = min;
	s = sec;
}
void Time::show()
{
	cout << setw(2) << setfill('0') << hour << ":" << min << ":" << sec << endl;
}
/* 转换构造与类型转换函数 */
Time::Time(const int past_seconds)
{
	int tmp = past_seconds;
	int time[3] = {0};
	while (tmp >= 3600)
	{
		time[0] += 1;
		tmp -= 3600;
	}
	while (tmp >= 60)
	{
		time[1] += 1;
		tmp -= 60;
	}
	time[2] = tmp;
	hour = time[0];
	min = time[1];
	sec = time[2];
}
Time::operator int const()
{
	return trans_to_seconds(hour, min, sec);
}
/* +、-重载函数 */
Time operator+(const int past_seconds, const Time& a)
{
	Time tmp;
	int days = past_seconds + trans_to_seconds(a.hour, a.min, a.sec);
	if (days > MAX_SECONDS)
		days -= MAX_SECONDS;
	tmp = Time(days);
	return tmp;
}
Time operator+(const Time& a, const int past_seconds)
{
	Time tmp;
	int seconds = past_seconds + trans_to_seconds(a.hour, a.min, a.sec);
	if (seconds > MAX_SECONDS)
		seconds -= MAX_SECONDS;
	tmp = Time(seconds);
	return tmp;
}
Time operator-(const Time& a, const int past_seconds)
{
	Time tmp;
	int seconds = trans_to_seconds(a.hour, a.min, a.sec) - past_seconds;
	if (seconds < 0)
		seconds += MAX_SECONDS;
	tmp = Time(seconds);
	return tmp;
}
int operator-(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) - trans_to_seconds(b.hour, b.min, b.sec);
}
/* ++、--重载函数 */
Time Time::operator ++()//前置型
{
	int seconds = trans_to_seconds(this->hour, this->min, this->sec);
	seconds++;
	if (seconds > MAX_SECONDS)
		seconds -= MAX_SECONDS;
	*this = Time(seconds);
	return Time(seconds);
}
Time Time::operator ++(int)//后置型
{
	Time tmp(this->hour, this->min, this->sec);
	int seconds = trans_to_seconds(this->hour, this->min, this->sec);
	seconds++;
	if (seconds > MAX_SECONDS)
		seconds -= MAX_SECONDS;
	*this = Time(seconds);
	return tmp;
}
Time Time::operator --()//前置型
{
	int seconds = trans_to_seconds(this->hour, this->min, this->sec);
	seconds--;
	if (seconds < 0)
		seconds += MAX_SECONDS;
	*this = Time(seconds);
	return Time(seconds);
}
Time Time::operator --(int)//后置型
{
	Time tmp(this->hour, this->min, this->sec);
	int seconds = trans_to_seconds(this->hour, this->min, this->sec);
	seconds--;
	if (seconds < 0)
		seconds += MAX_SECONDS;
	*this = Time(seconds);
	return tmp;
}
/* 标准输出输入cout、cin重载 */
ostream& operator<<(ostream& out, const Time& a)
{
	out << setw(2)<<setfill('0') << a.hour << ":" << a.min << ":" << a.sec << "日";
	return out;
}
istream& operator>>(istream& in, Time& a)
{
	in >> a.hour >> a.min >> a.sec;
	check_seconds(a.hour, a.min, a.sec);
	return in;
}
/* 六个比较运算符重载 */
bool operator>(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) > trans_to_seconds(b.hour, b.min, b.sec);
}
bool operator<(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) < trans_to_seconds(b.hour, b.min, b.sec);
}
bool operator>=(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) >= trans_to_seconds(b.hour, b.min, b.sec);
}
bool operator<=(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) <= trans_to_seconds(b.hour, b.min, b.sec);
}
bool operator==(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) == trans_to_seconds(b.hour, b.min, b.sec);
}
bool operator!=(const Time& a, const Time& b)
{
	return trans_to_seconds(a.hour, a.min, a.sec) != trans_to_seconds(b.hour, b.min, b.sec);
}

int check_seconds(int &h,int&m,int&s)
{
	int error = 0;
	if (h < 0 || h > 23)
	{
		h = 0;
		m = 0;
		s = 0;
		error = 1;
	}
	if (m < 0 || m > 59)
	{
		h = 0;
		m = 0;
		s = 0;
		error = 1;
	}
	if (s < 0 || s > 59)
	{
		h = 0;
		m = 0;
		s = 0;
		error = 1;
	}
	return error;
}

int trans_to_seconds( int h,  int m,  int s)
{
	int seconds = 0;
	seconds += s;
	while (m != 0)
	{
		seconds += 60;
		m--;
	}
	while (h != 0)
	{
		seconds += 3600;
		h--;
	}
	return seconds;
}