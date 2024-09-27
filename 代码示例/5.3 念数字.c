#include<stdio.h>

int main()
{
	int x;
	int mask = 1;
	scanf("%d", &x);
	
	if(x < 0)
	{
		printf("fu ");
		x = -x;
	}
	
	int t = x;
	while(t > 9)
	{
		t /= 10;
		mask *= 10;
	}
	while(mask > 0)
	{
		int d = x / mask;
		switch(d)
		{
			case 0: printf("ling"); break;
			case 1: printf("yi"); break;
			case 2: printf("er"); break;
			case 3: printf("san"); break;
			case 4: printf("si"); break;
			case 5: printf("wu"); break;
			case 6: printf("liu"); break;
			case 7: printf("qi"); break;
			case 8: printf("ba"); break;
			case 9: printf("jiu"); break;
		}
		if(mask > 9)
		{
			printf(" ");
		}
		x %= mask;
		mask /= 10;
	}
	
	return 0;
}
