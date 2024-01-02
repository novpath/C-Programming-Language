#include<stdio.h>

int main()
{
	int count = 0;
	int isPrime;
	int n, m;
	int sum = 0;

	scanf("%d %d", &n, &m);
	
	int i, j;
	j = 2;
	while(count < m) 
	{
		isPrime = 1;
		for(i = 2; i < j; i ++)
		{
			if(j % i == 0)
			{
				isPrime = 0;
				break;
			}
		}
		if(isPrime == 1)
		{
			count ++;
			if(count >= n && count <= m)
			{
				sum += j; 
			} 
		}
		j ++;
	}
	
	printf("%d", sum);
	
	return 0;
}
