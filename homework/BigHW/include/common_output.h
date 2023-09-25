#pragma once
void output_matrix(int line, int row, int matrix_num[][10]);
void output_mark_same(int matrix_num[][10], int mark_same[][10], int output_line, int output_row);
void output_newnum(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int goal_point, int display = 0);
void print_square(int matrix_num[][10], int line, int row, int x, int y, int make_to_ten = 1);
void print_shell(int matrix_num[][10], int line, int row, int make_to_ten = 1);
void print_new_square(int matrix_num[][10], int line, int row, int x, int y, int make_to_ten = 1);
void print_new_shell(int matrix_num[][10], int line, int row, int make_to_ten = 1);
void output_info(int line, int direction, const char* str, int no_line);
