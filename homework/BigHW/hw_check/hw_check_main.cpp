/* 2152041 �ƿ� ���� */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "../include/class_aat.h"
extern int check_secondline(const string& cno, const string& stulist_fname, const string& filename, const string& debug);
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������ԣ�ʵ��ʹ��ʱ��������һ��cpp(����hw_check_secondline.cpp)������
 ***************************************************************************/

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����������ҵ��Ҫ��ʵ�֣���������Ҫ�Ķ�
 ***************************************************************************/
int check_firstline(const string& cno, const string &stilist_fname, const string& filename)
{
	cout << "��ʼ����Դ�����ļ����м��..." << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;

	cout << endl;
	cout << "Usage: " << procname << " { --firstline | --secondline  }" << endl;
	cout << setw(wkey) << ' ' << "{ --cno xxx }" << endl;
	cout << setw(wkey) << ' ' << "{ --filename xxx/all }" << endl; //Լ��������ʵ���ļ���Ϊall
	cout << setw(wkey) << ' ' << "{ --stulist_fname xxx }" << endl;
	cout << setw(wkey) << ' ' << "{ --debug 11111 }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���������(��ѡһ)" << endl;
	cout << setw(wopt) << ' ' << "--firstline     : ���м��" << endl;
	cout << setw(wopt) << ' ' << "--secondline    : ���м��" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--cno           : �κ�" << endl;
	cout << setw(wopt) << ' ' << "--filename      : �ļ���(all��ʾȫ��)" << endl;
	cout << setw(wopt) << ' ' << "--stulist_fname : ��Ӧ��ѧ���б��ļ���" << endl;
	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--debug         : Debugѡ��(��������--secondline��Ĭ��11111)" << endl;
	cout << endl;

	cout << "e.g.   " << procname << " --firstline --cno 100692 --filename 3-b1.cpp --stulist_fname 100692.txt               : ���100692�γ̵�3-b1.cpp������" << endl;
	cout << "       " << procname << " --firstline --cno 100692 --filename all --stulist_fname 100692-firstline.txt          : ���100692�γ̵�ȫ���ļ�������" << endl;
	cout << "       " << procname << " --secondline --cno 100742 --filename 15-b5.c --stulist_fname 10108001.dat               : ���100742�γ̵�15-b5.c�Ĵ��У����ȫ����Ϣ" << endl;
	cout << "       " << procname << " --secondline --cno 100742 --filename 15-b5.c --stulist_fname 10108001.dat --debug 01001 : ���100742�γ̵�15-b5.c�Ĵ��У������2��5����Ϣ" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "����cmd�¼Ӳ�������." << endl << endl;
		system("pause");
	}
}

/* enum��˳��Ҫ��args������˳�򱣳�һ��
   ����enum class ֻ�ǲ���ÿ�ζ���ǿ��ת�� */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_FIRSTLINE, OPT_ARGS_SECONDLINE, OPT_ARGS_COURSEID, OPT_ARGS_FILENAME, OPT_ARGS_STULIST_FNAME, OPT_ARGS_DEBUG };

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--firstline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--secondline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cno", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--filename", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--stulist_fname", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--debug", ST_EXTARGS_TYPE::str, 1, string("11111")),
		args_analyse_tools()  //���һ�������ڽ���
	};

	int cur_argc, ret = 0;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ��Ҫ�Լ�ʵ�� */
	args_analyse_print(args);

	/* ��help�����⴦�� */
	if (args[OPT_ARGS_HELP].existed()) {
		//ֻҪ�� --help���������������ԣ���ʾ��������
		usage(argv[0], argc);
		return -1; //ִ�����ֱ���˳�
	}

	/* ������������ */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_SECONDLINE].existed() != 1) {
		usage(argv[0], argc);
		cout << "����[" << args[OPT_ARGS_FIRSTLINE].get_name() << "|" << args[OPT_ARGS_SECONDLINE].get_name() << "]����ָ��һ����ֻ��ָ��һ��" << endl;
		return -1;
	}

	/* �жϱ�ѡ���Ƿ���� */
	if (args[OPT_ARGS_COURSEID].existed() == 0) {
		cout << "����ָ������[" << args[OPT_ARGS_COURSEID].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* �жϱ�ѡ���Ƿ���� */
	if (args[OPT_ARGS_FILENAME].existed() == 0) {
		cout << "����ָ������[" << args[OPT_ARGS_FILENAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* �жϱ�ѡ���Ƿ���� */
	if (args[OPT_ARGS_STULIST_FNAME].existed() == 0) {
		cout << "����ָ������[" << args[OPT_ARGS_STULIST_FNAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* �ж� --firstline �� --debug �Ƿ��ͻ */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_DEBUG].existed() == 2) {
		cout << "����[" << args[OPT_ARGS_FIRSTLINE].get_name() << "]����Ҫ[" << args[OPT_ARGS_DEBUG].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* �ж� --secondline �� --filename all �Ƿ��ͻ */
	if (args[OPT_ARGS_SECONDLINE].existed()) {
		if (args[OPT_ARGS_FILENAME].get_string() == "all") {
			cout << "����[" << args[OPT_ARGS_SECONDLINE].get_name() << "]��[" << args[OPT_ARGS_SECONDLINE].get_name() << "]����Ϊall" << endl;
			usage(argv[0], argc);
			return -1;
		}
	}

	if (args[OPT_ARGS_FIRSTLINE].existed()) {
		/* �������м�� */
		check_firstline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string());
	}
	else if (args[OPT_ARGS_SECONDLINE].existed()) {
		/* ���д��м�� */
		check_secondline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string(), args[OPT_ARGS_DEBUG].get_string());
	}

	return 0;
}
