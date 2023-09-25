/* 2152041 计科 王浩 */
#include <iostream>
#include <string>
using namespace std;

template <typename T, int ROW, int COL>
class matrix;
template <typename T, int ROW, int COL>
istream& operator>>(istream& in, matrix<T, ROW, COL>& c);
template <typename T, int ROW, int COL>
ostream& operator<<(ostream& out, const matrix<T, ROW, COL>& c);
template <typename T, int ROW, int COL>
matrix <T, ROW, COL>operator +(matrix<T, ROW, COL>& a, matrix<T, ROW, COL>& b);

template <typename T, int ROW, int COL>
class matrix {
private:
	T value[ROW][COL];
public:
	friend istream& operator>><>(istream& in, matrix<T, ROW, COL>& c);//重载>>输出
	friend ostream& operator<<<>(ostream& out, const matrix<T, ROW, COL>& c);//重载<<输出
	friend matrix operator +<>(matrix<T, ROW, COL>& a, matrix<T, ROW, COL>& b);
};

template <typename T, int ROW, int COL>
istream& operator>>(istream& in, matrix<T, ROW, COL>& c)
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			in >> c.value[i][j];
		}
	return in;
}

template <typename T, int ROW, int COL>
ostream& operator<<(ostream& out, const matrix<T, ROW, COL> & c)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			out << c.value[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

template <typename T, int ROW, int COL>
matrix <T, ROW, COL>operator +(matrix<T, ROW, COL>& a, matrix<T, ROW, COL>& b)
{
	matrix <T, ROW, COL> tmp;
	for(int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			tmp.value[i][j] = a.value[i][j] + b.value[i][j];
		}
	return tmp;
}

