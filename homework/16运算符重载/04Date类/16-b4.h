/* 2152041 计科 王浩 */


#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int compute_year(int past_days);
int compute_month(int past_days);
int compute_day(int past_days);
int trans_to_days(int year, int month, int day);
void check_range(int& year, int& month, int &day);
void check_days(const int past_days, int& year, int& month, int& day);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	/* 构造函数 */
	Date();
	Date(const int y, const int m, const int d);
	/* 更改与展示函数 */
	void set(const int y, const int m, const int d);
	void set(const int y, const int m);
	void set(const int y);
	void get(int &y, int &m, int &d);
	void show();
	/* 转换构造与类型转换函数 */
	Date(const int past_days);
	operator int const();
	/* +、-重载函数 */
	friend Date operator+(const int past_days, const Date &a);
	friend Date operator+(const Date &a, const int past_days);
	friend Date operator-(const Date &a, const int past_days);
	friend int operator-(const Date &a, const Date& b);
	/* ++、--重载函数 */
	Date operator ++();//前置型
	Date operator ++(int);//后置型
	Date operator --();//前置型
	Date operator --(int);//后置型
	/* 标准输出输入cout、cin重载 */
	friend ostream& operator<<(ostream& out, const Date& a);
	friend istream& operator>>(istream& in, Date& a);
	/* 六个比较运算符重载 */
	friend bool operator>(const Date& a, const Date& b);
	friend bool operator<(const Date& a, const Date& b);
	friend bool operator>=(const Date& a, const Date& b);
	friend bool operator<=(const Date& a, const Date& b);
	friend bool operator==(const Date& a, const Date& b);
	friend bool operator!=(const Date& a, const Date& b);
};

