#pragma once

void input_ranks(int* line, int* row, int _3 = 0, int* goal_point = 0);
void output_matrix(int line, int row, int matrix_num[][10]);
void input_location(char* line, int* row, int output_line, int output_row);
void output_mark_same(int matrix_num[][10], int mark_same[][10], int output_line, int output_row);
void mark_same_norecursion(int matrix_num[][10], int mark_same[][10], int output_line, int output_row);
int mark_same_recursion(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int first = 1);
void down_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row);
void make_new_num(int matrix_num[][10], int max_num, int output_line, int output_row);
void output_newnum(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int goal_point, int display = 0);
int merge_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int& max_num, int goal_point, int(* grade)=0);
void print_shell(int matrix_num[][10], int line, int row);
void print_square(int matrix_num[][10], int line, int row, int x, int y);
void print_new_square(int matrix_num[][10], int line, int row, int x, int y);
void choose_num(int matrix_num[][10], int line, int row);
void plus_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int &max_num, int goal_point, int* grade, int *_9);
void print_merge(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int old = 1);
void except_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int& k, int& is_central, int &max_num);
void fall_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row);
void make_new_num_tuxing(int matrix_num[][10], int max_num, int output_line, int output_row);
void print_new_shell(int matrix_num[][10], int line, int row);
int judge_end(int matrix_num[][10], int line, int row);
void is_end();