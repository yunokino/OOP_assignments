/* 2152041 计科 王浩 */

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "16-b5.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */
TString::TString()
{
	content = NULL;
	len = 0;
}

TString::TString(const char* str)
{
	if (str == NULL || strlen(str) == 0)
	{
		len = 0;
		content = NULL;
	}
	else
	{
		len = strlen(str);
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return;
		else
			strcpy(content, str);
	}
}

TString::TString(const TString& str)
{
	if (str.content == NULL || strlen(str.content) == 0)
	{
		len = 0;
		content = NULL;
	}
	else
	{
		len = strlen(str.content);
		content = new(nothrow) char[len + 1];
		if (content == NULL)
			return;
		else
			strcpy(content, str.content);
	}
}

TString& TString::operator=(const char* str)
{
	if (str == NULL || strlen(str) == 0)
	{
		len = 0;
		content = NULL;
		return *this;
	}
	else
		len = strlen(str);
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(content, str);
	return *this;
}

TString& TString::operator=(const TString& str)
{
	if (str.content == NULL)
	{
		len = 0;
		content = NULL;
		return *this;
	}
	else
		len = str.len;
	if (content != str.content)
		delete[] content;
	else
		return *this;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(content, str.content);
	return *this;
}

const TString operator+(const TString& str1, const TString& str2)
{
	if (str1.content == NULL)
		return str2;
	else if (str2.content == NULL)
		return str1;
	else;
	TString tmp;
	tmp.len = str1.len + str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	strcpy(tmp.content, str1.content);
	strcat(tmp.content, str2.content);
	return tmp;
}

const TString operator+(const char* str1, const TString& str2)
{
	TString tmp;
	if (str1 == NULL || strlen(str1) == 0)
		return str2;
	tmp.len = strlen(str1) + str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	strcpy(tmp.content, str1);
	if (str2.len != 0)
		strcat(tmp.content, str2.content);
	return tmp;
}

const TString operator+(const TString& str2, const char* str1)
{
	if (str1 == NULL || strlen(str1) == 0)
		return str2;
	TString tmp;
	tmp.len = strlen(str1) + str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (tmp.content == NULL)
	{
		delete[]tmp.content;
		return tmp;
	}
	if (str2.len == 0)
	{
		strcpy(tmp.content, str1);
		return tmp;
	}
	strcpy(tmp.content, str2.content);
	strcat(tmp.content, str1);
	return tmp;
}

const TString operator+(const TString& str2, const char ch)
{
	TString tmp;
	tmp.len = CHAR_SIZE + str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	strcpy(tmp.content, str2.content);
	tmp.content[tmp.len-1] = ch;
	tmp.content[tmp.len] = '\0';
	return tmp;
}

const TString operator+(const char ch, const TString& str2)
{
	TString tmp;
	tmp.len = CHAR_SIZE + str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	tmp.content[0] = ch;
	tmp.content[1] = '\0';
	if(str2.len != 0)
		strcat(tmp.content, str2.content);
	return tmp;
}

TString& TString::operator+=(const TString& str)
{
	if (content == NULL)
	{
		len = str.len;
		content = new(nothrow) char[len + 1];
		if (content == NULL)
		{
			cout << "内存申请失败!" << endl;
			return *this;
		}
		strcpy(content, str.content);
		return *this;
	}
	len += str.len;
	char* tmp = new(nothrow) char[strlen(content) + 1];
	if (tmp == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(tmp, content);
	delete[]content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(content, tmp);
	delete[]tmp;
	strcat(content, str.content);
	return *this;
}

TString& TString::operator+=(const char* str)
{
	if (content == NULL)
	{
		len = strlen(str);
		content = new char[len + 1];
		strcpy(content, str);
		return *this;
	}
	else if (str == NULL)
		return *this;
	int store = len;
	int str_len = strlen(str);
	len += str_len;
	char* tmp = new(nothrow) char[store + 1];
	if (tmp == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	memcpy(tmp, content, store + 1);//memcpy直接拷贝内存，不需要判定，更加快一些
	delete[]content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	memcpy(content, tmp, store + 1);
	memcpy(content + store, str, str_len + 1);
	delete[]tmp;
	return *this;
}

TString& TString::operator+=(const char ch)
{
	if (content == NULL)
	{
		content = new char[CHAR_SIZE + 1];
		content[0] = ch;
		content[1] = '\0';
		len = 1;
		return *this;
	}
	len += CHAR_SIZE;
	char* tmp = new(nothrow) char[strlen(content) + 1];
	if (tmp == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(tmp, content);
	delete[]content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	strcpy(content, tmp);
	delete[] tmp;
	content[len - 1] = ch;
	content[len] = '\0';
	return *this;
}

const TString operator-(const TString& str1, const TString& str2)
{
	const char* ret = strstr(str1.content, str2.content);
	if (ret == NULL)
		return str1;
	TString tmp;
	tmp.len = str1.len - str2.len;
	tmp.content = new(nothrow) char[tmp.len + 1];
	int length = ret - str1.content;
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	for (int i = 0; i < tmp.len + 1; i++)
	{
		if (i < length)
			tmp.content[i] = str1.content[i];
		else if (i >= length)
			tmp.content[i] = str1.content[i + str2.len];
	}
	return tmp;
}

const TString operator-(const TString& str1, const char* str2)
{
	if (str2 == NULL)
		return str1;
	const char* ret = strstr(str1.content, str2);
	if (ret == NULL)
		return str1;
	TString tmp;
	tmp.len = str1.len - strlen(str2);
	tmp.content = new(nothrow) char[tmp.len + 1];
	int length = ret - str1.content;
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	for (int i = 0; i < tmp.len + 1; i++)
	{
		if (i < length)
			tmp.content[i] = str1.content[i];
		else if (i >= length)
			tmp.content[i] = str1.content[i + strlen(str2)];
	}
	return tmp;
}

const TString operator-(const TString& str1, const char ch)
{
	const char* ret = strchr(str1.content, ch);
	if (ret == NULL)
		return str1;
	TString tmp;
	tmp.len = str1.len - CHAR_SIZE;
	tmp.content = new(nothrow) char[tmp.len + 1];
	int length = ret - str1.content;
	if (tmp.content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return tmp;
	}
	for (int i = 0; i < tmp.len + 1; i++)
	{
		if (i < length)
			tmp.content[i] = str1.content[i];
		else if (i >= length)
			tmp.content[i] = str1.content[i + CHAR_SIZE];
	}
	return tmp;
}

TString&TString:: operator-=(const TString& str)
{
	const char* ret = strstr(content, str.content);
	if (ret == NULL)
		return *this;
	int length = ret - content;
	char* store = new(nothrow) char [strlen(content) + 1];
	strcpy(store, content);
	len -= str.len;
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	for (int i = 0; i < len + 1; i++)
	{
		if (i < length)
			content[i] = store[i];
		else if (i >= length)
			content[i] = store[i + str.len];
	}
	delete[]store;
	return *this;
}

TString&TString:: operator-=(const char* str)
{
	if (str == NULL)
		return *this;
	const char* ret = strstr(content, str);
	if (ret == NULL)
		return *this;
	int length = ret - content;
	char* store = new(nothrow) char[strlen(content) + 1];
	strcpy(store, content);
	len -= strlen(str);
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	for (int i = 0; i < len + 1; i++)
	{
		if (i < length)
			content[i] = store[i];
		else if (i >= length)
			content[i] = store[i + strlen(str)];
	}
	delete[]store;
	return *this;
}

TString&TString:: operator-=(const char ch)
{
	const char* ret = strchr(content, ch);
	if (ret == NULL)
		return *this;
	int length = ret - content;
	char* store = new(nothrow) char[strlen(content) + 1];
	strcpy(store, content);
	len -= CHAR_SIZE;
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "内存申请失败!" << endl;
		return *this;
	}
	for (int i = 0; i < len + 1; i++)
	{
		if (i < length)
			content[i] = store[i];
		else if (i >= length)
			content[i] = store[i + CHAR_SIZE];
	}
	delete[]store;
	return *this;
}

TString operator*(const TString& str1, const int multiplier)
{
	if (str1.len == 0)
		return str1;
	TString tmp;
	tmp.len = str1.len * multiplier;
	tmp.content = new(nothrow) char[tmp.len + 1];
	if (multiplier != 0)
	{
		strcpy(tmp.content, str1.content);
		for (int i = 1; i < multiplier; i++)
			strcat(tmp.content, str1.content);
		return tmp;
	}
	return tmp;
}

TString& TString::operator*=(const int multiplier)
{
	if (len == 0)
		return *this;
	len *= multiplier;
	char* store = new(nothrow) char[strlen(content) + 1];
	strcpy(store, content);
	delete[]content;
	content = new(nothrow) char[len + 1];
	if (multiplier != 0)
	{
		strcpy(content, store);
		for (int i = 1; i < multiplier; i++)
			strcat(content, store);
		return *this;
	}
	delete[]store;
	return *this;
}

TString TString:: operator!()
{
	if (len == 0)
		return *this;
	TString tmp;
	tmp.content = new(nothrow) char[len + 1];
	if (tmp.content == NULL)
		return *this;
	for (int i = 0; i < len + 1; i++)
	{
		tmp[i] = content[len - i - 1];
	}
	tmp[len] = '\0';
	return tmp;           
}

ostream& operator<<(ostream& out, const TString& str)
{
	if (str.content == NULL)
		out << "<NULL>";
	else
		out << str.content;
	return out;
}

istream& operator>>(istream& in, TString& str)
{
	char* content = new(nothrow) char[MAX_SIZE];
	in >> content;
	str.content = new(nothrow) char[strlen(content) + 1];
	strcpy(str.content, content);
	delete[] content;
	str.len = strlen(str.content);
	return in;
}

bool operator>(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 0;
	else if (a.len != 0 && b.len == 0)
		return 1;
	else if (a.len == 0 && b.len != 0)
		return 0;
	else
		return (strcmp(a.content, b.content) > 0);
}

bool operator>(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len == 0 && strlen(str) != 0)
		return 0;
	else
		return (strcmp(a.content, str) > 0);
}

bool operator>(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 && strlen(str) != 0)
		return 1;
	else
		return (strcmp(str, a.content) > 0);
}

bool operator<(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 0;
	else if (a.len != 0 && b.len == 0)
		return 0;
	else if (a.len == 0 && b.len != 0)
		return 1;
	else
		return (strcmp(a.content, b.content) < 0);
}

bool operator<(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 && strlen(str) != 0)
		return 1;
	else
		return (strcmp(a.content, str) < 0);
}

bool operator<(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len == 0 && strlen(str) != 0)
		return 0;
	else
		return (strcmp(str, a.content) < 0);
}

bool operator>=(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 1;
	else if (a.len != 0 && b.len == 0)
		return 1;
	else if (a.len == 0 && b.len != 0)
		return 0;
	else
		return (strcmp(a.content, b.content) >= 0);
}

bool operator>=(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len == 0 && strlen(str) != 0)
		return 0;
	else
		return (strcmp(a.content, str) >= 0);
}

bool operator>=(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 && strlen(str) != 0)
		return 1;
	else
		return (strcmp(str, a.content) >= 0);
}

bool operator<=(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 1;
	else if (a.len != 0 && b.len == 0)
		return 0;
	else if (a.len == 0 && b.len != 0)
		return 1;
	else
		return (strcmp(a.content, b.content) <= 0);
}

bool operator<=(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 && strlen(str) != 0)
		return 1;
	else
		return (strcmp(a.content, str) <= 0);
}

bool operator<=(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len == 0 && strlen(str) != 0)
		return 0;
	else
		return (strcmp(str, a.content) <= 0);
}

bool operator==(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 1;
	else if (a.len == 0 || b.len == 0)
		return 0;
	else
		return (strcmp(a.content, b.content) == 0);
}

bool operator==(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len != 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else
		return (strcmp(a.content, str) == 0);
}

bool operator==(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 1;
	else if (a.len == 0 || (str == NULL || strlen(str) == 0))
		return 0;
	else
		return (strcmp(str, a.content) == 0);
}

bool operator!=(const TString& a, const TString& b)
{
	if (a.len == 0 && b.len == 0)
		return 0;
	else if (a.len == 0 || b.len == 0)
		return 1;
	else
		return (strcmp(a.content, b.content) != 0);
}

bool operator!=(const TString& a, const char* str)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 || (str == NULL || strlen(str) == 0))
		return 1;
	else
		return (strcmp(a.content, str) != 0);
}

bool operator!=(const char* str, const TString& a)
{
	if (a.len == 0 && (str == NULL || strlen(str) == 0))
		return 0;
	else if (a.len == 0 || (str == NULL || strlen(str) == 0))
		return 1;
	else
		return (strcmp(str, a.content) != 0);
}

const char* TString:: c_str()const
{
	return content;
}

char& TString::operator[](const int location)
{
	return content[location];
}

const int TString:: length()
{
	return len;
}

TString::~TString()
{
	delete[]content;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int TStringLen(const TString& str)
{
	if (str.c_str() == NULL)
		return 0;
	return strlen(str.c_str());
}

