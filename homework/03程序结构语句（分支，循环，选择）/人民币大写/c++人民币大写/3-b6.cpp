/*���� ��07 2152041*/
#include <iostream>
using namespace std;

int main()
{

	double a, b;
	int i;
	cout << "������[0-100�ڣ�֮�������:\n";
	cin >> a;
	i = int(a / 10);
	b = a / 10 - i + 0.0001;
	cout << "��д�����:\n";
	switch (i / 100000000 % 10)//����ʮ�ڣ���λ�Ķ���
	{
		case 0:
			cout << "";
			break;
		case 1:
			cout << "Ҽʰ";
			break;
		case 2:
			cout << "��ʰ";
			break;
		case 3:
			cout << "��ʰ";
			break;
		case 4:
			cout << "��ʰ";
			break;
		case 5:
			cout << "��ʰ";
			break;
		case 6:
			cout << "½ʰ";
			break;
		case 7:
			cout << "��ʰ";
			break;
		case 8:
			cout << "��ʰ";
			break;
		case 9:
			cout << "��ʰ";
			break;
	}
	switch (i / 10000000 % 10)
	{
		case 0:
			(i / 100000000 % 10 == 0) ? cout << "" : cout << "��";
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "����";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "����";
			break;
		case 8:
			cout << "����";
			break;
		case 9:
			cout << "����";
			break;
	}
	switch (i / 1000000 % 10)//������λ����λ�Ķ�ȡ
	{
		case 0:
			cout << ((i / 10000000 % 10 == 0) ? "" : ((i / 100000 % 10 == 0 && i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? "" : ((i / 10000000 % 10 == 0) ? "" : "��")));//�������ȫ���㲻���������
			break;
		case 1:
			cout << "ҼǪ";
			break;
		case 2:
			cout << "��Ǫ";
			break;
		case 3:
			cout << "��Ǫ";
			break;
		case 4:
			cout << "��Ǫ";
			break;
		case 5:
			cout << "��Ǫ";
			break;
		case 6:
			cout << "½Ǫ";
			break;
		case 7:
			cout << "��Ǫ";
			break;
		case 8:
			cout << "��Ǫ";
			break;
		case 9:
			cout << "��Ǫ";
			break;
	}
	switch (i / 100000 % 10)
	{
		case 0:
			cout << ((i / 1000000 % 10 == 0) ? "" : (i / 10000 % 10 == 0 && i / 1000 % 10 == 0) ? ((i / 100 % 10 == 0 && i / 10 % 10 == 0 && i % 10 == 0 && int(10 * b) % 10 == 0) ? "" : "��") : "��");
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "���";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "���";
			break;
		case 8:
			cout << "�ư�";
			break;
		case 9:
			cout << "����";
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
					cout << "��";
			}

			break;
		case 1:
			cout << "Ҽʰ";
			break;
		case 2:
			cout << "��ʰ";
			break;
		case 3:
			cout << "��ʰ";
			break;
		case 4:
			cout << "��ʰ";
			break;
		case 5:
			cout << "��ʰ";
			break;
		case 6:
			cout << "½ʰ";
			break;
		case 7:
			cout << "��ʰ";
			break;
		case 8:
			cout << "��ʰ";
			break;
		case 9:
			cout << "��ʰ";
			break;
	}
	switch (i / 1000 % 10)
	{
		case 0:
			if (i / 10000 % 10 == 0 && i / 100000 % 10 == 0 && i / 1000000 % 10 == 0)
				cout << "";
			else
				cout << "��";
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "����";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "����";
			break;
		case 8:
			cout << "����";
			break;
		case 9:
			cout << "����";
			break;
	}
	switch (i / 100 % 10)//������λ���µĶ�ȡ
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
						cout << "��";
				}

			}
			break;
		case 1:
			cout << "ҼǪ";
			break;
		case 2:
			cout << "��Ǫ";
			break;
		case 3:
			cout << "��Ǫ";
			break;
		case 4:
			cout << "��Ǫ";
			break;
		case 5:
			cout << "��Ǫ";
			break;
		case 6:
			cout << "½Ǫ";
			break;
		case 7:
			cout << "��Ǫ";
			break;
		case 8:
			cout << "��Ǫ";
			break;
		case 9:
			cout << "��Ǫ";
			break;
	}
	switch (i / 10 % 10)
	{
		case 0:
			cout << ((i / 100 % 10 == 0) ? "" : (i % 10 == 0 && int(10 * b) % 10 == 0 ? "" : "��"));
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "���";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "���";
			break;
		case 8:
			cout << "�ư�";
			break;
		case 9:
			cout << "����";
			break;
	}
	switch (i % 10)
	{
		case 0:
			cout << ((i / 10 % 10 == 0) ? "" : (int(10 * b) % 10 == 0 ? "" : "��"));
			break;
		case 1:
			cout << "Ҽʰ";
			break;
		case 2:
			cout << "��ʰ";
			break;
		case 3:
			cout << "��ʰ";
			break;
		case 4:
			cout << "��ʰ";
			break;
		case 5:
			cout << "��ʰ";
			break;
		case 6:
			cout << "½ʰ";
			break;
		case 7:
			cout << "��ʰ";
			break;
		case 8:
			cout << "��ʰ";
			break;
		case 9:
			cout << "��ʰ";
			break;
	}
	switch (int(10 * b) % 10)
	{
		case 0:
			if (int(a) == 0)
			{
				if(a==0)
					cout<<"��Բ"; 
				else
					cout << "";
			}
			else
				cout << "Բ";
			break;
		case 1:
			cout << "ҼԲ";
			break;
		case 2:
			cout << "��Բ";
			break;
		case 3:
			cout << "��Բ";
			break;
		case 4:
			cout << "��Բ";
			break;
		case 5:
			cout << "��Բ";
			break;
		case 6:
			cout << "½Բ";
			break;
		case 7:
			cout << "��Բ";
			break;
		case 8:
			cout << "��Բ";
			break;
		case 9:
			cout << "��Բ";
			break;
	}
	switch (int(100 * b) % 10)
	{
		case 0:
			(int(1000 * b) % 10 == 0) ? cout << "��" : cout << (int(a)==0?"":"��");
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "���";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "���";
			break;
		case 8:
			cout << "�ƽ�";
			break;
		case 9:
			cout << "����";
			break;
	}
	switch (int(1000 * b) % 10)
	{
		case 0:
			(int(100 * b) % 10 == 0) ? cout << "" : cout << "��";
			break;
		case 1:
			cout << "Ҽ��";
			break;
		case 2:
			cout << "����";
			break;
		case 3:
			cout << "����";
			break;
		case 4:
			cout << "����";
			break;
		case 5:
			cout << "���";
			break;
		case 6:
			cout << "½��";
			break;
		case 7:
			cout << "���";
			break;
		case 8:
			cout << "�Ʒ�";
			break;
		case 9:
			cout << "����";
			break;
	}
	cout<<endl;
	return 0;
}
