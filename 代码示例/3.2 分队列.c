#include<stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int odd = 1;
    if(n % 2 == 0)
        odd = 0;
    
    for(int i = 1; i <= n; i = i + 2)
    {
        printf("%d", i);
        if(odd == 1)
		{
        	if(i != n)
        		printf(" ");
		} 
        else
        {
        	if(i != n - 1)
                printf(" ");
		}       
    }
    
    return 0;
}
