/* 2152041 王浩 信07 */
#include <iostream>
#include <string>
#include <limits>
//可按需增加需要的头文件
using namespace std;

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖"; /* 所有输出大写 "零" ~ "玖" 的地方，只允许从这个数组中取值 */
string result;  /* 除result外，不再允许定义任何形式的全局变量 */

/* --允许添加需要的函数 --*/
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
	cout << "请输入[0-100亿)之间的数字:\n";
	cin >> a;
	i = int(a / 10);
	b = a / 10 - i + 0.0001;
	c = int((i - int(i / 10000000) * 10000000) / 1000);//万位上的四位数字
	cout << "大写结果是:\n";
	daxie(i / 100000000 % 10, 0);
	if (i / 100000000 % 10 != 0)
		result += "拾";
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		result += "亿";
	daxie(i / 10000000 % 10, (i - int(i / 10000000) * 10000000) == 0 && int(10 * b) % 10 == 0 ? 0 : (i / 1000000 % 10 == 0 ? i / 100000000 % 10 : 0));
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 != 0)
		result += "亿";
	if (i / 100000000 % 10 == 0 && i / 10000000 % 10 != 0)
		result += "亿";
	if (i / 100000000 % 10 != 0 && i / 10000000 % 10 == 0)
		result += "";
	daxie(i / 1000000 % 10, ((i - int(i / 1000000) * 1000000) == 0 && int(10 * b) % 10 == 0) ? 0 : ((c == 0 && i / 100 % 10 != 0) ? 0 : i / 10000000 % 10));
	if (i / 1000000 % 10 != 0)
		result += "仟";
	if (i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 1000000 % 10 != 0)
		result += "万";
	daxie(i / 100000 % 10, (i - int(i / 100000) * 100000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 1000) * 1000 == 0 ? 0 : i / 1000000 % 10));
	if (i / 100000 % 10 != 0)
		result += "佰";
	if (i / 10000 % 10 == 0 && i / 1000 % 10 == 0 && i / 100000 % 10 != 0)
		result += "万";
	daxie(i / 10000 % 10, (i - int(i / 10000) * 10000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 100) * 100 == 0 ? 0 : i / 100000 % 10));
	if (i / 10000 % 10 != 0)
		result += "拾";
	if (i / 1000 % 10 == 0 && i / 10000 % 10 != 0)
		result += "万";
	daxie(i / 1000 % 10, (i - int(i / 1000) * 1000) == 0 && int(10 * b) % 10 == 0 ? 0 : (c - int(c / 10) * 10 == 0 ? 0 : i / 10000 % 10));
	if (i / 1000 % 10 != 0)
		result += "万";
	daxie(i / 100 % 10, (i - int(i / 100) * 100) == 0 && int(10 * b) % 10 == 0 ? 0 : (c == 0 ? 0 : 1));
	if (i / 100 % 10 != 0)
		result += "仟";
	daxie(i / 10 % 10, (i - int(i / 10) * 10) == 0 && int(10 * b) % 10 == 0 ? 0 : i / 100 % 10);
	if (i / 10 % 10 != 0)
		result += "佰";
	daxie(i % 10, (i - int(i)) == 0 && int(10 * b) % 10 == 0 ? 0 : i / 10 % 10);
	if (i % 10 != 0)
		result += "拾";
	daxie(int(10 * b) % 10, a == 0 ? 1 : 0);
	if (i != 0 || int(10 * b) % 10 != 0 || a == 0)
		result += "圆";
	if ((i != 0 || int(10 * b) % 10 != 0) && int(100 * b) % 10 == 0 && int(1000 * b) % 10 == 0)
		result += "整";
	if (a == 0)
		result += "整";
	daxie(int(100 * b) % 10, ((i != 0 || int(10 * b) % 10 != 0) && int(1000 * b) % 10));
	if (int(100 * b) % 10 != 0 && int(1000 * b) % 10 == 0)
		result += "角整";
	else if (int(100 * b) % 10 != 0 && int(1000 * b) % 10 != 0)
		result += "角";
	daxie(int(1000 * b) % 10, 0);
	if (int(1000 * b) % 10 != 0)
		result += "分";

	cout << result << endl;  /* 转换得到的大写结果，只允许用本语句输出，之前不允许任何形式的部分输出 */
	return 0;
}
