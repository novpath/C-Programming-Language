#include<stdio.h>

int main()
{
 	int x;
    scanf("%d", &x);
    
    int mask = 1;
    int t = x;
    while(t > 9)
    {
        t /= 10;
        mask *= 10;
    }
	
    while(mask > 0)
    {
        int d = x / mask;
        printf("%d", d);
        if(mask > 9)
        {
            printf(" ");
        }
        x %= mask;
        mask /= 10;
    }
    
    return 0;
}
