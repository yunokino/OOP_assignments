/*2152041 �ƿ� ����*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */

using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
/* ���廨ɫ */
#ifdef __linux//Linux
const char suit[4] = { 'H','D','C','S' };
#else
const char suit[4] = { '','','','' };
#endif
/* �����˿��Ƶ����� */
const char poker_content[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
const char special_poker[2][5] = { "BJ","RJ" };
/* ��������Լ���Ҫ�ĺ��� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	cout << prompt;
	for (int i = 0; i < 54; i++)
	{
		if (player >> i & (unsigned long long)(1))
		{
			if (i < 52)
			{
				cout << suit[i % 4];
				cout << poker_content[i / 4];
			}
			else
			{
				cout << special_poker[i % 4];
			}
			cout << " ";
		}
	}
	if (landlord)
		cout << "(����)";
	cout << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	srand(unsigned(time(NULL)));
	int poker_location;
	unsigned long long tmp = 1;
	for(int i = 0;i < 17;i++)
	{
		/* ÿ���ư��ִη��� */
		for (int j = 0; j < 3; j++)
		{
			while (1)
			{
				poker_location = rand() % 54;
				/* ��������û�б���������ô�˳� */
				if (!(( player[0] >> poker_location &tmp)| (player[1] >> poker_location & tmp)
					| (player[2] >> poker_location & tmp)))
					break;
			}
			player[j] |= tmp << poker_location;
		}
		cout << "��"<<i + 1<<"�ֽ�����" << endl;
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 0, player[1]);
		print("�����ƣ�", 0, player[2]);
	}
	/* ������� */
	int landlord;
	cout << "��ѡ��һ������[0-2]��" << endl;
	while (1)
	{
		cin >> landlord;
		if (cin.fail() || landlord < 0 || landlord > 2)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		break;
	}
	for (int i = 0; i < 54; i++)
	{
		if (!((player[0] >> i & tmp) | (player[1] >> i & tmp) 
			| (player[2] >> i & tmp)))
			player[landlord] |= tmp << i;
	}
	return landlord; //�˴��޸�Ϊѡ���ĵ���(0-2)
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", (landlord == 0), player[0]);
	print("�ҵ��ƣ�", (landlord == 1), player[1]);
	print("�����ƣ�", (landlord == 2), player[2]);

	return 0;
}
