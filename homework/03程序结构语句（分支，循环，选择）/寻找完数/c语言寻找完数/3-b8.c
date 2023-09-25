/*ÍõºÆ ÐÅ07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
    int a, b, n;
    for (a = 2; a < 1000; a++)
    {
        n = 0;
        for (b = 1; b < a; b++)
        {
            if ((a % b) == 0)
            {
                n+=b;
            }
        }
        if (n == a)
        {
            printf("%d its factors are ", a);
            for (b = 1; b < a; b++)
            {
                if (a % b == 0)
                {
                    printf("%d ", b);
                }
            }
            printf("\n");
        }
    }
    return 0;
}