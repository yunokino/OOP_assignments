/* 2152041 ���� ��07 */
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

/* -----------------------------------------------------------------------------------
		����   ��1����������һ�����������������������ӵĺ����в������κ���ʽ��ѭ��
				 2��������ų���
				 3������const�ͱ���

		������ ��1������ȫ�ֱ���
   ----------------------------------------------------------------------------------- */

int print_dash(char ch)
{
	int a = (int)(ch);
	return ((a - 64) * 2 - 1);
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void fun1(int n, int i);
void fun2(int m, int j);
void fun3(int i, int j);
void fun4(int m, int j);
void fun5(int n, int i);

void print_diamond(char start_ch, char end_ch)
{
	/* ����ʵ�֣������в������κ���ʽ��ѭ�����������徲̬�ֲ����� */
	fun1((int)(end_ch)-64, 1);
	fun5((int)(end_ch)-64, (int)(end_ch)-65);
}

void fun1(int n, int i)
{
	if (n - i >= 0)
	{
		fun2(n - i, 1);
		fun3(i, i);
		fun4(i - 1, 1);
		cout << endl;
		fun1(n, i + 1);
	}
}
void fun2(int m, int j)
{
	if (m - j >= 0)
	{
		cout << " ";
		fun2(m, j + 1);
	}
}
void fun3(int i, int j)
{
	if (i > 0)
	{
		cout << char(j + 64);
		j--;
		fun3(i - 1, j);
	}
}
void fun4(int m, int j)
{
	if (m > 0)
	{
		cout << char(j + 65);
		j++;
		fun4(m - 1, j);
	}
}

void fun5(int n, int i)
{
	if (i >= 1)
	{
		fun2(n - i, 1);
		fun3(i, i);
		fun4(i - 1, 1);
		if (i >= 1)
			cout << endl;
		fun5(n, i - 1);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main����������...�����޸ģ�����λ�ò�׼�޸�
***************************************************************************/
int main()
{
	char end_ch;

	/* ������������ַ�(����д��Ч) */
	cout << "����������ַ�(A~Z)" << endl;
	end_ch = getchar();

	/* ����(�м�ΪA) */
	cout << setw(print_dash(end_ch)) << setfill('=') << '=' << endl; /* ��������������=(��������ѭ��) */
	cout << "����(" << end_ch << "->A)" << endl;
	cout << setw(print_dash(end_ch)) << setfill('=') << '=' << endl; /* ��������������=(��������ѭ��) */
	print_diamond('A', end_ch);
	cout << endl;

	return 0;
}