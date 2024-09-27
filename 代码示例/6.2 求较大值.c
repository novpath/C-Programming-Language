#include<stdio.h>

int max(int a, int b)
{
    int ret;
    if(a > b)
        ret = a;
    else
        ret = b;
    
    return ret;
}

int main()
{
    int a, b, c;
    a = 2;
    b = 5;
    c = max(2, 5);
    c = max(a, b);
    c = max(c, 25);
    printf("%d\n", max(a, b));
    
    return 0;
}
