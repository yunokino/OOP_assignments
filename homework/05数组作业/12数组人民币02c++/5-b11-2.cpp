/* 2152041 ���� ��07 */
#include <iostream>
#include <string>
#include <limits>
//�ɰ���������Ҫ��ͷ�ļ�
using namespace std;

const char chnstr[] = "��Ҽ��������½��ƾ�"; /* ���������д "��" ~ "��" �ĵط���ֻ��������������ȡֵ */
string result;  /* ��result�⣬�����������κ���ʽ��ȫ�ֱ��� */

/* --���������Ҫ�ĺ��� --*/
void daxie(int num, int flag_of_zero)
{
	switch (num) {
		case 0:
			if (flag_of_zero)
			{
				result += chnstr[0];
				result += chnstr[1];
			}
			else
				result += "";
			break;
		case 1:
			result += chnstr[2];
			result += chnstr[3];
			break;
		case 2:
			result += chnstr[4];
			result += chnstr[5];
			break;
		case 3:
			result += chnstr[6];
			result += chnstr[7];
			break;
		case 4:
			result += chnstr[8];
			result += chnstr[9];
			break;
		case 5:
			result += chnstr[10];
			result += chnstr[11];
			break;
		case 6:
			result += chnstr[12];
			result += chnstr[13];
			break;
		case 7:
			result += chnstr[14];
			result += chnstr[15];
			break;
		case 8:
			result += chnstr[16];
			result += chnstr[17];
			break;
		case 9:
			result += chnstr[18];
			result += chnstr[19];
			break;
		default:
			break;
	}
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
	/* --���������Ҫ������ --*/
	double a, b;
	int i, c;
	cout << "������[0-100��)֮�������:\n";
	cin >> a;
	i = int(a / 10);
	b = a / 10 - i + 0.0001;
	c = int((i - int(i / 10000000) * 10000000) / 1000);//��λ�ϵ���λ����
	cout << "��д�����:\n";
	daxie(i / 100000000 % 10, 0);
	if (i / 100000000 % 10 != 0)
		result += "ʰ";
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		result += "��";
	daxie(i / 10000000 % 10, (i - int(i / 10000000) * 10000000) == 0 && int(10 * b) % 10 == 0 ? 0 : (i / 1000000 % 10 == 0 ? i / 100000000 % 10 : 0));
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 != 0)
		result += "��";
	if (i / 100000000 % 10 == 0 && i / 10000000 % 10 != 0)
		result += "��";
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		result += "";
	daxie(i / 1000000 % 10, ((i - int(i / 1000000) * 1000000) == 0 && int(10 * b) % 10 == 0) ? 0 : ((c == 0 && i / 100 % 10 != 0) ? 0 : i / 10000000 % 10));
	if (i / 1000000 % 10 != 0)
		result += "Ǫ";
	if (i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 1000000 % 10 != 0)
		result += "��";
	daxie(i / 100000 % 10, (i - int(i / 100000) * 100000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 1000) * 1000 == 0 ? 0 : i / 1000000 % 10));
	if (i / 100000 % 10 != 0)
		result += "��";
	if (i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100000 % 10 != 0)
		result += "��";
	daxie(i / 10000 % 10, (i - int(i / 10000) * 10000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 100) * 100 == 0 ? 0 : i / 100000 % 10));
	if (i / 10000 % 10 != 0)
		result += "ʰ";
	if (i / 1000 % 10 == 0 && i / 10000 % 10 != 0)
		result += "��";
	daxie(i / 1000 % 10, (i - int(i / 1000) * 1000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 10) * 10 == 0 ? 0 : i / 10000 % 10));
	if (i / 1000 % 10 != 0)
		result += "��";
	daxie(i / 100 % 10, (i - int(i / 100) * 100) == 0 && int(10 * b) % 10 == 0 ? 0 : (c == 0 ? 0 : 1));
	if (i / 100 % 10 != 0)
		result += "Ǫ";
	daxie(i / 10 % 10, (i - int(i / 10) * 10) == 0 && int(10 * b) % 10 == 0 ? 0 : i / 100 % 10);
	if (i / 10 % 10 != 0)
		result += "��";
	daxie(i % 10, (i - int(i)) == 0 && int(10 * b) % 10 == 0 ? 0 : i / 10 % 10);
	if (i % 10 != 0)
		result += "ʰ";
	daxie(int(10 * b) % 10, a == 0 ? 1 : 0);
	if (i != 0 || int(10 * b) % 10 != 0 || a == 0)
		result += "Բ";
	if ((i != 0 || int(10 * b) % 10 != 0) && int(100 * b) % 10 == 0 && int(1000 * b) % 10 == 0)
		result += "��";
	if (a == 0)
		result += "��";
	daxie(int(100 * b) % 10, ((i != 0 || int(10 * b) % 10 != 0) && int(1000 * b) % 10));
	if (int(100 * b) % 10 != 0 && int(1000 * b) % 10 == 0)
		result += "����";
	else if (int(100 * b) % 10 != 0 && int(1000 * b) % 10 != 0)
		result += "��";
	daxie(int(1000 * b) % 10, 0);
	if (int(1000 * b) % 10 != 0)
		result += "��";

	cout << result << endl;  /* ת���õ��Ĵ�д�����ֻ�����ñ���������֮ǰ�������κ���ʽ�Ĳ������ */
	return 0;
}
