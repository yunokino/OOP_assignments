/*王浩 信07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c;
    long i;
    float d, pi = 3.14159f;
    printf( "请输入三角形的两边及其夹角(角度)\n");
    scanf("%d %d %d",&a,&b,&c);
    i = a * b;
    d = i * sin(c * pi / 180) / 2;
    printf("三角形面积为 : %.3f", d);

    return 0;
}

