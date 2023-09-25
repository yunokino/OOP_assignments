/* 2152041 ¼Æ¿Æ ÍõºÆ */
#include <iostream>
#include <string>
using namespace std;
#define MAX 100
#define frame_start 5
#define frame_end   23
#define frame_height 15
int read_file(string* file_name);
int choose_file(string* file_name);
int read(string file_name);
void print_pages(string txt, int line, int format);
int read_progress(string file_name);
void change_progress(int line,string file_name);
