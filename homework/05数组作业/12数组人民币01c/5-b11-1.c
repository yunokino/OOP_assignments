/* 2152041 ���� ��07 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
//�ɰ���������Ҫ��ͷ�ļ�

const char chnstr[] = "��Ҽ��������½��ƾ�ʰ"; /* ���������д "��" ~ "��" �ĵط���ֻ��������������ȡֵ */
char result[256];  /* ��result�⣬�����������κ���ʽ��ȫ�ֱ��� */

/* --���������Ҫ�ĺ��� --*/
void daxie(int num, int flag_of_zero)
{
	switch (num) {
		case 0:
			if (flag_of_zero)
				strncat(result,&chnstr[0],2);
			else
				strcat(result, "");
			break;
		case 1:
			strncat(result, &chnstr[2],2);
			break;
		case 2:
			strncat(result, &chnstr[4], 2);
			break;
		case 3:
			strncat(result, &chnstr[6], 2);
			break;
		case 4:
			strncat(result, &chnstr[8], 2);
			break;
		case 5:
			strncat(result, &chnstr[10], 2);
			break;
		case 6:
			strncat(result, &chnstr[12], 2);
			break;
		case 7:
			strncat(result, &chnstr[14], 2);
			break;
		case 8:
			strncat(result, &chnstr[16], 2);
			break;
		case 9:
			strncat(result, &chnstr[18], 2);
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
	printf("������[0-100��)֮�������:\n");
	scanf("%lf", &a);
	i = (int)(a / 10);
	b = a / 10 - i + 0.0001;
	c = (int)((i - (int)(i / 10000000) * 10000000) / 1000);//��λ�ϵ���λ����
	printf("��д�����:\n");
	daxie(i / 100000000 % 10, 0);
	if (i / 100000000 % 10 != 0)
		strcat(result, "ʰ");
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		strcat(result, "��");
	daxie(i / 10000000 % 10, (i - (int)(i / 10000000) * 10000000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (i / 1000000 % 10 == 0 ? i / 100000000 % 10 : 0));
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 != 0)
		strcat(result, "��");
	if (i / 100000000 % 10 == 0 && i / 10000000 % 10 != 0)
		strcat(result, "��");
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		strcat(result, "");
	daxie(i / 1000000 % 10, ((i - (int)(i / 1000000) * 1000000) == 0 && (int)(10 * b) % 10 == 0) ? 0 : ((c == 0 && i / 100 % 10 != 0) ? 0 : i / 10000000 % 10));
	if (i / 1000000 % 10 != 0)
		strcat(result, "Ǫ");
	if (i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 1000000 % 10 != 0)
		strcat(result, "��");
	daxie(i / 100000 % 10, (i - (int)(i / 100000) * 100000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 1000) * 1000 == 0 ? 0 : i / 1000000 % 10));
	if (i / 100000 % 10 != 0)
		strcat(result, "��");
	if (i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100000 % 10 != 0)
		strcat(result, "��");
	daxie(i / 10000 % 10, (i - (int)(i / 10000) * 10000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 100) * 100 == 0 ? 0 : i / 100000 % 10));
	if (i / 10000 % 10 != 0)
		strcat(result, "ʰ");
	if (i / 1000 % 10 == 0 && i / 10000 % 10 != 0)
		strcat(result, "��");
	daxie(i / 1000 % 10, (i - (int)(i / 1000) * 1000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 10) * 10 == 0 ? 0 : i / 10000 % 10));
	if (i / 1000 % 10 != 0)
		strcat(result, "��");
	daxie(i / 100 % 10, (i - (int)(i / 100) * 100) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c == 0 ? 0 : 1));
	if (i / 100 % 10 != 0)
		strcat(result, "Ǫ");
	daxie(i / 10 % 10, (i - (int)(i / 10) * 10) == 0 && (int)(10 * b) % 10 == 0 ? 0 : i / 100 % 10);
	if (i / 10 % 10 != 0)
		strcat(result, "��");
	daxie(i % 10, (i - (int)(i)) == 0 && (int)(10 * b) % 10 == 0 ? 0 : i / 10 % 10);
	if (i % 10 != 0)
		strcat(result, "ʰ");
	daxie((int)(10 * b) % 10, a == 0 ? 1 : 0);
	if (i != 0 || (int)(10 * b) % 10 != 0 || a == 0)
		strcat(result, "Բ");
	if ((i != 0 || (int)(10 * b) % 10 != 0) && (int)(100 * b) % 10 == 0 && (int)(1000 * b) % 10 == 0)
		strcat(result, "��");
	if (a == 0)
		strcat(result, "��");
	daxie((int)(100 * b) % 10, ((i != 0 || (int)(10 * b) % 10 != 0) && (int)(1000 * b) % 10));
	if ((int)(100 * b) % 10 != 0 && (int)(1000 * b) % 10 == 0)
		strcat(result, "����");
	else if ((int)(100 * b) % 10 != 0 && (int)(1000 * b) % 10 != 0)
		strcat(result, "��");
	daxie((int)(1000 * b) % 10, 0);
	if ((int)(1000 * b) % 10 != 0)
		strcat(result, "��");


	printf("%s\n", result);  /* ת���õ��Ĵ�д�����ֻ�����ñ���������֮ǰ�������κ���ʽ�Ĳ������ */
	return 0;
}
