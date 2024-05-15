#include<stdio.h>

void minmax(int a[], int lenm, int *max, int *min);

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 16, 17, 21, 23, 55, };
	int min, max;
	printf("main sizeof(a)=%lu\n", sizeof(a));
	printf("main a=%p\n", a);
	minmax(a, sizeof(a)/sizeof(a[0]), &min, &max);
	printf("a[0]=%d\n", a[0]);
	printf("min=%d,max=%d\n", min, max);
	
	return 0;
}

void minmax(int a[], int len, int *min, int *max)
{
	int i;
	printf("minmax sizeof(a)=%lu\n", sizeof(a));
	printf("minmax a=%p\n", a);
	a[0] = 1000;
	*min = *max = a[0];
	for(i = 1; i < len; i ++)
	{
		if(a[i] < *min)
			*min = a[i];
		if(a[i] > *max)
			*max = a[i]; 
	}
}
