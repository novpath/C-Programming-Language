#include<stdio.h>

int main()
{
	int n;
	int odd = 0;
	int even = 0;
	
	scanf("%d", &n);
	while(n != -1)
	{
		scanf("%d", &n);
		if(n % 2 == 0)
			even ++;
		else
			odd ++;
	}
	
	printf("%d %d", odd, even);
	
	
	return 0;
}
