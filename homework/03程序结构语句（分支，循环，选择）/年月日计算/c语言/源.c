/*���� ��07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
	int a, b, c;
	printf("�������꣬�£���\n");
	scanf("%d%d%d",&a,&b,&c);
	if (a % 4 == 0)                    //���ж��Ƿ������꣬�������յ�˳�������з�֧
	{
		if (b > 12 || b < 1)
		{
			printf( "�������-�·ݲ���ȷ\n");
		}
		else
		{
			if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
			{
				if (c > 31 || c < 1)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
			}
			else if (b == 2)
			{
				if (c > 29 || c < 10)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
			}
			else
			{
				if (c > 30 || c < 1)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
			}
			switch (b)
			{
				case 1:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c);
					break;
				case 2:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+31);
					break;
				case 3:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+60);
					break;
				case 4:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+91);
					break;
				case 5:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+121);
					break;
				case 6:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+152);
					break;
				case 7:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+182);
					break;
				case 8:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+213);
					break;
				case 9:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+244);
					break;
				case 10:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+274);
					break;
				case 11:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+305);
					break;
				case 12:
					printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c+335);
					break;
			}
		}
	}
	if (a % 4 != 0)
	{
		if (b > 12 || b < 1)
		{
			printf(  "�������-�·ݲ���ȷ\n");
		}
		else
		{
			if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
			{
				if (c > 31 || c < 1)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
				else
					switch (b)
					{
						case 1:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c);
							break;
						case 2:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 31);
							break;
						case 3:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 59);
							break;
						case 4:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 90);
							break;
						case 5:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 120);
							break;
						case 6:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 151);
							break;
						case 7:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 181);
							break;
						case 8:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 212);
							break;
						case 9:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 243);
							break;
						case 10:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 273);
							break;
						case 11:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 304);
							break;
						case 12:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 334);
							break;
					}
			}
			else if (b == 2)
			{
				if (c > 28 || c < 10)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
				else
					switch (b)
					{
						case 1:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c);
							break;
						case 2:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 31);
							break;
						case 3:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 59);
							break;
						case 4:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 90);
							break;
						case 5:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 120);
							break;
						case 6:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 151);
							break;
						case 7:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 181);
							break;
						case 8:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 212);
							break;
						case 9:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 243);
							break;
						case 10:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 273);
							break;
						case 11:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 304);
							break;
						case 12:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 334);
							break;
					}
			}
			else
			{
				if (c > 30 || c < 1)
					printf(  "�������-�����µĹ�ϵ�Ƿ�\n");
				else
					switch (b)
					{
						case 1:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c);
							break;
						case 2:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 31);
							break;
						case 3:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 59);
							break;
						case 4:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 90);
							break;
						case 5:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 120);
							break;
						case 6:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 151);
							break;
						case 7:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 181);
							break;
						case 8:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 212);
							break;
						case 9:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 243);
							break;
						case 10:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 273);
							break;
						case 11:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 304);
							break;
						case 12:
							printf("%d-%d-%d��%d��ĵ�%d��\n", a, b, c, a, c + 334);
							break;
					}
			}
		
		}
	}
	return 0;
}
