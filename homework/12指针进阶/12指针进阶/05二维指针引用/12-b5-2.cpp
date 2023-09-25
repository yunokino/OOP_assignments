/*2152041 �ƿ� ����*/
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ÿ�����ֿ��Ϊ8���Ҷ���
***************************************************************************/
template <class T,unsigned num>
void matrix_print(const char* tips,T (&matrix)[num])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	int M = num;
	int N = sizeof(matrix) / ((sizeof(**matrix))*M);
	cout << tips << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << right << setw(8) << *(* (matrix + i) + j);
		}
		cout << endl;
	}
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template <typename T1, typename T2, typename T3, unsigned num>
void matrix_addition(T1(&matrix1)[num], T2(&matrix2)[num], T3(&matrix3)[num])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	int M = num;
	int N = sizeof(matrix1) / ((sizeof(**matrix1)) * M);
	cout << "Դ����1 : ��=" << M << " " << "��=" << N << " " << "ռ�ÿռ�=" << sizeof(matrix2) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << M << " " << "��=" << N << " " << "ռ�ÿռ�=" << sizeof(matrix3) << "�ֽ�" << endl;
	cout << "�;���  : ��=" << M << " " << "��=" << N << " " << "ռ�ÿռ�=" << sizeof(matrix1) << "�ֽ�" << endl;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			*(*(matrix1 + i) + j) = *(*(matrix2 + i) + j) + *(*(matrix3 + i) + j);
	return;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template <typename T1,typename T2, typename T3, unsigned num1, unsigned num2>
void matrix_multiplication(T1(&matrix1)[num1], T2(&matrix2)[num1], T3(&matrix3)[num2])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	int M = num1;
	int N = num2; 
	int P = sizeof(matrix1) / ((sizeof(**matrix1)) * M);
	cout << "Դ����1 : ��=" << M << " " << "��=" << N << " " << "ռ�ÿռ�=" << sizeof(matrix2) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << N << " " << "��=" << P << " " << "ռ�ÿռ�=" << sizeof(matrix3) << "�ֽ�" << endl;
	cout << "������  : ��=" << M << " " << "��=" << P << " " << "ռ�ÿռ�=" << sizeof(matrix1) << "�ֽ�" << endl;
	//strcpy_s(1, 2);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < P; j++)
		{
			*(*(matrix1 + i) + j) = 0;
		}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < P; j++)
			for (int k = 0; k < N; k++)
				*(*(matrix1 + i) + j) += (int)(*((*(matrix2 + i)) + k) * (*(*(matrix3 + k) + j)));
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼����
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("�ӷ����㣬Դ����1��", t1);
	matrix_print("�ӷ����㣬Դ����2��", t2);
	matrix_addition(t_add, t1, t2);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", t_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", t1);
	matrix_print("�˷����㣬Դ����2��", t3);
	matrix_multiplication(t_mul, t1, t3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", t_mul);
	cout << sp << endl;
	
	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* ��Ҫ��Ϊʲô����˷��������Ͳ�ͬ������� */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];
	
	matrix_print("�ӷ����㣬Դ����1��", d1);
	matrix_print("�ӷ����㣬Դ����2��", d2);
	matrix_addition(d_add, d1, d2);	//��d1��d2�ĺͷ���d_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", d_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", d1);
	matrix_print("�˷����㣬Դ����2��", f3);
	matrix_multiplication(i_mul, d1, f3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", i_mul);
	cout << sp << endl;

	return 0;
}
