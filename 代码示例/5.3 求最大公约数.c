#include<stdio.h>

int main()
{
	int a, b;

	scanf("%d %d", &a, &b);
	
	int ret = 0;
	int i;
	for(i = 1; i < ((a < b)? a : b); i ++)
	{
	    if(a % i == 0 && b % i == 0)
	    {
	    	ret = i;  //如果求最小公约数可以直接break
	    }
	}

	printf("%d和%d的最大公约数是%d。\n", a, b, ret);
	
	return 0;
}
