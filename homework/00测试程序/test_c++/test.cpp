#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<vector<int>> matrix;

void get_input(matrix& a)
{
	ifstream fin;
	fin.open("input.txt", ios::binary);
	int m, n, p;
	fin >> m >> n >> p;
	int t;
	vector<int>tmp;
	for (int j = 0; j < m * n; j++)
	{
		for (int i = 0; i < p; i++)
		{
			fin >> t;
			tmp.push_back(t);
		}
		a.push_back(tmp);
	}

	fin.close();
}

int main()
{
	matrix a;
	get_input(a);
	int max, sum = 0;
	int m = a.size(), n = a[0].size(), p  =a[0].size();
	matrix b;

	for (int i = 0; i < m; i++)
	{
		for(int k = 0; k < n; k++)
			for (int t = 0; t < p; t++)
			{
				b[k][t] = 0;
				for (int j = i; j < m; j++)
				{
					for (int k = 0; k < n; k++)
					{
						for (int t = 0; t < p; t++)
						{
							b[k][t] += a[j][k];
							if (max > sum)
								sum = max;
						}
					}
				}
			}
	}
}