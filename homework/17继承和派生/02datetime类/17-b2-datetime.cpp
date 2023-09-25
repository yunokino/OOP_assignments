/* 2152041 ¼Æ¿Æ ÍõºÆ */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

DateTime::DateTime() :Date(), Time()
{

}

DateTime::DateTime(const DateTime& datetime)
{
	Date::set(datetime.year, datetime.month, datetime.day);
	Time::set(datetime.hour, datetime.min, datetime.sec);
}

DateTime::DateTime(const long long past_seconds)
{
	int days = 0;
	long long tmp = past_seconds;
	if (tmp < 0)
		tmp += Day_Seconds * MAX_DAYS;
	if (tmp > Day_Seconds * MAX_DAYS)
		tmp -=Day_Seconds * MAX_DAYS;
	while (tmp >= Day_Seconds)
	{
		days++;
		tmp -= Day_Seconds;
	}
	Time::set(Time((int)tmp));
	Date::set(Date(days));
}

DateTime::operator long long const()
{
	return trans_to_seconds(year, month, day, hour, min, sec);
}

DateTime DateTime::operator++()
{
	long long seconds = trans_to_seconds(year, month, day, hour, min, sec);
	seconds++;
	*this = DateTime(seconds);
	return DateTime(*this);
}

DateTime DateTime::operator++(int)
{
	long long seconds = trans_to_seconds(year, month, day, hour, min, sec);
	long long tmp = seconds;
	seconds++;
	*this = DateTime(seconds);
	return DateTime(tmp);
}

DateTime DateTime::operator--()
{
	long long seconds = trans_to_seconds(year, month, day, hour, min, sec);
	seconds--;
	*this = DateTime(seconds);
	return DateTime(*this);
}

DateTime DateTime::operator--(int)
{
	long long seconds = trans_to_seconds(year, month, day, hour, min, sec);
	long long tmp = seconds;
	seconds--;
	*this = DateTime(seconds);
	return DateTime(tmp);
}

DateTime::DateTime(const int y, const int m):Time()
{
	Date::set(y, m);
}

DateTime::DateTime(const int y, const int m, const int d) :Date(y, m, d), Time()
{
}

DateTime::DateTime(const int y, const int m, const int d, const int h):Date(y,m,d)
{
	Time::set(h);
	int error = 0;
	error = check_days(trans_to_days(this->year, this->month, this->day), this->year, this->month, this->day);
	if (!error)
	{
		if (h < 0 || h > 23)
			error = 1;
	}
	if (error)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		this->hour= 0;
		this->min = 0;
		this->sec = 0;
	}
}

DateTime::DateTime(const int y, const int m, const int d, const int h, const int mi) :Date(y, m, d)
{
	Time::set(h, mi);
	int error = 0;
	error = check_days(trans_to_days(this->year, this->month, this->day), this->year, this->month, this->day);
	if (!error)
	{
		if (h < 0 || h > 23 || mi < 0 || mi >59)
			error = 1;
	}
	if (error)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		this->hour = 0;
		this->min = 0;
		this->sec = 0;
	}
}

DateTime::DateTime(const int y, const int m, const int d, const int h, const int mi, const int s):Date(y,m,d),Time(h,mi,s)
{
	int error = 0;
	if (y < 1900 || y > 2099 || m < 1 || m > 12)
	{
		error = 1;
	}
	if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && m == 2 && (d < 1 || d >29))
		error = 1;
	else if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (m == 1 || m == 3 || m == 5
		|| m == 7 || m == 8 || m == 10 || m == 12) && (d < 1 || d >31))
		error = 1;
	else if (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (m == 4 || m == 6 || m == 9
		|| m == 11) && (d < 1 || d >30))
		error = 1;
	else if (!((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && m == 2 && (d < 1 || d >28))
		error = 1;
	else if (!((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (m == 1 || m == 3 || m == 5
		|| m == 7 || m == 8 || m == 10 || m == 12) && (d < 1 || d >31))
		error = 1;
	else if (!((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (m == 4 || m == 6 || m == 9
		|| m == 11) && (d < 1 || d >30))
		error = 1;
	if (!error)
	{
		if (h < 0 || h > 23 || mi < 0 || mi >59 || s < 0|| s>59)
			error = 1;
	}
	if (error)
	{
		this->year = 1900;
		this->month = 1;
		this->day = 1;
		this->hour = 0;
		this->min = 0;
		this->sec = 0;
	}
}

void DateTime::get(int& y, int& m, int& d, int& h, int& mi, int &s)
{
	y = year;
	m = month;
	d = day;
	h = hour;
	mi = min;
	s = sec;
}

void DateTime::set(const DateTime& datetime)
{
	Date::set(datetime.year, datetime.month, datetime.day);
	Time::set(datetime.hour, datetime.min, datetime.sec);
}

void DateTime::set()
{
	year = 1900;
	month = 1;
	day = 1;
	hour = 0;
	min = 0;
	sec = 0;
}

void DateTime::set(const int y)
{
	Date::set(y);
	Time::set(0,0,0);
}

void DateTime::set(const int y, const int m)
{
	Date::set(y,m);
	Time::set(0, 0, 0);
}

void DateTime::set(const int y, const int m, const int d)
{
	Date::set(y,m,d);
	Time::set(0, 0, 0);
}

void DateTime::set(const int y, const int m, const int d, const int h)
{
	this->year = y;
	this->month = m;
	this->day = d;
	this->hour = h;
	this->min = 0;
	this->sec = 0;
	check_seconds(this->year, this->month, this->day, this->hour, this->min, this->sec);
}

void DateTime::set(const int y, const int m, const int d, const int h, const int mi)
{
	this->year = y;
	this->month = m;
	this->day = d;
	this->hour = h;
	this->min = mi;
	this->sec = 0;
	check_seconds(this->year, this->month, this->day, this->hour, this->min, this->sec);
}

void DateTime::set(const int y, const int m, const int d, const int h, const int mi, const int s)
{
	this->year = y;
	this->month = m;
	this->day = d;
	this->hour = h;
	this->min = mi;
	this->sec = s;
	check_seconds(this->year, this->month, this->day, this->hour, this->min, this->sec);
}

void DateTime::show()
{
	cout << year << "-";
	cout << setw(2)<< setfill('0') << setw(2) << month << "-" << setw(2) << day << " " << setw(2) << hour << ":" << setw(2) << min << ":" << setw(2) << sec << endl;
}

void check_seconds(int& y, int& m, int& d, int& h, int& mi, int& s)
{
	int error = 0;
	error = check_days(trans_to_days(y, m, d), y, m, d);
	if(!error)
		check_seconds(h, mi, s);
	if (error)
	{
		y = 1900;
		m = 1;
		d = 1;
		h = 0;
		mi = 0;
		s = 0;
	}
}

long long trans_to_seconds(const int y, const int m, const int d, const int h, const int mi, const int s)
{
	long long seconds = 0;
	seconds += trans_to_days(y, m, d) * Day_Seconds;
	seconds += trans_to_seconds(h, mi, s);
	return seconds;
}

DateTime operator+(const long long past_seconds, const DateTime& a)
{
	long long seconds = trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec);
	seconds += past_seconds;
	return DateTime(seconds);
}

DateTime operator+(const DateTime& a, const long long past_seconds)
{
	return past_seconds + a;
}

DateTime operator-(const DateTime& a, const long long past_seconds)
{
	long long seconds = trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec);
	seconds -= past_seconds;
	return DateTime(seconds);
}

long long operator-(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) - trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

DateTime operator+(const DateTime& a, const int past_seconds)
{
	long long seconds = trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec);
	seconds += past_seconds;
	return DateTime(seconds);
}

DateTime operator+(const int past_seconds, const DateTime& a)
{
	return a + past_seconds;
}


DateTime operator-(const DateTime& a, const int past_seconds)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) - past_seconds;
}

ostream& operator<<(ostream& out, const DateTime& a)
{
	out << a.year << "-";
	out << setw(2) << setfill('0') << setw(2) << a.month << "-" << setw(2) << a.day << " " << setw(2) << a.hour << ":" << setw(2) << a.min << ":" << setw(2) << a.sec << endl;
	return out;
}

istream& operator>>(istream& in, DateTime& a)
{
	in >> a.year >> a.month >> a.day >> a.hour >> a.min >> a.sec;
	check_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec);
	return in;
}

bool operator>(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year,a.month,a.day,a.hour,a.min,a.sec) > trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

bool operator<(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) < trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

bool operator>=(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) >= trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

bool operator<=(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) <= trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

bool operator==(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) == trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}

bool operator!=(const DateTime& a, const DateTime& b)
{
	return trans_to_seconds(a.year, a.month, a.day, a.hour, a.min, a.sec) != trans_to_seconds(b.year, b.month, b.day, b.hour, b.min, b.sec);
}
