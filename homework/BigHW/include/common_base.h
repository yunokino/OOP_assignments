#pragma once
void panning_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int command_line = 1);
int mark_same_recursion(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int first = 1, int make_to_ten = 1, int command_line = 1);
int merge_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int& max_num, int goal_point =0, int* grade=0, int make_to_ten = 1);
void down_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row);
void make_new_num(int matrix_num[][10], int max_num, int output_line, int output_row);
void choose_num_noline(int matrix_num[][10], int line, int row, int location[]);
void choose_num(int matrix_num[][10], int line, int row, int make_to_ten = 1);
void print_merge(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int old = 1, int make_to_ten = 1, int no_line = 0);
void except_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int& k, int& is_central, int& max_num);
void destory_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int no_line = 1);
void fall_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int make_to_ten = 1, int no_line = 0);
void judge_quit(char quit);
void plus_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int& max_num, int goal_point, int* grade, int* _9, int make_to_ten = 1, int no_line = 0);
int judge_end(int matrix_num[][10], int line, int row);
void is_end();