/* 2152041 计科 王浩 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class TString {
private:
	char* content;
	int   len;
	char* next;
public:
	inline const int length();
	inline TString();
	inline TString& operator+=(const char* str);
	inline bool operator!=(const char* str);
};

inline TString::TString()
{
	content = NULL;
	next = NULL;
	len = 0;
}

inline const int TString:: length()
{
	return len;
}

inline TString& TString:: operator+=(const char* str)
{
	/* 内存碎片化，像链表一样连接起来，越来越慢应该是因为new申请的连续内存越来越大，寻找时间会变长 */
	if (len == 0)
	{
		len = strlen(str);
		content = new char[len + 1];
		memcpy(content, str, len + 1);
		return *this;
	}
	/* 连接起来 */
	len += strlen(str);
	//int length = strlen(str);
	//char* tmp = new char[len + length + 1];
	//memcpy(tmp, content, len + 1);
	//delete[]content;
	//memcpy(tmp + len, str, length + 1);
	//len += length;
	//content = tmp;
	return *this;
}

inline bool TString:: operator!=(const char* str)
{
	if (len == int(strlen(str)) && !strcmp(content, str))
		return 0;
	else
		return 1;
}

//TString::~TString()
//{
//	char* p = content;
//	while (p != NULL)
//		p = next;
//}
