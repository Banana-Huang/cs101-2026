#include <stdio.h>

int add_func(int a, int b)
{
    return a + b;
}

int main(void)
{
    int n = 10;
    int m = 1;
    int (*func_ptr)(int, int) = add_func;

    printf("%d\n", func_ptr(n, m));
    return 0;
}
