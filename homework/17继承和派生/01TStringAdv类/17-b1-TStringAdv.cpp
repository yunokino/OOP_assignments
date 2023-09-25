/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iostream>
#include <string.h>
#include "17-b1-TStringAdv.h"
using namespace std;

TStringAdv::TStringAdv():TString()
{

}

TStringAdv::TStringAdv(const char* str):TString(str)
{
}

TStringAdv::TStringAdv(const TString& str) :TString(str)
{
}

TStringAdv& TStringAdv::assign(const TStringAdv& ts2)
{
	if (ts2.content == NULL)
	{
		len = 0;
		content = NULL;
		return *this;
	}
	else
		len = ts2.len;
	if (content != ts2.content)
		delete[] content;
	else
		return *this;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		return *this;
	}
	strcpy(content, ts2.content);
	return *this;
}

TStringAdv& TStringAdv::assign(const char* s)
{
	if (this->content)
		delete[]this->content;
	if (s == NULL || strlen(s) == 0)
	{
		this->len = 0;
		this->content = NULL;
		return *this;
	}
	int s_len = strlen(s);
	this->content = new(nothrow)char[s_len + 1];
	if (this->content == NULL)
		return *this;
	this->len = s_len;
	memcpy(this->content, s, s_len + 1);
	return *this;
}

TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
	(* this) += ts2;
	return *this;
}

TStringAdv& TStringAdv::append(const char* s)
{
	(*this) += s;
	return *this;
}

TStringAdv& TStringAdv::append(const char& c)
{
	if (this->content == NULL)
	{
		this->content = new char[CHAR_SIZE + 1];
		this->content[0] = c;
		this->content[1] = '\0';
		this->len = 1;
		return *this;
	}
	this->len += CHAR_SIZE;
	char* tmp = new(nothrow) char[len + 1];
	if (tmp == NULL)
		return *this;
	memcpy(tmp, this->content, this->len);
	tmp[len - 1] = c;
	tmp[len] = '\0';
	delete[]this->content;
	this->content = tmp;
	return *this;
}

TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
	if (this->len == 0)
	{
		if (pos == 1 && ts2.len != 0)
			*this = ts2;
		return *this;
	}
	if (ts2.len == 0)
		return *this;
	if (pos < 1 || pos > this->len + 1 || ts2.len == 0)
		return *this;
	if (pos == 1)//插入头部
	{
		TStringAdv tmp = ts2;
		tmp.append(*this);
		this->assign(tmp);
		return *this;
	}
	if (pos == this->len + 1)//插入尾部
	{
		this->append(ts2);
		return *this;
	}
	/* 插入中间 */
	int length = this->len + ts2.len;
	char* tmp = new(nothrow)char[length + 1];
	if (tmp == NULL)
		return* this;
	memcpy(tmp, this->content, pos - 1);
	memcpy(tmp + pos - 1, ts2.content, ts2.len + 1);
	memcpy(tmp + pos + ts2.len - 1, this->content + pos - 1, this->len - pos + 2);
	delete[]content;
	this->content = tmp;
	this->len += ts2.len;
	return *this;
}

TStringAdv& TStringAdv::insert(const char* s, int pos)
{
	if (this->len == 0)
	{
		if (pos == 1 && s!=NULL&&strlen(s)!=0 )
			*this = TStringAdv(s);
		return *this;
	}
	if (s == NULL)
		return *this;
	int s_len = strlen(s);
	if (s_len == 0)
		return *this;
	if (pos < 1 || pos > this->len + 1 || s_len == 0)
		return *this;
	if (pos == 1)
	{
		TStringAdv tmp = s;
		tmp.append(*this);
		this->assign(tmp);
		return *this;
	}
	if (pos == this->len + 1)
	{
		this->append(s);
		return *this;
	}
	int length = this->len + s_len;
	char* tmp = new(nothrow)char[length + 1];
	if (tmp == NULL)
		return*this;
	memcpy(tmp, this->content, pos - 1);
	memcpy(tmp + pos - 1,s, s_len + 1);
	memcpy(tmp + pos + s_len - 1, this->content + pos - 1, this->len - pos + 2);
	delete[]content;
	this->content = tmp;
	this->len += s_len;
	return *this;
}

TStringAdv& TStringAdv::insert(const char& c, int pos)
{
	if (len == 0)
		return *this;
	if (pos < 1 || pos > this->len + 1)
		return *this;
	if (pos == 1)
	{
		TStringAdv tmp;
		tmp.append(c);
		tmp.append(*this);
		this->assign(tmp);
		return *this;
	}
	if (pos == this->len + 1)
	{
		this->append(c);
		return *this;
	}
	int length = this->len + CHAR_SIZE;
	char* tmp = new(nothrow)char[length + 1];
	if (tmp == NULL)
		return*this;
	memcpy(tmp, this->content, pos - 1);
	tmp[pos-1] = c;
	memcpy(tmp + pos + CHAR_SIZE - 1, this->content + pos  -1, this->len - pos + 2);
	this->content = tmp;
	this->len += CHAR_SIZE;
	return *this;
}

TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
	const char* ret = strstr(content, ts2.content);
	if (ret == NULL)
		return *this;
	int length = ret - content;
	char* store = new(nothrow) char[strlen(content) + 1];
	strcpy(store, content);
	len -= ts2.len;
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
		return *this;
	for (int i = 0; i < len + 1; i++)
	{
		if (i < length)
			content[i] = store[i];
		else if (i >= length)
			content[i] = store[i + ts2.len];
	}
	delete[]store;
	return *this;

}

TStringAdv& TStringAdv::erase(const char* s)
{
	if (s == NULL)
		return *this;
	const char* ret = strstr(content, s);
	if (ret == NULL)
		return *this;
	int length = ret - content;
	char* store = new(nothrow) char[strlen(content) + 1];
	strcpy(store, content);
	len -= strlen(s);
	delete[] content;
	content = new(nothrow) char[len + 1];
	if (content == NULL)
		return *this;
	for (int i = 0; i < len + 1; i++)
	{
		if (i < length)
			content[i] = store[i];
		else if (i >= length)
			content[i] = store[i + strlen(s)];
	}
	delete[]store;
	return *this;
}

TStringAdv& TStringAdv::erase(const char& c)
{
	const char* ret = strchr(content, c);
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

TStringAdv TStringAdv::substr(const int pos, const int len)
{
	if (pos < 1 || pos > this->len)
		return NULL;
	int sub_len = (len == -1)?this->len - pos + 1:len;
	if (pos + len - 1 > (int)strlen(content))
		sub_len = strlen(content) - pos + 1;
	char* sub_str = new(nothrow)char[sub_len + 1];
	if (sub_str == NULL)
		return NULL;
	memcpy(sub_str, content + pos - 1, sub_len);
	sub_str[sub_len] = '\0';
	return TStringAdv(sub_str);
}

char& TStringAdv::at(const int n)
{
	return this->content[n];
}

istream& operator>>(istream& in, TStringAdv& str)
{
	char* content = new(nothrow) char[MAX_SIZE];
	in >> content;
	str.content = new(nothrow) char[strlen(content) + 1];
	if (str.content == NULL)
		return in;
	str.content = content;
	str.len = strlen(str.content);
	return in;
}

ostream& operator<<(ostream& out,const TStringAdv &str)
{
	if (str.len == 0)
		out << "<NULL>";
	else
		out << str.content;
	return out;
}

