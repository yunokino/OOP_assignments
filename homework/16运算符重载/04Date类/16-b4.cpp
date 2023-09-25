/* 2152041 计科 王浩 */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
/* 构造函数 */
Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

Date::Date(const int y, const int m, const int d)
{
	year = y;
	if (year < 1900 || year > 2099)
		year = 2000;
	month = m;
	if (month < 1 || month > 12)
		month = 1;
	day = d;
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 29 || day < 1))
		day = 1;
	else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 28 || day < 1))
		day = 1;
	else if ((month == 1 || month == 3 || month == 5
		|| month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day < 1))
		day = 1;
	else if ((month == 4 || month == 6 || month == 9 ||  month == 11) &&(day > 30 || day < 1))
		day = 1;
	else;
}
///* 更改与展示函数 */
void Date::set(const int y, const int m, const int d)
{
	if (y != 0)
		year = y;
	if (year < 1900 || year > 2099)
		year = 2000;
	if (m != 0)
		month = m;
	if (month < 1 || month > 12)
		month = 1;
	if (d != 0)
		day = d;
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 29 || day < 1))
		day = 1;
	else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 28 || day < 1))
		day = 1;
	else if ((month == 1 || month == 3 || month == 5
		|| month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day < 1))
		day = 1;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1))
		day = 1;
	else;
}

void Date::set(const int y, const int m)
{
	if (y != 0)
		year = y;
	if (year < 1900 || year > 2099)
		year = 2000;
	if (m != 0)
		month = m;
	if (month < 1 || month > 12)
		month = 1;
	day = 1;
}

void Date::set(const int y)
{
	if (y != 0)
		year = y;
	if (year < 1900 || year > 2099)
		year = 2000;
	month = 1;
	day = 1;
}

void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
}

void Date::show()
{
	cout << year << "年" << month << "月" << day <<"日" << endl;
}
///* 转换构造与类型转换函数 */
Date::Date(const int past_days)
{
	if (past_days <= 1)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	else if (past_days >= 73049)
	{
		year = 2099;
		month = 12;
		day = 31;
	}
	else
	{
		year = compute_year(past_days);
		month = compute_month(past_days);
		day = compute_day(past_days);
		check_range(year, month, day);
	}
}
Date::operator int const()
{
	return trans_to_days(year, month, day);
}
///* +、-重载函数 */
Date operator+(const int past_days, const Date& a)
{
	Date tmp;
	int days = past_days + trans_to_days(a.year, a.month, a.day);
	tmp = Date(days);
	return tmp;
}
Date operator+(const Date& a, const int past_days)
{
	Date tmp;
	int days = past_days + trans_to_days(a.year, a.month, a.day);
	tmp = Date(days);
	return tmp;
}
Date operator-(const Date& a, const int past_days)
{
	Date tmp;
	int days = trans_to_days(a.year, a.month, a.day) - past_days;
	tmp = Date(days);
	return tmp;
}
int operator-(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) - trans_to_days(b.year, b.month, b.day);
}
///* ++、--重载函数 */
Date Date::operator ++()//前置型
{
	int days = trans_to_days(this->year, this->month, this->day);
	days++;
	check_days(days, this->year, this->month, this->day);
	*this = Date(days);
	return Date(days);
}
Date Date::operator ++(int)//后置型
{
	Date tmp(this->year, this->month, this->day);
	int days = trans_to_days(this->year, this->month, this->day);
	days++;
	check_days(days, this->year, this->month, this->day);
	*this = Date(days);
	return tmp;
}
Date Date::operator --()//前置型
{
	int days = trans_to_days(this->year, this->month, this->day);
	days--;
	check_days(days, this->year, this->month, this->day);
	*this = Date(days);
	return Date(days);
}
Date Date::operator --(int)//后置型
{
	Date tmp(this->year, this->month, this->day);
	int days = trans_to_days(this->year, this->month, this->day);
	days--;
	check_days(days, this->year, this->month, this->day);
	*this = Date(days);
	return tmp;
}
///* 标准输出输入cout、cin重载 */
ostream& operator<<(ostream& out, const Date& a)
{
	out << a.year << "年" << a.month << "月" << a.day << "日";
	return out;
}
istream& operator>>(istream& in, Date& a)
{
	in >> a.year >> a.month >> a.day;
	check_range(a.year, a.month, a.day);
	return in;
}
///* 六个比较运算符重载 */
bool operator>(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) > trans_to_days(b.year, b.month, b.day);
}
bool operator<(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) < trans_to_days(b.year, b.month, b.day);
}
bool operator>=(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) >= trans_to_days(b.year, b.month, b.day);
}
bool operator<=(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) <= trans_to_days(b.year, b.month, b.day);
}
bool operator==(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) == trans_to_days(b.year, b.month, b.day);
}
bool operator!=(const Date& a, const Date& b)
{
	return trans_to_days(a.year, a.month, a.day) != trans_to_days(b.year, b.month, b.day);
}
/* 如果有需要的其它全局函数的实现，可以写于此处 */
int compute_year(int past_days)
{
	int year = 1900;
	int loop = 1;
	while (loop)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			past_days -= 366;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
		else
		{
			past_days -= 365;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
	}
	return year;
}
int compute_month(int past_days)
{
	int year = 1900;
	int month = 1;
	int loop = 1;
	while (loop)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			past_days -= 366;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
		else
		{
			past_days -= 365;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
	}
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		past_days += 366;
	else
		past_days += 365;
	loop = 1;
	while (loop)
	{
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			past_days -= 29;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			past_days -= 28;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 1 || month == 3 || month == 5
			|| month == 7 || month == 8 || month == 10 || month == 12)
		{
			past_days -= 31;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			past_days -= 30;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else;
	}
	return month;
}
int compute_day(int past_days)
{
	int year = 1900;
	int month = 1;
	int day = 1;
	int loop = 1;
	while (loop)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			past_days -= 366;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
		else
		{
			past_days -= 365;
			if (past_days > 0)
				year++;
			else
				loop = 0;
		}
	}
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		past_days += 366;
	else
		past_days += 365;
	loop = 1;
	while (loop)
	{
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			past_days -= 29;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			past_days -= 28;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 1 || month == 3 || month == 5
			|| month == 7 || month == 8 || month == 10 || month == 12)
		{
			past_days -= 31;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			past_days -= 30;
			if (past_days > 0)
				month++;
			else
				loop = 0;
		}
		else;
	}
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		past_days += 29;
	else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		past_days += 28;
	else if (month == 1 || month == 3 || month == 5
		|| month == 7 || month == 8 || month == 10 || month == 12)
		past_days += 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		past_days += 30;
	else;
	day = past_days;
	return day;
}
int trans_to_days(int year, int month, int day)
{
	int count_days = 0;
	int tmp_year = 1900;
	int tmp_month = 1;
	while (tmp_year < year)
	{
		if ((tmp_year % 4 == 0 && tmp_year % 100 != 0) || tmp_year % 400 == 0)
			count_days += 366;
		else
			count_days += 365;
		tmp_year++;
	}
	while (tmp_month < month)
	{
		if (tmp_month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
			count_days += 29;
		else if (tmp_month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
			count_days += 28;
		else if (tmp_month == 1 || tmp_month == 3 || tmp_month == 5
			|| tmp_month == 7 || tmp_month == 8 || tmp_month == 10 || tmp_month == 12)
			count_days += 31;
		else if (tmp_month == 4 || tmp_month == 6 || tmp_month == 9 || tmp_month == 11)
			count_days += 30;
		else;
		tmp_month++;
	}
	count_days += day;
	return count_days;
}
void check_range(int &year, int &month, int &day)
{
	if (year < 1900 || year > 2099)
		year = 2000;
	if (month < 1 || month > 12)
		month = 1;
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 29 || day < 1))
		day = 1;
	else if (month == 2 && !((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day > 28 || day < 1))
		day = 1;
	else if ((month == 1 || month == 3 || month == 5
		|| month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day < 1))
		day = 1;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1))
		day = 1;
	else;
	
}
void check_days(const int past_days, int& year, int& month, int& day)
{
	if (past_days <= 1)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	else if (past_days >= 73049)
	{
		year = 2099;
		month = 12;
		day = 31;
	}
	else;
}
