/* 2152041 ���� ��07 */
#include <iostream>
#include <iomanip>
using namespace std;

/* ----����Ҫ��----
   1���������������ͷ�ļ�
   2����������ȫ�ֱ�������̬�ֲ�����
   3������������������������ʼ/Ŀ�����ĺ���������������ʹ��ѭ�������������
   4����������ú������У���main�в���������κ���ʽ��ѭ��
	  ���������main�н��У���main���������ѭ��
   --------------------------------------------------------------------- */
void move(int n, char x, char y)
{
	cout << setw(2) << n << "# " << x << "-->" << y << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡn�㺺ŵ�����ƶ�˳��
  ���������int n������
			char src����ʼ��
			char tmp���м���
			char dst��Ŀ����
  �� �� ֵ��
  ˵    ����1�����������βΡ��������;���׼��
			2������������������κ���ʽ��ѭ��
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
	if (n == 1)
	{
		move(1, src, dst);
	}
	else
	{
		hanoi(n - 1, src, dst, tmp);
		move(n, src, dst);
		hanoi(n - 1, tmp, src, dst);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����������(��������뺯��)�����õݹ麯��
***************************************************************************/
int main()
{
	int x;
	char f, g, h;
	g = '0';

	while (1) {
		cout << "�����뺺ŵ���Ĳ���(1-16)\n";
		cin >> x;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (x >= 1 && x <= 16)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "��������ʼ��(A-C)\n";
		cin >> f;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (f == 'a' || f == 'b' || f == 'c' || f == 'A' || f == 'B' || f == 'C')
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "������Ŀ����(A-C)\n";
		cin >> h;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if ((int)f == (int)h || (int)f == (int)h - 32 || (int)f == (int)h + 32)
		{
			h = (int(h) > 90) ? char(int(h) - 32) : h;
			f = (int(f) > 90) ? char(int(f) - 32) : f;
			cout << "Ŀ����(" << h << ")��������ʼ��(" << f << ")��ͬ\n";
			cin.ignore(65536, '\n');
			continue;
		}
		else if ((h == 'a' || h == 'b' || h == 'c' || h == 'A' || h == 'B' || h == 'C'))
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	bool _1, _2, _3;
	_1 = _2 = _3 = 1;
	switch (int(f))
	{
		case 65:
		case 97:
			_1 = 0;
			f = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			f = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			f = 'C';
			break;
	}
	switch (int(h))
	{
		case 65:
		case 97:
			_1 = 0;
			h = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			h = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			h = 'C';
			break;
	}
	if (_1)
		g = 'A';
	if (_2)
		g = 'B';
	if (_3)
		g = 'C';
	cout << "�ƶ�����Ϊ:\n";
	hanoi(x, f, g, h);
	return 0;
}