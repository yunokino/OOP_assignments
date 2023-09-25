/*ÍõºÆ ĞÅ07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double a, b;
	int i;
	printf("ÇëÊäÈë[0-100ÒÚ£©Ö®¼äµÄÊı×Ö\n");
	scanf("%lf", &a);
	i = (int)(a / 10);
	b = a / 10 - i + 0.0001;
	printf("´óĞ´½á¹ûÊÇ:\n");
	switch (i / 100000000 % 10)//´¦ÀíÊ®ÒÚ£¬ÒÚÎ»µÄ¶Á·¨
	{
		case 0:
			printf("");
			break;
		case 1:
			printf("Ò¼Ê°");
			break;
		case 2:
			printf("·¡Ê°");
			break;
		case 3:
			printf("ÈşÊ°");
			break;
		case 4:
			printf("ËÁÊ°");
			break;
		case 5:
			printf("ÎéÊ°");
			break;
		case 6:
			printf("Â½Ê°");
			break;
		case 7:
			printf("ÆâÊ°");
			break;
		case 8:
			printf("°ÆÊ°");
			break;
		case 9:
			printf("¾ÁÊ°");
			break;
	}
	switch (i / 10000000 % 10)
	{
		case 0:
			(i / 100000000 % 10 == 0) ? printf("") : printf("ÒÚ");
			break;
		case 1:
			printf("Ò¼ÒÚ");
			break;
		case 2:
			printf("·¡ÒÚ");
			break;
		case 3:
			printf("ÈşÒÚ");
			break;
		case 4:
			printf("ËÁÒÚ");
			break;
		case 5:
			printf("ÎéÒÚ");
			break;
		case 6:
			printf("Â½ÒÚ");
			break;
		case 7:
			printf("ÆâÒÚ");
			break;
		case 8:
			printf("°ÆÒÚ");
			break;
		case 9:
			printf("¾ÁÒÚ");
			break;
	}
	switch (i / 1000000 % 10)//´¦ÀíÍòÎ»ÖÁÒÚÎ»µÄ¶ÁÈ¡
	{
		case 0:
			printf(((i / 10000000 % 10 == 0) ? "" : ((i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? "" : ((i / 10000000 % 10 == 0) ? "" : "Áã"))));//´¦ÀíºóÃæÈ«ÊÇÁã²»Êä³öµÄÎÊÌâ
			break;
		case 1:
			printf("Ò¼Çª");
			break;
		case 2:
			printf("·¡Çª");
			break;
		case 3:
			printf("ÈşÇª");
			break;
		case 4:
			printf("ËÁÇª");
			break;
		case 5:
			printf("ÎéÇª");
			break;
		case 6:
			printf("Â½Çª");
			break;
		case 7:
			printf("ÆâÇª");
			break;
		case 8:
			printf("°ÆÇª");
			break;
		case 9:
			printf("¾ÁÇª");
			break;
	}
	switch (i / 100000 % 10)
	{
		case 0:
			printf(((i / 1000000 % 10 == 0) ? "" : (i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? ((i / 100 % 10 == 0 && i / 10 % 10 == 0 && i % 10 == 0 && (int)(10 * b) % 10 == 0) ? "" : "Áã") : "Áã"));
			break;
		case 1:
			printf("Ò¼°Û");
			break;
		case 2:
			printf("·¡°Û");
			break;
		case 3:
			printf("Èş°Û");
			break;
		case 4:
			printf("ËÁ°Û");
			break;
		case 5:
			printf("Îé°Û");
			break;
		case 6:
			printf("Â½°Û");
			break;
		case 7:
			printf("Æâ°Û");
			break;
		case 8:
			printf("°Æ°Û");
			break;
		case 9:
			printf("¾Á°Û");
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
					printf( "Áã");
			}

			break;
		case 1:
			printf("Ò¼Ê°");
			break;
		case 2:
			printf("·¡Ê°");
			break;
		case 3:
			printf("ÈşÊ°");
			break;
		case 4:
			printf("ËÁÊ°");
			break;
		case 5:
			printf("ÎéÊ°");
			break;
		case 6:
			printf("Â½Ê°");
			break;
		case 7:
			printf("ÆâÊ°");
			break;
		case 8:
			printf("°ÆÊ°");
			break;
		case 9:
			printf("¾ÁÊ°");
			break;
	}
	switch (i / 1000 % 10)
	{
		case 0:
			if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
				printf("");
			else
				printf("Íò");
			break;
		case 1:
			printf("Ò¼Íò");
			break;
		case 2:
			printf("·¡Íò");
			break;
		case 3:
			printf("ÈşÍò");
			break;
		case 4:
			printf("ËÁÍò");
			break;
		case 5:
			printf("ÎéÍò");
			break;
		case 6:
			printf("Â½Íò");
			break;
		case 7:
			printf("ÆâÍò");
			break;
		case 8:
			printf("°ÆÍò");
			break;
		case 9:
			printf("¾ÁÍò");
			break;
	}
	switch (i / 100 % 10)//´¦ÀíÍòÎ»ÒÔÏÂµÄ¶ÁÈ¡
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
						printf("Áã");
				}
            }
			break;
		case 1:
			printf("Ò¼Çª");
			break;
		case 2:
			printf("·¡Çª");
			break;
		case 3:
			printf("ÈşÇª");
			break;
		case 4:
			printf("ËÁÇª");
			break;
		case 5:
			printf("ÎéÇª");
			break;
		case 6:
			printf("Â½Çª");
			break;
		case 7:
			printf("ÆâÇª");
			break;
		case 8:
			printf("°ÆÇª");
			break;
		case 9:
			printf("¾ÁÇª");
			break;
	}
	switch (i / 10 % 10)
	{
		case 0:
			printf(((i / 100 % 10 == 0) ? (i % 10 == 0 ? "" : ((i / 100000000 % 10 == 0 && i / 10000000 % 10 == 0 && i / 1000000 % 10 == 0 && i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100 % 10 == 0 ? "" : "Áã"))) : ""));
			break;
		case 1:
			printf("Ò¼°Û");
			break;
		case 2:
			printf("·¡°Û");
			break;
		case 3:
			printf("Èş°Û");
			break;
		case 4:
			printf("ËÁ°Û");
			break;
		case 5:
			printf("Îé°Û");
			break;
		case 6:
			printf("Â½°Û");
			break;
		case 7:
			printf("Æâ°Û");
			break;
		case 8:
			printf("°Æ°Û");
			break;
		case 9:
			printf("¾Á°Û");
			break;
	}
	switch (i % 10)
	{
		case 0:
			printf(((i / 10 % 10 == 0) ? ((i / 100000000 % 10 == 0 && i / 10000000 % 10 == 0 && i / 1000000 % 10 == 0 && i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 == 0 && i / 100 == 0 ? "" : ((int)(10 * b) % 10 == 0 ? "" : "Áã"))) : ((int)(10 * b) % 10 == 0 ? "" : "Áã")));
			break;
		case 1:
			printf("Ò¼Ê°");
			break;
		case 2:
			printf("·¡Ê°");
			break;
		case 3:
			printf("ÈşÊ°");
			break;
		case 4:
			printf("ËÁÊ°");
			break;
		case 5:
			printf("ÎéÊ°");
			break;
		case 6:
			printf("Â½Ê°");
			break;
		case 7:
			printf("ÆâÊ°");
			break;
		case 8:
			printf("°ÆÊ°");
			break;
		case 9:
			printf("¾ÁÊ°");
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
				printf("Ô²");
			break;
		case 1:
			printf("Ò¼Ô²");
			break;
		case 2:
			printf("·¡Ô²");
			break;
		case 3:
			printf("ÈşÔ²");
			break;
		case 4:
			printf("ËÁÔ²");
			break;
		case 5:
			printf("ÎéÔ²");
			break;
		case 6:
			printf("Â½Ô²");
			break;
		case 7:
			printf("ÆâÔ²");
			break;
		case 8:
			printf("°ÆÔ²");
			break;
		case 9:
			printf("¾ÁÔ²");
			break;
	}
	switch ((int)(100 * b) % 10)
	{
		case 0:
			((int)(1000 * b) % 10 == 0) ? printf("Õû") : printf((int)(a) == 0 ? "" : "Áã");
			break;
		case 1:
			printf("Ò¼½Ç");
			break;
		case 2:
			printf("·¡½Ç");
			break;
		case 3:
			printf("Èş½Ç");
			break;
		case 4:
			printf("ËÁ½Ç");
			break;
		case 5:
			printf("Îé½Ç");
			break;
		case 6:
			printf("Â½½Ç");
			break;
		case 7:
			printf("Æâ½Ç");
			break;
		case 8:
			printf("°Æ½Ç");
			break;
		case 9:
			printf("¾Á½Ç");
			break;
	}
	switch ((int)(1000 * b) % 10)
	{
		case 0:
			((int)(100 * b) % 10 == 0) ? printf("") : printf("Õû");
			break;
		case 1:
			printf("Ò¼·Ö");
			break;
		case 2:
			printf("·¡·Ö");
			break;
		case 3:
			printf("Èş·Ö");
			break;
		case 4:
			printf("ËÁ·Ö");
			break;
		case 5:
			printf("Îé·Ö");
			break;
		case 6:
			printf("Â½·Ö");
			break;
		case 7:
			printf("Æâ·Ö");
			break;
		case 8:
			printf("°Æ·Ö");
			break;
		case 9:
			printf("¾Á·Ö");
			break;
	}
	return 0;
}
