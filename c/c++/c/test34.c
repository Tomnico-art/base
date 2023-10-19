#include<stdio.h>

int main()
{
    int a[5] = {1,2,3,4,5};
    int *pt = (int *)(&a + 1);
    printf("%d, %d\n", *(a+1), *(pt-1));//2 5

    return 0;
}