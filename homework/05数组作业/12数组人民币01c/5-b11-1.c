/* 2152041 王浩 信07 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
//可按需增加需要的头文件

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖拾"; /* 所有输出大写 "零" ~ "玖" 的地方，只允许从这个数组中取值 */
char result[256];  /* 除result外，不再允许定义任何形式的全局变量 */

/* --允许添加需要的函数 --*/
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	/* --允许添加需要的内容 --*/
	double a, b;
	int i, c;
	printf("请输入[0-100亿)之间的数字:\n");
	scanf("%lf", &a);
	i = (int)(a / 10);
	b = a / 10 - i + 0.0001;
	c = (int)((i - (int)(i / 10000000) * 10000000) / 1000);//万位上的四位数字
	printf("大写结果是:\n");
	daxie(i / 100000000 % 10, 0);
	if (i / 100000000 % 10 != 0)
		strcat(result, "拾");
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		strcat(result, "亿");
	daxie(i / 10000000 % 10, (i - (int)(i / 10000000) * 10000000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (i / 1000000 % 10 == 0 ? i / 100000000 % 10 : 0));
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 != 0)
		strcat(result, "亿");
	if (i / 100000000 % 10 == 0 && i / 10000000 % 10 != 0)
		strcat(result, "亿");
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		strcat(result, "");
	daxie(i / 1000000 % 10, ((i - (int)(i / 1000000) * 1000000) == 0 && (int)(10 * b) % 10 == 0) ? 0 : ((c == 0 && i / 100 % 10 != 0) ? 0 : i / 10000000 % 10));
	if (i / 1000000 % 10 != 0)
		strcat(result, "仟");
	if (i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 1000000 % 10 != 0)
		strcat(result, "万");
	daxie(i / 100000 % 10, (i - (int)(i / 100000) * 100000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 1000) * 1000 == 0 ? 0 : i / 1000000 % 10));
	if (i / 100000 % 10 != 0)
		strcat(result, "佰");
	if (i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100000 % 10 != 0)
		strcat(result, "万");
	daxie(i / 10000 % 10, (i - (int)(i / 10000) * 10000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 100) * 100 == 0 ? 0 : i / 100000 % 10));
	if (i / 10000 % 10 != 0)
		strcat(result, "拾");
	if (i / 1000 % 10 == 0 && i / 10000 % 10 != 0)
		strcat(result, "万");
	daxie(i / 1000 % 10, (i - (int)(i / 1000) * 1000) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c - (int)(c / 10) * 10 == 0 ? 0 : i / 10000 % 10));
	if (i / 1000 % 10 != 0)
		strcat(result, "万");
	daxie(i / 100 % 10, (i - (int)(i / 100) * 100) == 0 && (int)(10 * b) % 10 == 0 ? 0 : (c == 0 ? 0 : 1));
	if (i / 100 % 10 != 0)
		strcat(result, "仟");
	daxie(i / 10 % 10, (i - (int)(i / 10) * 10) == 0 && (int)(10 * b) % 10 == 0 ? 0 : i / 100 % 10);
	if (i / 10 % 10 != 0)
		strcat(result, "佰");
	daxie(i % 10, (i - (int)(i)) == 0 && (int)(10 * b) % 10 == 0 ? 0 : i / 10 % 10);
	if (i % 10 != 0)
		strcat(result, "拾");
	daxie((int)(10 * b) % 10, a == 0 ? 1 : 0);
	if (i != 0 || (int)(10 * b) % 10 != 0 || a == 0)
		strcat(result, "圆");
	if ((i != 0 || (int)(10 * b) % 10 != 0) && (int)(100 * b) % 10 == 0 && (int)(1000 * b) % 10 == 0)
		strcat(result, "整");
	if (a == 0)
		strcat(result, "整");
	daxie((int)(100 * b) % 10, ((i != 0 || (int)(10 * b) % 10 != 0) && (int)(1000 * b) % 10));
	if ((int)(100 * b) % 10 != 0 && (int)(1000 * b) % 10 == 0)
		strcat(result, "角整");
	else if ((int)(100 * b) % 10 != 0 && (int)(1000 * b) % 10 != 0)
		strcat(result, "角");
	daxie((int)(1000 * b) % 10, 0);
	if ((int)(1000 * b) % 10 != 0)
		strcat(result, "分");


	printf("%s\n", result);  /* 转换得到的大写结果，只允许用本语句输出，之前不允许任何形式的部分输出 */
	return 0;
}
