/*���� ��07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double a, b;
	int i;
	printf("������[0-100�ڣ�֮�������\n");
	scanf("%lf", &a);
	i = (int)(a / 10);
	b = a / 10 - i + 0.0001;
	printf("��д�����:\n");
	switch (i / 100000000 % 10)//����ʮ�ڣ���λ�Ķ���
	{
		case 0:
			printf("");
			break;
		case 1:
			printf("Ҽʰ");
			break;
		case 2:
			printf("��ʰ");
			break;
		case 3:
			printf("��ʰ");
			break;
		case 4:
			printf("��ʰ");
			break;
		case 5:
			printf("��ʰ");
			break;
		case 6:
			printf("½ʰ");
			break;
		case 7:
			printf("��ʰ");
			break;
		case 8:
			printf("��ʰ");
			break;
		case 9:
			printf("��ʰ");
			break;
	}
	switch (i / 10000000 % 10)
	{
		case 0:
			(i / 100000000 % 10 == 0) ? printf("") : printf("��");
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("����");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("����");
			break;
		case 8:
			printf("����");
			break;
		case 9:
			printf("����");
			break;
	}
	switch (i / 1000000 % 10)//������λ����λ�Ķ�ȡ
	{
		case 0:
			printf(((i / 10000000 % 10 == 0) ? "" : ((i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? "" : ((i / 10000000 % 10 == 0) ? "" : "��"))));//�������ȫ���㲻���������
			break;
		case 1:
			printf("ҼǪ");
			break;
		case 2:
			printf("��Ǫ");
			break;
		case 3:
			printf("��Ǫ");
			break;
		case 4:
			printf("��Ǫ");
			break;
		case 5:
			printf("��Ǫ");
			break;
		case 6:
			printf("½Ǫ");
			break;
		case 7:
			printf("��Ǫ");
			break;
		case 8:
			printf("��Ǫ");
			break;
		case 9:
			printf("��Ǫ");
			break;
	}
	switch (i / 100000 % 10)
	{
		case 0:
			printf(((i / 1000000 % 10 == 0) ? "" : (i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? ((i / 100 % 10 == 0 && i / 10 % 10 == 0 && i % 10 == 0 && (int)(10 * b) % 10 == 0) ? "" : "��") : "��"));
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("���");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("���");
			break;
		case 8:
			printf("�ư�");
			break;
		case 9:
			printf("����");
			break;
	}
	switch (i / 10000 % 10)
	{
		case 0:
			if (i / 100000 % 10 == 0)
				printf( "");
			else
			{
				if (i / 1000 % 10 == 0)
					printf( "");
				else
					printf( "��");
			}

			break;
		case 1:
			printf("Ҽʰ");
			break;
		case 2:
			printf("��ʰ");
			break;
		case 3:
			printf("��ʰ");
			break;
		case 4:
			printf("��ʰ");
			break;
		case 5:
			printf("��ʰ");
			break;
		case 6:
			printf("½ʰ");
			break;
		case 7:
			printf("��ʰ");
			break;
		case 8:
			printf("��ʰ");
			break;
		case 9:
			printf("��ʰ");
			break;
	}
	switch (i / 1000 % 10)
	{
		case 0:
			if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
				printf("");
			else
				printf("��");
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("����");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("����");
			break;
		case 8:
			printf("����");
			break;
		case 9:
			printf("����");
			break;
	}
	switch (i / 100 % 10)//������λ���µĶ�ȡ
	{
		case 0:
			if (i / 1000 % 10 == 0)
			{
				if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
					printf("");
				else
				{
					if (i / 10 % 10 == 0 && i % 10 == 0 && (int)(10 * b) % 10 == 0)
						printf("");
					else
						printf("��");
				}
            }
			break;
		case 1:
			printf("ҼǪ");
			break;
		case 2:
			printf("��Ǫ");
			break;
		case 3:
			printf("��Ǫ");
			break;
		case 4:
			printf("��Ǫ");
			break;
		case 5:
			printf("��Ǫ");
			break;
		case 6:
			printf("½Ǫ");
			break;
		case 7:
			printf("��Ǫ");
			break;
		case 8:
			printf("��Ǫ");
			break;
		case 9:
			printf("��Ǫ");
			break;
	}
	switch (i / 10 % 10)
	{
		case 0:
			printf(((i / 100 % 10 == 0) ? (i % 10 == 0 ? "" : ((i / 100000000 % 10 == 0 && i / 10000000 % 10 == 0 && i / 1000000 % 10 == 0 && i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100 % 10 == 0 ? "" : "��"))) : ""));
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("���");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("���");
			break;
		case 8:
			printf("�ư�");
			break;
		case 9:
			printf("����");
			break;
	}
	switch (i % 10)
	{
		case 0:
			printf(((i / 10 % 10 == 0) ? ((i / 100000000 % 10 == 0 && i / 10000000 % 10 == 0 && i / 1000000 % 10 == 0 && i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 == 0 && i / 100 == 0 ? "" : ((int)(10 * b) % 10 == 0 ? "" : "��"))) : ((int)(10 * b) % 10 == 0 ? "" : "��")));
			break;
		case 1:
			printf("Ҽʰ");
			break;
		case 2:
			printf("��ʰ");
			break;
		case 3:
			printf("��ʰ");
			break;
		case 4:
			printf("��ʰ");
			break;
		case 5:
			printf("��ʰ");
			break;
		case 6:
			printf("½ʰ");
			break;
		case 7:
			printf("��ʰ");
			break;
		case 8:
			printf("��ʰ");
			break;
		case 9:
			printf("��ʰ");
			break;
	}
	switch ((int)(10 * b) % 10)
	{
		case 0:
			if ((int)(a) == 0)
			{
				printf("");
			}
			else
				printf("Բ");
			break;
		case 1:
			printf("ҼԲ");
			break;
		case 2:
			printf("��Բ");
			break;
		case 3:
			printf("��Բ");
			break;
		case 4:
			printf("��Բ");
			break;
		case 5:
			printf("��Բ");
			break;
		case 6:
			printf("½Բ");
			break;
		case 7:
			printf("��Բ");
			break;
		case 8:
			printf("��Բ");
			break;
		case 9:
			printf("��Բ");
			break;
	}
	switch ((int)(100 * b) % 10)
	{
		case 0:
			((int)(1000 * b) % 10 == 0) ? printf("��") : printf((int)(a) == 0 ? "" : "��");
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("���");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("���");
			break;
		case 8:
			printf("�ƽ�");
			break;
		case 9:
			printf("����");
			break;
	}
	switch ((int)(1000 * b) % 10)
	{
		case 0:
			((int)(100 * b) % 10 == 0) ? printf("") : printf("��");
			break;
		case 1:
			printf("Ҽ��");
			break;
		case 2:
			printf("����");
			break;
		case 3:
			printf("����");
			break;
		case 4:
			printf("����");
			break;
		case 5:
			printf("���");
			break;
		case 6:
			printf("½��");
			break;
		case 7:
			printf("���");
			break;
		case 8:
			printf("�Ʒ�");
			break;
		case 9:
			printf("����");
			break;
	}
	return 0;
}
