/*���� ��07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    double pi = 3.14159, a, b;
    printf("������뾶�͸߶�\n");
    scanf("%lf %lf", &a, &b);
    printf("Բ�ܳ�    :%.2lf\n", 2 * pi * a);
    printf("Բ���    :%.2lf\n", pi * a * a);
    printf("Բ������:%.2lf\n", 4 * pi * a * a);
    printf("Բ�����  :%.2lf\n", 4 * pi * a * a * a / 3);
    printf("Բ�����  :%.2lf\n", pi * a * a * b);
    return 0;
}
