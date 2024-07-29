#include<stdio.h>
#include "acllib.h" 

int Setup()
{
	initConsole();
	printf("Input width:");
	int width;
	scanf("%d", &width);
	initWindow("test", 100, 100, width, width);
	beginPaint();
	line(20, 20, width - 20, width - 20);
	endPaint();
	
	return 0;
}
