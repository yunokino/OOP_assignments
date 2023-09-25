/* 2152041 �ƿ� ���� */


#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int compute_year(int past_days);
int compute_month(int past_days);
int compute_day(int past_days);
int trans_to_days(int year, int month, int day);
int check_days(const int past_days, int& year, int& month, int& day);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
#define MAX_DAYS 73049

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
#ifndef _CLASSDATE_
#define _CLASSDATE_
class Date {
protected:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
	/* ���캯�� */
	Date();
	Date(const int y, const int m);
	Date(const int y, const int m, const int d);
	/* ������չʾ���� */
	void set(const int y, const int m, const int d);
	void set(const int y, const int m);
	void set(const int y);
	void set(const Date& a);
	void get(int& y, int& m, int& d);
	void show();
	/* ת������������ת������ */
	Date(const int past_days);
	operator int const();
	/* +��-���غ��� */
	friend Date operator+(const int past_days, const Date& a);
	friend Date operator+(const Date& a, const int past_days);
	friend Date operator-(const Date& a, const int past_days);
	friend int operator-(const Date& a, const Date& b);
	/* ++��--���غ��� */
	Date operator ++();//ǰ����
	Date operator ++(int);//������
	Date operator --();//ǰ����
	Date operator --(int);//������
	/* ��׼�������cout��cin���� */
	friend ostream& operator<<(ostream& out, const Date& a);
	friend istream& operator>>(istream& in, Date& a);
	/* �����Ƚ���������� */
	friend bool operator>(const Date& a, const Date& b);
	friend bool operator<(const Date& a, const Date& b);
	friend bool operator>=(const Date& a, const Date& b);
	friend bool operator<=(const Date& a, const Date& b);
	friend bool operator==(const Date& a, const Date& b);
	friend bool operator!=(const Date& a, const Date& b);
};
#endif