/* 2152041 �ƿ� ���� */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
#include "17-b2-time.h"
using namespace std;

#define Day_Seconds (long long)86400
void check_seconds(int& y, int& m, int& d, int& h, int& mi, int& s);
long long trans_to_seconds(const int y, const int m, const int d, const int h, const int mi, const int s);


class DateTime :public Date,public Time{
public:
	DateTime();
	DateTime(const DateTime& datetime);
	DateTime(const int y, const int m);
	DateTime(const int y, const int m, const int d);
	DateTime(const int y, const int m, const int d, const int h);
	DateTime(const int y, const int m, const int d, const int h, const int mi);
	DateTime(const int y, const int m, const int d, const int h, const int mi,const int s);
	/* ������չʾ���� */
	void set(const DateTime& datetime);
	void set();
	void set(const int y);
	void set(const int y, const int m);
	void set(const int y, const int m, const int d);
	void set(const int y, const int m, const int d, const int h);
	void set(const int y, const int m, const int d, const int h, const int mi);
	void set(const int y, const int m, const int d, const int h, const int mi, const int s);
	void get(int& y, int& m, int& d, int& h, int& mi, int &s);
	void show();
	/* ת������������ת������ */
	DateTime(const long long past_seconds);
	operator long long const();
	/* +��-���غ��� */
	friend DateTime operator+(const long long past_seconds, const DateTime& a);
	friend DateTime operator+(const DateTime& a, const long long past_seconds);
	friend DateTime operator-(const DateTime& a, const long long past_seconds);
	friend long long operator-(const DateTime& a, const DateTime& b);
	friend DateTime operator+(const int past_seconds, const DateTime& a);
	friend DateTime operator+(const DateTime& a, const int past_seconds);
	friend DateTime operator-(const DateTime& a, const int past_seconds);
	friend long long operator-(const DateTime& a, const DateTime& b);
	/* ++��--���غ��� */
	DateTime operator ++();//ǰ����
	DateTime operator ++(int);//������
	DateTime operator --();//ǰ����
	DateTime operator --(int);//������
	/* ��׼�������cout��cin���� */
	friend ostream& operator<<(ostream& out, const DateTime& a);
	friend istream& operator>>(istream& in, DateTime& a);
	/* �����Ƚ���������� */
	friend bool operator>(const DateTime& a, const DateTime& b);
	friend bool operator<(const DateTime& a, const DateTime& b);
	friend bool operator>=(const DateTime& a, const DateTime& b);
	friend bool operator<=(const DateTime& a, const DateTime& b);
	friend bool operator==(const DateTime& a, const DateTime& b);
	friend bool operator!=(const DateTime& a, const DateTime& b);
};
