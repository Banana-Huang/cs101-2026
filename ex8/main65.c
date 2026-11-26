#include <stdio.h>

void func(int *i, int *j)
{
    printf("in func, i = %d, j = %d\n", *i, *j);

    int temp = *j;
    *j = *i;
    *i = temp;

    printf("in func, i = %d, j = %d\n", *i, *j);
}

int main(void)
{
    int n = 1;
    int m = 2;

    func(&n, &m);
    printf("in main, n = %d, m = %d\n", n, m);
    return 0;
}
