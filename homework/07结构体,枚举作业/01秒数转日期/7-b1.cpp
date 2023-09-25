/* 2152041 ���� ��07 */
#define _CRT_SECURE_NO_WARNINGS		//ʹ����VS��Ϊunsafe�ĺ���
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <conio.h>	//��getch����˲���Ҫ֧��Linux
#include <string.h>	//Dev/CB��strlen��Ҫ
using namespace std;

struct tj_time {
	int tj_year;	//��ʾ���
	int tj_month;	//��ʾ��(1-12)
	int tj_day;	//��ʾ��(1-28/29/30/31)
	int tj_hour;	//��ʾСʱ(0-23)
	int tj_minute;	//��ʾ��(0-59)
	int tj_second;	//��ʾ��(0-59)
};

/* �����ڴ˶���������Ҫ�ĺ��� */


/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʾ���ȴ��س���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter(const char* const prompt = NULL)
{
	if ((prompt == NULL) || (strlen(prompt) == 0)) //˼��һ�£�||���������������ܷ񻥻�
		cout << endl << "���س�������";
	else
		cout << endl << prompt << "�����س�������";

	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ϵͳ��ת��������������ֵת��Ϊ�뱾�����ƵĽṹ�岢���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void system_time_output(const time_t input_time)  //time_t�ı�����64λ�޷�������
{
	struct tm* tt;	//struct tm Ϊϵͳ����Ľṹ��

	tt = localtime(&input_time);	//localtimeΪϵͳ����

	/* tm_*** Ϊstruct tm�еĳ�Ա���ͱ����struct tj_time��������ݲ���ȫ���ϣ����庬���Լ������������ */
	cout << setfill('0') << setw(4) << tt->tm_year + 1900 << '-'
		<< setw(2) << tt->tm_mon + 1 << '-'
		<< setw(2) << tt->tm_mday << ' '
		<< setw(2) << tt->tm_hour << ':'
		<< setw(2) << tt->tm_min << ':'
		<< setw(2) << tt->tm_sec << endl;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Զ���ת������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void tj_time_output(const struct tj_time* const tp)
{
	/* ʵ���Զ���ṹ������������ʽ��system_time_output��ͬ */
	cout << setfill('0') << setw(4) << tp->tj_year << '-'
		<< setw(2) << tp->tj_month << '-'
		<< setw(2) << tp->tj_day << ' '
		<< setw(2) << tp->tj_hour << ':'
		<< setw(2) << tp->tj_minute << ':'
		<< setw(2) << tp->tj_second << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��Զ���ת������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
struct tj_time* tj_time_convert(int input_time)
{
	static struct tj_time result;	//���徲̬�ֲ���������׼��

	/* ʵ�ֹ��̿�ʼ�������������Ӧ�Ķ��弰ִ����伴�� */
	input_time += 28800;
	result = { 1970,1,1,0,0 };
	int trans_year = input_time;
	while (1)
	{
		if (((result.tj_year % 4 == 0 && result.tj_year % 100 != 0) || result.tj_year % 400 == 0) && trans_year >= 31622400)
		{
			trans_year -= 31622400;
			result.tj_year++;
		}
		else if (!((result.tj_year % 4 == 0 && result.tj_year % 100 != 0) || result.tj_year % 400 == 0) && trans_year >= 31536000)
		{
			trans_year -= 31536000;
			result.tj_year++;
		}
		else
			break;
	}
	result.tj_day += input_time / 86400;
	int start_year = 1970;
	while (start_year != result.tj_year)
	{
		if ((start_year % 4 == 0 && start_year % 100 != 0) || start_year % 400 == 0)
			result.tj_day -= 366;
		else
			result.tj_day -= 365;
		start_year++;
	}
	while (1)
	{
		if (result.tj_month == 1 || result.tj_month == 3 || result.tj_month == 5 || result.tj_month == 7 || result.tj_month == 8 || result.tj_month == 10 || result.tj_month == 12)
		{
			if (result.tj_day > 31)
			{
				result.tj_day -= 31;
				result.tj_month++;
			}
			else
				break;
		}
		else if (result.tj_month == 4 || result.tj_month == 6 || result.tj_month == 9 || result.tj_month == 11)
		{
			if (result.tj_day > 30)
			{
				result.tj_day -= 30;
				result.tj_month++;
			}
			else
				break;
		}
		else if (result.tj_month == 2)
		{
			if (((start_year % 4 == 0 && start_year % 100 != 0) || start_year % 400 == 0) && result.tj_day > 29)
			{
				result.tj_day -= 29;
				result.tj_month++;
			}
			else if (!((start_year % 4 == 0 && start_year % 100 != 0) || start_year % 400 == 0) && result.tj_day > 28)
			{
				result.tj_day -= 28;
				result.tj_month++;
			}
			else
				break;
		}
		else
			break;
	}
	result.tj_hour += (input_time / 3600) % 24;
	result.tj_minute += (input_time / 60) % 60;
	result.tj_second += input_time % 60;
	/* ʵ�ֹ��̽��� */

	return &result;	//ע�⣬���ص��Ǿ�̬�ֲ������ĵ�ַ������䲻׼��
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int read_time;
	struct tj_time* tp;

	for (;;) {
		cin >> read_time; //��Ϊ���������ض��򣬴˴������κ���ʾ

		/* ��������<0���˳�ѭ�� */
		if (cin.good() == 0 || read_time < 0)
			break;

		cout << "����             : " << read_time << endl;
		cout << "ϵͳת���Ľ��   : ";
		system_time_output(read_time);

		cout << "�Զ���ת���Ľ�� : ";
		tp = tj_time_convert(read_time);
		tj_time_output(tp);

		wait_for_enter();
	}

	if (1) {
		struct tj_time* tp;
		int t = (int)time(0);		//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ��������

		cout << "��ǰϵͳʱ��     : " << t << endl;
		cout << "ϵͳת���Ľ��   : ";
		system_time_output(t);

		cout << "�Զ���ת���Ľ�� : ";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		wait_for_enter();
	}

	return 0;
}