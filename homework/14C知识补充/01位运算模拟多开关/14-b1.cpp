/*2152041 �ƿ� ����*/
#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

void switch_state(short num)
{
	cout << "0x";
	unsigned short tmp = (unsigned short)(15 * 16 * 16 * 16);
	for (int i = 0; i < 4; i++)
	{
		unsigned short state = tmp & num;
		tmp /= 16;
		while (state > 15)
			state /= 16;
		cout << hex << state;
	}
	cout << endl;
	for (int i = 'A'; i <= 'J'; i++)
		cout << left << setw(4) << char(i);
	cout << endl;
	for (short i = 1; i < 1024; i *= 2)
	{
		short state = i & num;
		if (state >= 1)
			cout << left << setw(4) << "ON";
		else
			cout << left << setw(4) << "OFF";
	}
	cout << endl;
}

int main()
{
	short on_off_switch = 0x0000;
	cout << "��ʼ״̬��" ;
	switch_state(on_off_switch);
	cout << endl;
	bool loop = 1;
	while (loop)
	{
		char _switch[100],state[100];
		cout << "����(\"A On/J Off\"��ʽ���룬����\"Q on/off\"�˳�)" << endl;
		/* ���벿�� */
		/* ���뿪�� */
		cin >> _switch;
		_switch[0] = tolower(_switch[0]);
		if ((strlen(_switch) != 1 || _switch[0] < 'a' || _switch[0] > 'j' )&& _switch[0] != 'q')
		{
			cin.ignore(65536, '\n');
			continue;
		}
		/* ����״̬ */
		cin >> state;
		for (int i = 0; state[i] != '\0'; i++)
		{
			state[i] = tolower(state[i]);
		}
		if ((strlen(state) != 2 && strlen(state) != 3) || (strcmp(state, "on") && strcmp(state, "off")))
		{
			cin.ignore(65536, '\n');
			continue;
		}
		/* �õ�q�˳� */
		if (_switch[0] == 'q')
			break;
		/* �ı俪��״̬ */
		short tmp = 1, bit_state = 0;
		if (!strcmp(state, "on"))
			bit_state = 1;
		else if (!strcmp(state, "off"))
			bit_state = 0;
		else;
		int count = _switch[0] - 'a';
		while (count)
		{
			tmp *= 2;
			count--;
		}
		if (bit_state == 0)
		{
			tmp = ~tmp;
		}
		if(bit_state == 1)
			on_off_switch |= tmp;
		else
			on_off_switch &= tmp;
		cout << "��ǰ״̬��" ;
		switch_state(on_off_switch);
		cout << endl;
	}
	return 0;
}