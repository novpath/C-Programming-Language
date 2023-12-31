#include<stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    
    int digit;
    int ret = 0;
    
    while(x > 0)
    {
        digit = x % 10;
        ret = 10 * ret + digit;
        x /= 10;
    }
    
    printf("%d", ret);
    
    return 0;
}
