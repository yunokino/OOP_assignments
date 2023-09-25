/* 2152041 �ƿ� ���� */
#include <iostream>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		0	//������������ó�Ա������ʽʵ�֣����ֵΪ0����ʾ����Ԫ��ʽʵ�֣�

class matrix {
private:
	int value[ROW][COL];
	//����֮�ⲻ������������ݳ�Ա
public:
	matrix(const int(*p)[COL]);	//���캯�����������ʼ������

#if OPERATOR_IS_MENBER_FUNCTION
	//����+�ĳ�Ա����ʵ�ַ�ʽ������
	matrix operator+(const matrix& b);
#else
	//����+����Ԫ����ʵ�ַ�ʽ������
	friend matrix operator+(const matrix& a, const matrix& b);
#endif

	/* ----������Ҫ���������Ա�����Ķ������Ԫ��������������������---- */
	friend istream& operator>>(istream& in, matrix& c);//����>>���
	friend ostream& operator<<(ostream& out, const matrix& c);//����<<���
	matrix();//�޲ι��캯��
};

/* ---- ������Ա����������ʵ��/��Ԫ������ʵ�֣�����+��ʵ���г�Ա����Ԫ������ʽ��Ҫ����������Ԥ������ ---- */

matrix::matrix(const int(*p)[COL])
{
	for(int i = 0;i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			value[i][j] = *(*(p + i) + j);
		}
}

matrix::matrix()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			value[i][j] = 0;
		}
}

istream& operator>>(istream& in, matrix& c)//����>>���
{
	for(int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			in >> c.value[i][j];
		}
	return in;
}
ostream& operator<<(ostream& out, const matrix& c)//����<<���
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			out << c.value[i][j] <<" ";
		}
		out << endl;
	}
	return out;
}

#if OPERATOR_IS_MENBER_FUNCTION
//����+�ĳ�Ա������ʽ������ʵ��
matrix matrix::operator+(const matrix& b)
{
	matrix tmp;
	for(int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			tmp.value[i][j] = value[i][j] + b.value[i][j];
		}
	return tmp;
}
#else
//����+����Ԫ������ʽ������ʵ��
matrix operator+(const matrix& a, const matrix& b)
{
	matrix tmp;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
		{
			tmp.value[i][j] = a.value[i][j] + b.value[i][j];
		}
	return tmp;
}

#endif


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3; //m3�ĳ�ֵΪȫ0

	/* ����Ϊ��ֵ���� */
	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* ����Ϊ����������� */
	cout << "�������ʼ����m1" << endl;
	cin >> m1;
	cout << "�������ʼ����m2" << endl;
	cin >> m2;

	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}