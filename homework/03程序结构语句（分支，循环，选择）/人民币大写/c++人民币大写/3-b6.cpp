/*ÍõºÆ ĞÅ07 2152041*/
#include <iostream>
using namespace std;

int main()
{

	double a, b;
	int i;
	cout << "ÇëÊäÈë[0-100ÒÚ£©Ö®¼äµÄÊı×Ö:\n";
	cin >> a;
	i = int(a / 10);
	b = a / 10 - i + 0.0001;
	cout << "´óĞ´½á¹ûÊÇ:\n";
	switch (i / 100000000 % 10)//´¦ÀíÊ®ÒÚ£¬ÒÚÎ»µÄ¶Á·¨
	{
		case 0:
			cout << "";
			break;
		case 1:
			cout << "Ò¼Ê°";
			break;
		case 2:
			cout << "·¡Ê°";
			break;
		case 3:
			cout << "ÈşÊ°";
			break;
		case 4:
			cout << "ËÁÊ°";
			break;
		case 5:
			cout << "ÎéÊ°";
			break;
		case 6:
			cout << "Â½Ê°";
			break;
		case 7:
			cout << "ÆâÊ°";
			break;
		case 8:
			cout << "°ÆÊ°";
			break;
		case 9:
			cout << "¾ÁÊ°";
			break;
	}
	switch (i / 10000000 % 10)
	{
		case 0:
			(i / 100000000 % 10 == 0) ? cout << "" : cout << "ÒÚ";
			break;
		case 1:
			cout << "Ò¼ÒÚ";
			break;
		case 2:
			cout << "·¡ÒÚ";
			break;
		case 3:
			cout << "ÈşÒÚ";
			break;
		case 4:
			cout << "ËÁÒÚ";
			break;
		case 5:
			cout << "ÎéÒÚ";
			break;
		case 6:
			cout << "Â½ÒÚ";
			break;
		case 7:
			cout << "ÆâÒÚ";
			break;
		case 8:
			cout << "°ÆÒÚ";
			break;
		case 9:
			cout << "¾ÁÒÚ";
			break;
	}
	switch (i / 1000000 % 10)//´¦ÀíÍòÎ»ÖÁÒÚÎ»µÄ¶ÁÈ¡
	{
		case 0:
			cout << ((i / 10000000 % 10 == 0) ? "" : ((i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? "" : ((i / 10000000 % 10 == 0) ? "" : "Áã")));//´¦ÀíºóÃæÈ«ÊÇÁã²»Êä³öµÄÎÊÌâ
			break;
		case 1:
			cout << "Ò¼Çª";
			break;
		case 2:
			cout << "·¡Çª";
			break;
		case 3:
			cout << "ÈşÇª";
			break;
		case 4:
			cout << "ËÁÇª";
			break;
		case 5:
			cout << "ÎéÇª";
			break;
		case 6:
			cout << "Â½Çª";
			break;
		case 7:
			cout << "ÆâÇª";
			break;
		case 8:
			cout << "°ÆÇª";
			break;
		case 9:
			cout << "¾ÁÇª";
			break;
	}
	switch (i / 100000 % 10)
	{
		case 0:
			cout << ((i / 1000000 % 10 == 0) ? "" : (i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? ((i / 100 % 10 == 0 && i / 10 % 10 == 0 && i % 10 == 0 && int(10 * b) % 10 == 0) ? "" : "Áã") : "Áã");
			break;
		case 1:
			cout << "Ò¼°Û";
			break;
		case 2:
			cout << "·¡°Û";
			break;
		case 3:
			cout << "Èş°Û";
			break;
		case 4:
			cout << "ËÁ°Û";
			break;
		case 5:
			cout << "Îé°Û";
			break;
		case 6:
			cout << "Â½°Û";
			break;
		case 7:
			cout << "Æâ°Û";
			break;
		case 8:
			cout << "°Æ°Û";
			break;
		case 9:
			cout << "¾Á°Û";
			break;
	}
	switch (i / 10000 % 10)
	{
		case 0:
			if (i / 100000 % 10 == 0)
				cout << "";
			else
			{
				if (i / 1000 % 10 == 0)
					cout << "";
				else
					cout << "Áã";
			}

			break;
		case 1:
			cout << "Ò¼Ê°";
			break;
		case 2:
			cout << "·¡Ê°";
			break;
		case 3:
			cout << "ÈşÊ°";
			break;
		case 4:
			cout << "ËÁÊ°";
			break;
		case 5:
			cout << "ÎéÊ°";
			break;
		case 6:
			cout << "Â½Ê°";
			break;
		case 7:
			cout << "ÆâÊ°";
			break;
		case 8:
			cout << "°ÆÊ°";
			break;
		case 9:
			cout << "¾ÁÊ°";
			break;
	}
	switch (i / 1000 % 10)
	{
		case 0:
			if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
				cout << "";
			else
				cout << "Íò";
			break;
		case 1:
			cout << "Ò¼Íò";
			break;
		case 2:
			cout << "·¡Íò";
			break;
		case 3:
			cout << "ÈşÍò";
			break;
		case 4:
			cout << "ËÁÍò";
			break;
		case 5:
			cout << "ÎéÍò";
			break;
		case 6:
			cout << "Â½Íò";
			break;
		case 7:
			cout << "ÆâÍò";
			break;
		case 8:
			cout << "°ÆÍò";
			break;
		case 9:
			cout << "¾ÁÍò";
			break;
	}
	switch (i / 100 % 10)//´¦ÀíÍòÎ»ÒÔÏÂµÄ¶ÁÈ¡
	{
		case 0:
			if (i / 1000 % 10 == 0)
			{
				if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
					cout << "";
				else
				{
					if (i / 10 % 10 == 0 && i % 10 == 0 && int(10 * b) % 10 == 0)
						cout << "";
					else
						cout << "Áã";
				}

			}
			break;
		case 1:
			cout << "Ò¼Çª";
			break;
		case 2:
			cout << "·¡Çª";
			break;
		case 3:
			cout << "ÈşÇª";
			break;
		case 4:
			cout << "ËÁÇª";
			break;
		case 5:
			cout << "ÎéÇª";
			break;
		case 6:
			cout << "Â½Çª";
			break;
		case 7:
			cout << "ÆâÇª";
			break;
		case 8:
			cout << "°ÆÇª";
			break;
		case 9:
			cout << "¾ÁÇª";
			break;
	}
	switch (i / 10 % 10)
	{
		case 0:
			cout << ((i / 100 % 10 == 0) ? "" : (i % 10 == 0 && int(10 * b) % 10 == 0 ? "" : "Áã"));
			break;
		case 1:
			cout << "Ò¼°Û";
			break;
		case 2:
			cout << "·¡°Û";
			break;
		case 3:
			cout << "Èş°Û";
			break;
		case 4:
			cout << "ËÁ°Û";
			break;
		case 5:
			cout << "Îé°Û";
			break;
		case 6:
			cout << "Â½°Û";
			break;
		case 7:
			cout << "Æâ°Û";
			break;
		case 8:
			cout << "°Æ°Û";
			break;
		case 9:
			cout << "¾Á°Û";
			break;
	}
	switch (i % 10)
	{
		case 0:
			cout << ((i / 10 % 10 == 0) ? "" : (int(10 * b) % 10 == 0 ? "" : "Áã"));
			break;
		case 1:
			cout << "Ò¼Ê°";
			break;
		case 2:
			cout << "·¡Ê°";
			break;
		case 3:
			cout << "ÈşÊ°";
			break;
		case 4:
			cout << "ËÁÊ°";
			break;
		case 5:
			cout << "ÎéÊ°";
			break;
		case 6:
			cout << "Â½Ê°";
			break;
		case 7:
			cout << "ÆâÊ°";
			break;
		case 8:
			cout << "°ÆÊ°";
			break;
		case 9:
			cout << "¾ÁÊ°";
			break;
	}
	switch (int(10 * b) % 10)
	{
		case 0:
			if (int(a) == 0)
			{
				if(a==0)
					cout<<"ÁãÔ²"; 
				else
					cout << "";
			}
			else
				cout << "Ô²";
			break;
		case 1:
			cout << "Ò¼Ô²";
			break;
		case 2:
			cout << "·¡Ô²";
			break;
		case 3:
			cout << "ÈşÔ²";
			break;
		case 4:
			cout << "ËÁÔ²";
			break;
		case 5:
			cout << "ÎéÔ²";
			break;
		case 6:
			cout << "Â½Ô²";
			break;
		case 7:
			cout << "ÆâÔ²";
			break;
		case 8:
			cout << "°ÆÔ²";
			break;
		case 9:
			cout << "¾ÁÔ²";
			break;
	}
	switch (int(100 * b) % 10)
	{
		case 0:
			(int(1000 * b) % 10 == 0) ? cout << "Õû" : cout << (int(a)==0?"":"Áã");
			break;
		case 1:
			cout << "Ò¼½Ç";
			break;
		case 2:
			cout << "·¡½Ç";
			break;
		case 3:
			cout << "Èş½Ç";
			break;
		case 4:
			cout << "ËÁ½Ç";
			break;
		case 5:
			cout << "Îé½Ç";
			break;
		case 6:
			cout << "Â½½Ç";
			break;
		case 7:
			cout << "Æâ½Ç";
			break;
		case 8:
			cout << "°Æ½Ç";
			break;
		case 9:
			cout << "¾Á½Ç";
			break;
	}
	switch (int(1000 * b) % 10)
	{
		case 0:
			(int(100 * b) % 10 == 0) ? cout << "" : cout << "Õû";
			break;
		case 1:
			cout << "Ò¼·Ö";
			break;
		case 2:
			cout << "·¡·Ö";
			break;
		case 3:
			cout << "Èş·Ö";
			break;
		case 4:
			cout << "ËÁ·Ö";
			break;
		case 5:
			cout << "Îé·Ö";
			break;
		case 6:
			cout << "Â½·Ö";
			break;
		case 7:
			cout << "Æâ·Ö";
			break;
		case 8:
			cout << "°Æ·Ö";
			break;
		case 9:
			cout << "¾Á·Ö";
			break;
	}
	cout<<endl;
	return 0;
}
