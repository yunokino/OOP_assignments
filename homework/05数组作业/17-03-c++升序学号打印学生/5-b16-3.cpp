/* 2152041 ���� ��07 */
#include <iostream>
#include<string>
using namespace std;

void in_put(string sch_num[], string name[], int score[])
{
	for (int i = 0; i <= 9; i++)
	{
		cout << "�������" << i + 1 << "���˵�ѧ�š��������ɼ�\n";
		cin >> sch_num[i] >> name[i] >> score[i];
	}
}
void sort_order(string sch_num[], string name[], int score[])
{
	int t;
	string n;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8 - i; j++)
		{
			if (sch_num[j]>sch_num[j + 1])
			{
				t = score[j];
				score[j] = score[j + 1];
				score[j + 1] = t;
				n = sch_num[j];
				sch_num[j] = sch_num[j + 1];
				sch_num[j + 1] = n;
				n = name[j];
				name[j] = name[j + 1];
				name[j + 1] = n;
			}
		}
}
void out_put(string sch_num[], string name[], int score[])
{
	cout << "\nȫ��ѧ��(ѧ������):\n";
	for (int i = 0; i <= 9; i++)
		cout << name[i] << " " << sch_num[i] << " " << score[i] << endl;
}

int main()
{
	string school_num[10];
	string name[10];
	int score[10];
	in_put(school_num, name, score);
	sort_order(school_num, name, score);
	out_put(school_num, name, score);

	return 0;
}
