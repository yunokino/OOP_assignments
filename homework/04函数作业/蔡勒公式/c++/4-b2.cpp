/* 2152041 ���� ��07 */
#include <iostream>
#include <limits>
using namespace std;

int zeller(int y, int m, int d)
{
	int w;
	if (m == 1 || m == 2)
	{
		y -= 1;
		m += 12;
	}
	int a = int(y / 100);//���ǰ��λ
	int b = y - int(y / 100) * 100;//��ݺ���λ
	w = b + int(b / 4) + int(a / 4) - 2 * a + int(13 * (m + 1) / 5) + d - 1;
	while (w < 0)
	{
		w += 7;
	}
	return w % 7;
}

int main()
{
	int year, m, d;
	while (1)
	{
		cout << "��������[1900-2100]���¡��գ�\n";
		cin >> year >> m >> d;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����������������\n";
			continue;
		}
		else
		{
			if (year < 1900 || year > 2100)
			{
				cout << "��ݲ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if (m < 0 || m > 12)
			{
				cout << "�·ݲ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d < 0 || d>31))
			{
				cout << "�ղ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if ((m == 4 || m == 6 || m == 9 || m == 11) && (d < 0 || d>30))
			{
				cout << "�ղ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if ((m == 2) && (year % 4 == 0 ? (d < 0 || d>29) : (d < 0 || d>28)))
			{
				cout << "�ղ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else
				break;
		}
	}
	switch (zeller(year, m, d))
	{
		case 0:
			cout << "������";
			break;
		case 1:
			cout << "����һ";
			break;
		case 2:
			cout << "���ڶ�";
			break;
		case 3:
			cout << "������";
			break;
		case 4:
			cout << "������";
			break;
		case 5:
			cout << "������";
			break;
		case 6:
			cout << "������";
			break;
	}
	cout << endl;
	return 0;
}
