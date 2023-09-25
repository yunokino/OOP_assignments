/* 2152041 ���� ��07 */

/* ���������ϵͳ�ĺ궨�塢��Ҫ��ͷ�ļ��� */
#include <iostream>
#include<iomanip>
#include <fstream>
#include<cstring>
using namespace std;

#define MAX_STU_NUM			256	//Լ���������Ϊ256�ˣ����ֵ��ܺͣ�������ѡ����ѡ��
#define MAX_NAME_LEN			32	//ѧ����������󳤶Ȳ�����16������
#define MAX_FILENAME_LEN		256	//�ļ�������󳤶�

/* stu_info ����ÿ��ѧ������Ϣ������ѧ�š�������������Ҫ��˽����Ϣ���������ݲ�׼�����ɼ����������Ҫ��������� */
class stu_list;
class stu_info {
private:
	int  stu_no;			//ѧ��
	char stu_name[MAX_NAME_LEN];	//����
	int  second_stu_no;			//ѧ��
	char second_stu_name[MAX_NAME_LEN];
	char in_class;
	char second_in_class[10];
	friend class stu_list;
	/* ���������private���ݳ�Ա����Ա�����Լ�������Ҫ������ */

public:
	/* ���಻�������κεĹ������ݳ�Ա����Ա���� */
};

/* stu_list ������ѡ����Ϣ���������ݲ�׼�����ɼ����������Ҫ��������� */
class stu_list {
private:
	stu_info stu[MAX_STU_NUM + 1];
	int number;

	/* ���������private���ݳ�Ա�ͳ�Ա���� */

public:
	int read(const char* filename, const int append = 0);	//���ļ��ж���ѡ����Ϣ�����д�����2������ֵΪ0��ʾ���Ƿ�ʽ��1��ʾ׷�ӷ�ʽ
	int print(const char* prompt = NULL);		//��ӡ��ǰ�����ѡ������
	/* �������������public��Ա���� */
	int first_judge(int i, int number, int* a)
	{
		int is_in = 0;
		for (int k = 0; k <= number-1; k++)
		{
			if (stu[i].second_stu_no == stu[k].stu_no) {
				(*a) = k;
				is_in = 1;
				break;
			}
		}
		return is_in;
	}
	int second_judge(int j, int i)
	{
		int n, is_in = 0;
		for (n = 0; n < i; n++)
		{
			if (stu[n].second_stu_no == stu[j].stu_no) {
				is_in = 1;
				break;
			}
		}
		return is_in;
	}
};
int stu_list::read(const char* filename, const int append)
{
	int i,j, a;
	if (append == 0)
		number = 0;
	ifstream infile(filename, ios::in);
	if (!infile.is_open())
	{
		cout << "�����ļ�" << filename << "��ʧ��!" << endl;
		infile.close();
	}
	else
	{
		if (append == 0) {
			for (;!infile.eof(); number++)
			{
				infile >> stu[number].stu_no;
				infile >> stu[number].stu_name;
				stu[number].in_class = 'Y';
			}

		}
		else {
			number--;
			for (i = 0; !infile.eof(); i++)
			{
				infile >> stu[i].second_stu_no;
				infile >> stu[i].second_stu_name;
				if (first_judge(i, number, &a) == 0 && stu[i].second_stu_no > 0)
				{
					stu[number].stu_no = stu[i].second_stu_no;
					strcpy_s(stu[number].stu_name, stu[i].second_stu_name);
					stu[number].in_class = '/';
					strcpy_s(stu[number].second_in_class, "��ѡ");
					number++;
				}
				else if (first_judge(i, number, &a) == 1 && stu[i].second_stu_no > 0)
					strcpy_s(stu[a].second_in_class, "Y");
				else;
			}
			for (j = 0; j <= number-1; j++)
			{
				if (second_judge(j, i) == 0)
					strcpy_s(stu[j].second_in_class, "�˿�");
				else if (second_judge(j, i) == 1 && stu[j].in_class != '/')
					strcpy_s(stu[j].second_in_class, "Y");
				else;
			}
		}
	}
	if (append == 1) {
		int t;
		char name[40];
		char state;
		char first[10];
		for (int i = 0;i < number - 1; i++) {
			for (int j = 0; j < number - (i + 1); j++) 
			{
				if (stu[j].stu_no > stu[j + 1].stu_no)
				{
					t = stu[j].stu_no;
					stu[j].stu_no = stu[j + 1].stu_no;
					stu[j + 1].stu_no = t;
					strcpy_s(name, stu[j].stu_name);
					strcpy_s(stu[j].stu_name, stu[j + 1].stu_name);
					strcpy_s(stu[j + 1].stu_name, name);
					state = stu[j].in_class;
					stu[j].in_class = stu[j + 1].in_class;
					stu[j + 1].in_class = state;
					strcpy_s(first, stu[j].second_in_class);
					strcpy_s(stu[j].second_in_class, stu[j + 1].second_in_class);
					strcpy_s(stu[j + 1].second_in_class, first);
				}
			}
		}
	}
	return 0;
}

int stu_list::print(const char* prompt)
{
	cout << prompt << endl;
	cout << "===========================================================" << endl;
	cout << "��� ѧ��    ����                             ��һ�� �ڶ���" << endl;
	cout << "===========================================================" << endl;
	for (int k = 0; k <= number - 1; k++)
	{
		cout << left << setw(5) << k + 1;
		cout << stu[k].stu_no << " ";
		cout << setw(10) <<stu[k].stu_name<< "                       ";
		cout << stu[k].in_class << "      ";
		cout << stu[k].second_in_class << endl;
	}
	cout << "===========================================================" << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	char file1[MAX_FILENAME_LEN], file2[MAX_FILENAME_LEN];

	cout << "������ǰһ��ѡ�ε������ļ� : ";
	cin >> file1;
	cout << "�������һ��ѡ�ε������ļ� : ";
	cin >> file2;

	stu_list list;

	/* �����һ�������ļ� */
	if (list.read(file1) < 0)
		return -1;

	/* ����ڶ��������ļ�������2��ֵΪ1��ʾ׷�ӷ�ʽ */
	if (list.read(file2, 1) < 0)
		return -1;

	list.print("����ѡ������");

	return 0;
}