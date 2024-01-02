#include<stdio.h>

int main()
{
	int a = 1;
	int b = 3;
	int c = 7;
	int d = 15;
	int e = 24;
	int f = 35;
	
	a=b+=c++-d+--e/-f;
	
	printf("a=%d  b=%d  c=%d  d=%d e=%d  f=%d", a, b, c, d, e, f);
	
	//a=-5  b=-5  c=8  d=15 e=23  f=35
	return 0;
}
