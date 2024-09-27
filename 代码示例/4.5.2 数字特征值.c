#include<stdio.h>

int main()
{
	int n;
	int val = 0;
	int digit = 1;
	int i = 1;
	
	scanf("%d", &n);
	while(n != 0)
	{
		if(n % 2 == digit % 2)
			{
				val += i;
			}
		i *= 2;
		digit ++;
		n /= 10;
	}
	
	printf("%d", val);
	
	return 0;
}
