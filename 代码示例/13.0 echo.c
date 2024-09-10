#include<stdio.h>

int main(int argc, char * argv[])
{
	int k;
	for(k = 1; k < argc; k ++)
		printf("%s", argv[k]);
	printf("\n");
	
	return 0;
}
