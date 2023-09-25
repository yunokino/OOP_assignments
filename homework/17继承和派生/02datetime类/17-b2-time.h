/* 2152041 �ƿ� ���� */
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
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
	/* ���캯�� */
	Time();
	Time(const int y, const int m);
	Time(const int y, const int m, const int d);
	/* ������չʾ���� */
	void set(const int y, const int m, const int d);
	void set(const int y, const int m);
	void set(const int y);
	void set();
	void set(const Time& a);
	void get(int& y, int& m, int& d);
	void show();
	/* ת������������ת������ */
	Time(const int past_days);
	operator int const();
	/* +��-���غ��� */
	friend Time operator+(const int past_days, const Time& a);
	friend Time operator+(const Time& a, const int past_days);
	friend Time operator-(const Time& a, const int past_days);
	friend int operator-(const Time& a, const Time& b);
	/* ++��--���غ��� */
	Time operator ++();//ǰ����
	Time operator ++(int);//������
	Time operator --();//ǰ����
	Time operator --(int);//������
	/* ��׼�������cout��cin���� */
	friend ostream& operator<<(ostream& out, const Time& a);
	friend istream& operator>>(istream& in, Time& a);
	/* �����Ƚ���������� */
	friend bool operator>(const Time& a, const Time& b);
	friend bool operator<(const Time& a, const Time& b);
	friend bool operator>=(const Time& a, const Time& b);
	friend bool operator<=(const Time& a, const Time& b);
	friend bool operator==(const Time& a, const Time& b);
	friend bool operator!=(const Time& a, const Time& b);
};
#endif
